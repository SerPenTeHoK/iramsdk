#include "ram_sdk.h"

//#undef ICACHE_FLASH_ATTR
//#define ICACHE_FLASH_ATTR

os_timer_t test_timer;

//=============================================================================
void test_timer_isr(void)
{
	ets_printf("*");
	ets_uart_printf("#");
}

//=============================================================================
void tests(void)
{
	ets_set_idle_cb(NULL, NULL); // снять callback
	ets_intr_unlock();
	ets_printf(">");
}

//=============================================================================
void user_init(void)
{
	ets_timer_disarm(&test_timer);
	ets_timer_setfn(&test_timer, (os_timer_func_t *)test_timer_isr, NULL);
	ets_timer_arm_new(&test_timer, 1000000, 1, 0); // 1 раз в сек
	ets_set_idle_cb(tests, NULL); // после инициалаизации запустить tests()
}
