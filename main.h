#ifndef MAIN_H
#define MAIN_H

#include "serial.h"
#include "dma.h"
#include "clock_init.h"
#include "timer.h"
#include <debugio.h>
#include <string.h>
#include "stm32f4xx.h"

extern uint8_t serialTxBuffer[128];
extern uint8_t serialRxBuffer[128];

#endif