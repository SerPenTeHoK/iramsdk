/******************************************************************************
 * FileName: gpio_func.h
 * Description: gpio set
 * Alternate SDK ver 0.0.0 (b0)
 * Author: PV`
 * (c) PV` 2015
*******************************************************************************/
#ifndef _IO_GPIO_FUNC_H_
#define _IO_GPIO_FUNC_H_

#include "hw/eagle_soc.h"
#include "eagle_soc.h"

////---------------------------------15141312111009080706050403020100
//#define _FUN_GPIO ((unsigned int)0b11111111111111111111000011001100) // ������� (�� 2 ���� �� ����� ����) ������� ������� ����� ��� ��������� � ����� GPIO
#define _FUN_GPIO ((uint32_t)0xFFFFF0CCul) // ������� (�� 2 ���� �� ����� ����) ������� ������� ����� ��� ��������� � ����� GPIO
#define PERIPHS_GPIO_FUN(PIN_NUM) ((uint32_t)(_FUN_GPIO >> (PIN_NUM<<1)) & 0x03) // ��������� I/O ���� � ����� ����� GPIOn
#define _FUN_DEF_GPIO ((uint64_t)0x3333111111000200ull) // ������� (�� 4 ���� �� ����� ����) ������� ������� ����� ��� ��������� � ����� �� �������� � SDK
#define PERIPHS_IO_FUN_DEF(PIN_NUM) ((uint32_t)((_FUN_DEF_GPIO >> (PIN_NUM<<2)) & 0x0F)) // ��������� I/O ���� � ����� �� ��������� ��� SDK
#define _IO_MUX_GPIO ((uint64_t)0x3210BA9876FE4D5Cull) // ������� (�� 4 ���� �� ����� ����) ������� IO_MUX � ������������ � �������� GPIOn
#define PERIPHS_IO_MUX_GPIO_ADDR(PIN_NUM) (PERIPHS_IO_MUX + 0x04 + (uint32_t)(((_IO_MUX_GPIO>>(PIN_NUM<<2)) & 0x0F)<<2)) // �������� ����� IO_MUX � ������������ � ������� GPIOn

#define PIN_FUNC_IOPORT(n) PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO_ADDR(n), PERIPHS_GPIO_FUN(n)) // ���������� ������� GPIOn ��� I/O port
#define PIN_FUNC_DEFAULT(n) PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO_ADDR(n), PERIPHS_IO_FUN_DEF(n)) // ���������� ������� GPIOn �� ��������� ��� SDK

#endif /* _IO_GPIO_FUNC_H_ */
