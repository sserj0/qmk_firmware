// Copyright 2022 sserj0 (@sserj0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "first60oled.h"

uint8_t logged_row = 0, logged_col = 0;
uint32_t oled_timer = 0;

void oled_timer_reset() { oled_timer = timer_read32(); }

/*
void set_keylog(uint16_t keycode, keyrecord_t *record) {
    logged_row = record->event.key.row;
    logged_col = record->event.key.col;
}

*/

#if OLED_ENABLE
const char *read_logo(void) {
  static char logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};

  return logo;
}


bool oled_task_user(void) {
    oled_write(read_logo(), false);


     // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);


    return false;
}


#endif
