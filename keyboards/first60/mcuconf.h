// Copyright 2022 sserj0 (@sserj0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>


#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE

#undef RP_I2C_USE_I2C2
#define RP_I2C_USE_I2C2 FALSE


#undef RP_ADC_USE_ADC1
#define RP_ADC_USE_ADC1 TRUE

#undef RP_ADC_USE_ADC2
#define RP_ADC_USE_ADC2 TRUE

#undef RP_IRQ_ADC1_PRIORITY
#define RP_IRQ_ADC1_PRIORITY 3
