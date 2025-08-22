#ifndef __SERIAL_H
#define __SERIAL_H

#include <string.h>
#include <stdlib.h>
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_usart.h"
#include "main.h"
#include "boardfile.h"
#include "dma.h"

#define UART_BUFFER_TX_SIZE 1024
#define UART_BUFFER_RX_SIZE 1024
#define UART_MIN_BUFFER 128
#define SERIAL_LIST_SIZE 5


typedef struct{
   uint8_t* data;
   uint8_t type;
   uint16_t size;
} sendList_t;

enum serialUsage{
  SERIAL_USE_DMA = 0,
  SERIAL_USE_INTERRUPT
};

enum serialMsgType{
 SERIAL_TELEMETRY_MESSAGE = 0,
 SERIAL_NOTICE_MESSAGE,
 SERIAL_TEST_MESSAGE
};

typedef enum{
  IDLE,
  PROCESSING
}uartStatus_t; 

typedef uint32_t serialRxCallBack_t(uint8_t* data, uint32_t size);

typedef struct {
    unsigned int baudRate;
    uint16_t flowControl;
    uint16_t parity;
    uint16_t stopBits;

    uint8_t* uartBufferRx;//To be retired
    uint8_t* uartBufferTx;//To be retired
    sendList_t sendList[SERIAL_LIST_SIZE];
    volatile unsigned int txHead, txTail;

    //unsigned int rxBufSize;
    //volatile unsigned char *rxBuf;
    volatile unsigned int rxHead, rxTail;
    uint8_t tempRxBuf[UART_BUFFER_RX_SIZE];
    serialRxCallBack_t* rxCallBack;
    uint8_t callbackParam;
    uint8_t txStart;
    uint8_t uartIndex;

    //This should not be expected from the user as input but rather passed through boardfile
    unsigned long txPin, rxPin;
    GPIO_TypeDef * txPort;
    GPIO_TypeDef*  rxPort;
    USART_TypeDef *USARTx;
    DMA_TypeDef* rxDMAx;
    DMA_TypeDef* txDMAx;
    uint8_t rxDMAStreamNumber;
    uint8_t txDMAStreamNumber;
    uint32_t rxDMAMuxRequest;
    uint32_t txDMAMuxRequest;
    uint32_t txDMAIrqn;
    uint32_t afType;
    uint32_t rxDMAChannel;
    uint32_t txDMAChannel;

    uartStatus_t uartStatus;
} serialPort_t;


extern serialPort_t* serialPort1;
extern serialPort_t* serialPort2;
extern serialPort_t* serialPort6;
serialPort_t *serialOpen(USART_TypeDef *USARTx, uint32_t uart, uint32_t baud, uint16_t flowControl, uint8_t usageMethod, uint8_t dmaOutputUsage, serialRxCallBack_t* rxCallBack, uint8_t callbackParam);
void serialTx(serialPort_t *s, uint8_t* buffer, uint32_t length);
void serialScheduleTx(serialPort_t *s, uint8_t* buffer, uint32_t length, uint8_t msgType);
void serialProcessRx(serialPort_t* s);
void serialSendListItem(serialPort_t*);
void serialPrint(uint8_t*, serialPort_t*);

uint32_t RxCallBack(uint8_t* data, uint32_t size);
#endif


