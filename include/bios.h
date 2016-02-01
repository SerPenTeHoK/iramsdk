/******************************************************************************
 * FileName: bios.h
 * Description: funcs in ROM-BIOS
 * Alternate SDK ver 0.0.0 (b0)
 * Author: PV`
 * (c) PV` 2015
*******************************************************************************/
#ifndef _INCLUDE_BIOS_H_
#define _INCLUDE_BIOS_H_
#include "bios/spiflash.h"

#include "bios/cha1.h"
#include "bios/ets.h"
#include "bios/gpio.h"
#include "bios/uart.h"
#include "bios/vectors.h"
#include "bios/xthal.h"
#include "bios/xtos.h"
#include "bios/rtc_dtm.h"
#include "bios/add_funcs.h"

#define system_get_time() (*((volatile unsigned int *)(0x3FF20C00))) // io2_regs_[768]
#define system_get_rtc_time()  IO_RTC_SLP_CNT_VAL
#define system_get_timer_time()  TIMER1_COUNT
#define system_get_cpu_clk_count()  xthal_get_ccount()

#endif // _INCLUDE_BIOS_H_
