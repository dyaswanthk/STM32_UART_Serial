#include "serial.h"

//this file contains the serial processes

/* defining a few preprocesses for now, must to in board file */

#include "boardfile.h"
#include "dma.h"
#include <string.h>
#include <stdlib.h>

uint8_t findUartIndex(uint32_t UART){
  for(int uart_index = 0; uart_index < NUM_UARTS; uart_index++){
      if(UART == UARTS[uart_index])
        return uart_index;
  }

  return 0;
}

uint8_t uart2BufferRx[128], uart2BufferTx[128], uart1BufferRx[128], uart1BufferTx[128];

serialPort_t *serialOpen(USART_TypeDef *USARTx, uint32_t UART, uint32_t baud, uint16_t flowControl, uint8_t usageMethod, uint8_t dmaOutputUsage, serialRxCallBack_t* rxCallBack, uint8_t callbackParam){

    serialPort_t *s = 0;

    LL_GPIO_InitTypeDef GPIO_InitStruct;
    LL_USART_InitTypeDef USART_InitStruct;
    LL_DMA_InitTypeDef DMA_InitStruct;

    s = (serialPort_t *)calloc(1, sizeof(serialPort_t)); //used calloc instead aqCalloc
    s->rxCallBack = rxCallBack;
    s->callbackParam = callbackParam;
    s->txHead = 0;
    s->txTail = 0;
    s->uartStatus = IDLE;

    s->uartIndex = findUartIndex(UART);

      s->txPin =  UART_TX_GPIO_PINS[s->uartIndex];
      s->rxPin =  UART_RX_GPIO_PINS[s->uartIndex];
      s->txPort = UART_TX_GPIO_PORTS[s->uartIndex];
      s->rxPort = UART_RX_GPIO_PORTS[s->uartIndex];
      s->afType = UART_GPIO_AF[s->uartIndex];

      s->uartBufferRx = uart2BufferRx;
      s->rxDMAx = UART_RX_DMA_NUMBER[s->uartIndex];
      s->rxDMAStreamNumber= UART_RX_DMA_STREAM[s->uartIndex];
      s->rxDMAChannel = UART_RX_DMA_CHANNEL[s->uartIndex];

      s->uartBufferTx = uart2BufferTx;
      s->txDMAx = UART_TX_DMA_NUMBER[s->uartIndex];
      s->txDMAStreamNumber= UART_TX_DMA_STREAM[s->uartIndex];
      s->txDMAChannel = UART_TX_DMA_CHANNEL[s->uartIndex];

 //   if (USARTx == USART2){
 ////   RCC->APB1ENR |= RCC_APB1ENR_USART2EN; //turn on clock
 //     s->txPin =  UART2_TX_GPIO_PIN;
 //     s->rxPin =  UART2_RX_GPIO_PIN;
 //     s->txPort = UART2_TX_GPIO_PORT;
 //     s->rxPort = UART2_RX_GPIO_PORT;
 //     s->afType = UART2_GPIO_AF;

 //     s->uartBufferRx = uart2BufferRx;
 //     s->rxDMAx = UART2_RX_DMA_NUMBER;
 //     s->rxDMAStreamNumber= UART2_RX_DMA_STREAM;
 //     s->rxDMAChannel = UART2_RX_DMA_CHANNEL;

 //     s->uartBufferTx = uart2BufferTx;
 //     s->txDMAx = UART2_TX_DMA_NUMBER;
 //     s->txDMAStreamNumber= UART2_TX_DMA_STREAM;
 //     s->txDMAChannel = UART2_TX_DMA_CHANNEL;
 //    }

    LL_USART_StructInit(&USART_InitStruct);
    USART_InitStruct.BaudRate = baud;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    USART_InitStruct.HardwareFlowControl = flowControl;
    LL_USART_Init(USARTx, &USART_InitStruct);
    LL_USART_EnableDMAReq_TX(USARTx);
    LL_USART_EnableDMAReq_RX(USARTx);
    LL_USART_Enable(USARTx);

    LL_GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Pin = s->txPin;
    GPIO_InitStruct.Alternate = s->afType;
    LL_GPIO_Init(s->txPort, &GPIO_InitStruct);

    LL_GPIO_StructInit(&GPIO_InitStruct);     
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Pin = s->rxPin;
    GPIO_InitStruct.Alternate = s->afType;
    LL_GPIO_Init(s->rxPort, &GPIO_InitStruct);

    
    //DMA for sending data to uart - ENABLING TX DMA STREAM WHEN NDTR = 0 RAISES TEIF.
    LL_DMA_StructInit(&DMA_InitStruct); 
    DMA_InitStruct.PeriphOrM2MSrcAddress  = (uint32_t)&(USARTx->DR);
    DMA_InitStruct.MemoryOrM2MDstAddress  = (uint32_t)&(uart2BufferTx[0]);
    DMA_InitStruct.NbData                 = 0;
    DMA_InitStruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;
    DMA_InitStruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
    DMA_InitStruct.Direction              = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
    DMA_InitStruct.Mode                   = LL_DMA_MODE_NORMAL;
    DMA_InitStruct.Channel 		  = s->txDMAChannel;//changed DMA channel from hardcoded value to strucuture member
    LL_DMA_Init(s->txDMAx, s->txDMAStreamNumber, &DMA_InitStruct);
  //  LL_DMA_EnableStream(s->txDMAx, s->txDMAStreamNumber);

    //DMA for receiving Data from uart
    LL_DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.PeriphOrM2MSrcAddress  = (uint32_t)&USARTx->DR;
    DMA_InitStruct.MemoryOrM2MDstAddress  = (uint32_t)&(uart2BufferRx[0]);//(uint32_t)(uart_buffer_rx);
    DMA_InitStruct.NbData                 = UART_BUFFER_RX_SIZE;
    DMA_InitStruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;
    DMA_InitStruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
    DMA_InitStruct.Direction              = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
    DMA_InitStruct.Mode                   = LL_DMA_MODE_CIRCULAR;
    DMA_InitStruct.Channel 		  = s->rxDMAChannel;//changed DMA channel from hardcoded value to strucuture member
    LL_DMA_Init(s->rxDMAx, s->rxDMAStreamNumber, &DMA_InitStruct);
    LL_DMA_EnableStream(s->rxDMAx, s->rxDMAStreamNumber);

    s->txStart = 1;
    return s;
}


void serialProcessRx(serialPort_t* s){
    int i, j;
    int bytesRead = 0;
    int unprocessedDataLength;
    //ndtr holds number of bytes remaining to be transferred.
    int ndtr = LL_DMA_GetDataLength(s->rxDMAx, s->rxDMAStreamNumber);

    s->rxHead = UART_BUFFER_RX_SIZE - ndtr;
    if (s->rxHead > s->rxTail){
       unprocessedDataLength = s->rxHead - s->rxTail;
       bytesRead = s->rxCallBack(&s->uartBufferRx[s->rxTail], unprocessedDataLength);
    }
    else if (s->rxHead < s->rxTail){
       unprocessedDataLength = s->rxHead + UART_BUFFER_RX_SIZE - s->rxTail;
       memcpy(&s->tempRxBuf[0], &s->uartBufferRx[s->rxTail], UART_BUFFER_RX_SIZE - s->rxTail);
       memcpy(&s->tempRxBuf[UART_BUFFER_RX_SIZE - s->rxTail], &s->uartBufferRx[0], s->rxHead);
       bytesRead = s->rxCallBack(s->tempRxBuf, unprocessedDataLength);
    }
    s->rxTail = (s->rxTail + bytesRead) % UART_BUFFER_RX_SIZE;
    
}

void serialTx(serialPort_t *s, uint8_t* buffer, uint32_t length){
  //This has been converted into a blocking call and is best avoided
  //ClearFlag is stream specific - check how to modularise  
  
  while(LL_DMA_IsActiveFlag_TC6(s->txDMAx) == 0); 
//ClearFlag is stream specific - check how to modularise  
  LL_DMA_ClearFlag_TC6(s->txDMAx); //, s->txDMAStreamNumber);// clear transfer complete flag
  LL_DMA_SetMemoryAddress(s->txDMAx, s->txDMAStreamNumber, (uint32_t)buffer);
  LL_DMA_SetDataLength(s->txDMAx, s->txDMAStreamNumber, length);
  LL_DMA_EnableStream(s->txDMAx, s->txDMAStreamNumber);
}



void serialSendListItem(serialPort_t* s){
  if(DMA_IsActiveFlag_TC(s->txDMAx, s->txDMAStreamNumber) && (s->uartStatus == PROCESSING)){
    DMA_ClearFlag_TC(s->txDMAx, s->txDMAStreamNumber);
    s->txTail = (s->txTail + 1) % SERIAL_LIST_SIZE;
    s->uartStatus = IDLE;
  }
  if((s->txHead != s->txTail) && s->uartStatus == IDLE){
    LL_DMA_SetMemoryAddress(s->txDMAx, s->txDMAStreamNumber, (uint32_t)s->sendList[s->txTail].data);
    LL_DMA_SetDataLength(s->txDMAx, s->txDMAStreamNumber, s->sendList[s->txTail].size);
    LL_DMA_EnableStream(s->txDMAx, s->txDMAStreamNumber);
    s->uartStatus = PROCESSING;
  }
}

void serialScheduleTx(serialPort_t *s, uint8_t* buffer, uint32_t length, uint8_t msgType){
    //Insert data in the head
    s->sendList[s->txHead].data = buffer;
    s->sendList[s->txHead].size = length;
    s->sendList[s->txHead].type = msgType;
    s->txHead = (s->txHead + 1) % SERIAL_LIST_SIZE;
}

void serialPrint(uint8_t *str, serialPort_t *serialPortx){
// strlen doesn't work, need to change this so the user passes the length of the data.
    int len = strlen(str);
    uint8_t buffer[50];
    memcpy(buffer,str,len);
    if (len){
        serialScheduleTx(serialPortx, str, len, SERIAL_NOTICE_MESSAGE);
    }
   
 }

 uint32_t RxCallBack(uint8_t* data, uint32_t size)
 {
    memcpy(serialRxBuffer, data, size);
    debug_printf("%s",serialRxBuffer);
    return size;
 }

serialPort_t* serialPort1;
serialPort_t* serialPort2;
serialPort_t* serialPort6;
