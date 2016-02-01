/*
 * RAM SDK
 */
#include "ram_sdk.h"
#include "hw/uart_register.h"

#undef ICACHE_FLASH_ATTR
#define ICACHE_FLASH_ATTR

//=============================================================================
// Вывод в (UART0)
//-----------------------------------------------------------------------------
void uart0_write_char(unsigned char c)
{
	do {
		MEMW();
		if(((UART0_STATUS >> UART_TXFIFO_CNT_S) & UART_TXFIFO_CNT) <= 125) break;
	} while(1);
    UART0_FIFO = c;
}
//=============================================================================
// Стандартный вывод putc (UART1)
//-----------------------------------------------------------------------------
void uart1_write_char(char c)
{
	if (c != '\r') {
		do {
			MEMW();
			if(((UART1_STATUS >> UART_TXFIFO_CNT_S) & UART_TXFIFO_CNT) <= 125) break;
		} while(1);
		if (c != '\n') UART1_FIFO = c;
		else {
		    UART1_FIFO = '\r';
		    UART1_FIFO = '\n';
		}
	}
}

//=============================================================================
// Инициализация IRAM
//-----------------------------------------------------------------------------
extern uint32 _text_start[]; // start addr IRAM
extern uint32 _lit4_start[]; // addr data buf IRAM
/* Определение размера свободного буфера в IRAM и очистка BSS IRAM (сегмент DATA_IRAM_ATTR) */
int iram_buf_init(void)
{
	 uint32 dwsize = 0x0C000>>2;
	 switch(((DPORT_BASE[9]>>3)&3)) {
	 case 0:
		 dwsize = 0x10000 >> 2;
		 break;
	 case 3:
		 dwsize = 0x08000 >> 2;
		 break;
	 }
	 uint32 * end = &_text_start[dwsize];
	 eraminfo.size = (int32)((uint32)(end) - (uint32)eraminfo.base);
	 if(eraminfo.size > 0) {
		 uint32 * ptr = _lit4_start;
		 while(ptr < end) *ptr++ = 0;
	 }
#if DEBUGSOO > 1
	 else {
		 ets_printf("No free IRAM!");
	 }
#endif
	 return eraminfo.size;
}
//=============================================================================
// uart_wait_tx_fifo_empty()
//-----------------------------------------------------------------------------
void uart_wait_tx_fifo_empty(void)
{
	while((UART0_STATUS >> UART_TXFIFO_CNT_S) & UART_TXFIFO_CNT);
	while((UART1_STATUS >> UART_TXFIFO_CNT_S) & UART_TXFIFO_CNT);
}
//=============================================================================
// uart0_init()
// cfg:
// = 0 - 1 stop
// = 1 - 2 stop
// = 2 - parity odd + stop
// = 3 - parity even + stop
//-----------------------------------------------------------------------------
void uart0_init(uint32 baud, uint32 cfg)
{
	UART0_CLKDIV = ((ets_get_cpu_frequency()  * 1000000) >> (CLK_PRE_PORT & 1)) / baud;
	UART1_CONF0 = 0x1C | (cfg & 3) | ((cfg & UART_PARITY_EN)? 0 : (cfg+1) << UART_STOP_BIT_NUM_S);
}
//=============================================================================
// uart1_init()
// cfg:
// = 0 - 1 stop
// = 1 - 2 stop
// = 2 - parity odd + stop
// = 3 - parity even + stop
//-----------------------------------------------------------------------------
void uart1_init(uint32 baud, uint32 cfg)
{
	GPIO2_MUX = (1<<GPIO_MUX_FUN_BIT1);
	UART1_CLKDIV = ((ets_get_cpu_frequency()  * 1000000) >> (CLK_PRE_PORT & 1)) / baud;
	UART1_CONF0 = 0x1C | (cfg & 3) | ((cfg & UART_PARITY_EN)? 0 : (cfg+1) << UART_STOP_BIT_NUM_S);
	os_install_putc1((void *)uart1_write_char); // install uart1 putc callback
}
//=============================================================================
// call_user_start()
//-----------------------------------------------------------------------------
extern uint8 _bss_start;
extern uint8 _bss_end;

void call_user_start(void)
{
	IO_RTC_4 = 0; // отключить WiFi
	GPIO0_MUX = 0; // отключить вывод Q_CLK
	// Очистка сегмента bss //	mem_clr_bss();
	uint8 * ptr = &_bss_start;
	while(ptr < &_bss_end) *ptr++ = 0;
	iram_buf_init(); // определить и разметить свободную IRAM
	prvHeapInit(); // инициализация менеджера памяти heap
//	ets_delay_us(50); // ожидание вывода последнего байта для esptool
	// Включить CLK CPU 160 MHz
	rom_i2c_writeReg(103, 4, 1, 136);
	rom_i2c_writeReg(103, 4, 2, 145);
	CLK_PRE_PORT |= 1;
	ets_update_cpu_frequency(80 * 2);
	IO_RTC_4 = 0xfe000000; // переключить источник тактирования (частоту) для I2S,...
	ets_timer_init();
	TIMER1_CTRL = 0x84;	// таймер в us
	UART0_INT_ENA = 0;
	uart0_init(115200, 0);
	uart1_init(230400, 0);
	ets_printf("\n\nIRAM SDK Init.\n Free Heap: %d\n Free IRAM: %d\n", system_get_free_heap_size(), eraminfo.size);
	uart_wait_tx_fifo_empty();
	user_init();
	ets_run();
}
