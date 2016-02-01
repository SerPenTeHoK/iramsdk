#ifndef _RAM_SDK_H_
#define _RAM_SDK_H_

#include "user_config.h"
#include "bios.h"
#include "osapi.h"
#include "os_type.h"
#include "hw/esp8266.h"
#include "sdk/mem_manager.h"

#define system_get_time() (*((volatile unsigned int *)(0x3FF20C00))) // io2_regs_[768]
#define system_get_rtc_time()  IO_RTC_SLP_CNT_VAL
#define system_get_timer_time()  TIMER1_COUNT
#define system_get_cpu_clk_count()  xthal_get_ccount()

typedef struct t_eraminfo // описание свободной области в iram
{
	uint32 *base;	// адрес начала буфера
	int32 size; 	// размер в байтах
}ERAMInfo;

/* описание свободной области (буфера) в iram */
extern ERAMInfo eraminfo;

extern void ets_timer_arm_new(ETSTimer *ptimer, uint32_t us_ms, int repeat_flag, int isMstimer);
extern void call_user_start(void);
extern void uart_wait_tx_fifo_empty(void);
extern void user_init(void);
extern void uart0_init(uint32 baud, uint32 cfg);
extern void uart0_write_char(unsigned char c);



#endif // _RAM_SDK_H_
