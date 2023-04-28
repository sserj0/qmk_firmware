// Copyright 2022 sserj0 (@sserj0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "print.h"
#include "first60oled.h"
#include "analog.h"
#include <stdio.h>



#define _BL 0
#define _FL 1
#define _CL 2

enum custom_keycodes {
    ADC_SAMPLE = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │Ctrl│GUI │Alt │                        │ Alt│ GUI│Menu│Ctrl│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     */
    [_BL] = LAYOUT_60_ansi(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENTER,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPACE,                             MO(_FL), KC_DOWN, KC_UP,  KC_RIGHT
    ),

    [_FL] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,   KC_F12,   BL_STEP,
        _______, _______, _______,_______,_______,_______,_______,_______,KC_PSCR,KC_SCRL, KC_PAUS,  _______,  _______,  _______,
        _______, _______, _______,_______,_______,_______,_______,_______,_______,RGB_TOG,  _______,  _______,  _______,_______,                         
        _______, _______, _______,_______,_______,_______,_______,_______,_______,_______,           KC_PGUP,         
        RGB_TOG, KC_LGUI, KC_LALT,                            KC_SPACE,                        MO(_FL),  KC_HOME,  KC_PGDN,  KC_END
    )
};


static bool precision = false;
static uint16_t precision_mod = 64;
static uint16_t axis_val = 127;

//Joystick

#ifndef ADC1_PIN
    #define ADC1_PIN GP27
#endif

#ifndef ADC2_PIN
    #define ADC2_PIN GP28
#endif


joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(ADC1_PIN, 0, 512, 1023),  //x
    JOYSTICK_AXIS_IN(ADC2_PIN, 0, 512, 1023)    //y
    //JOYSTICK_AXIS_VIRTUAL  // y
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed

    int16_t val_x = analogReadPin(ADC1_PIN);
    int16_t val_y = analogReadPin(ADC2_PIN);
    #ifdef CONSOLE_ENABLE

        uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u, ADC X: %u, ADC Y: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count, val_x, val_y);


    #endif 

     int16_t precision_val = axis_val;
        if (precision) {
            precision_val -= precision_mod;
        }

        switch (keycode) {
        case KC_1:
            //joystick_set_axis(1, record->event.pressed ? -precision_val : 0);
            uprintf("Joystick 1 pressed.\n");
            return false;
        case KC_2:
            //joystick_set_axis(1, record->event.pressed ? precision_val : 0);
            return false;
        case KC_3:
            //joystick_set_axis(0, record->event.pressed ? -precision_val : 0);
            return false;
        case KC_4:
            //joystick_set_axis(0, record->event.pressed ? precision_val : 0);
            return false;
        case KC_5:
            precision = record->event.pressed;
            return false;
    }

  return true;
}


#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return true;
}
#endif



/*
void process_joystick_axes(int8_t x, int8_t y) {
    if (x > JOYSTICK_DEADZONE) {
        tap_code(KC_RGHT);
    } else if (x < -JOYSTICK_DEADZONE) {
        tap_code(KC_LEFT);
    }

    if (y > JOYSTICK_DEADZONE) {
        tap_code(KC_UP);
    } else if (y < -JOYSTICK_DEADZONE) {
        tap_code(KC_DOWN);
    }
}

*/


/*
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
*/

/*

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (layer >= _FN) {
        // Translate move to scroll when Fn is active
        mouse_report.h = sign(mouse_report.x);
        mouse_report.v = sign(mouse_report.y);
        mouse_report.x = 0;
        mouse_report.y = 0;

        // Only send once every SCROLL_WAIT_PERIOD ticks to slow scroll down
        if (mouse_report.h || mouse_report.v) {
            if (scroll_ticks != 0) {
                mouse_report.h = 0;
                mouse_report.v = 0;
            }
            scroll_ticks = (scroll_ticks + 1) % SCROLL_WAIT_PERIOD;
        }
    }

    return mouse_report;
}

*/