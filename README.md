# IRAM SDK
IRAM SDK ESP8266 
---
Базовый комплект (IRAM SDK)<br>
для загрузки и отладки тестового кода в IRAM без записи в flash.<br>

Размер IRAM у ESP8266 составляет 64 килобайта.<br> 

Использует только функции ROM-BIOS и IramSDK.<br>

В IramSDK входит:<br>
1) Инициализация частот процеcсора ESP8266 на 80 или 160 МГц.<br>
2) Инициализация bss в RAM и IRAM.<br>
3) Инициализация UART.<br>
4) Инициализация менеджера памяти 'heap'.<br>
5) Инициализация таймера на работу в мсек.<br>
6) Инициализация ets_printf() для вывода отладки в TX2/GPIO2.<br>

ets_uart_printf() выводит в TX/UATR0<br>
ets_printf() выводит в TX2/UATR1<br>

```
IRAM SDK Init.
 Free Heap: 81816
 Free IRAM: 64036
>
```

Для компиляции SDK используется [Unofficial Developer Kit](http://esp8266.ru/forum/forums/devkit/).<br>

В Eclipse заданы 2 опции Manage Configurations:<br>
1. AutoMake (собрать проект для загрузки, используются установки в Eclipse)<br>
2. Default (собрать проект для загрузки используя makefile)<br>
