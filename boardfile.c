#include "boardfile.h"
#include <stdint.h>


//CONTAINS THE CONFIGURATIONS OF THE MICROCONTROLLER

/*
  | | | |
  | | | |
  | | | |
rows - > numbers of uarts
columns -> attribute
values -> value
  */
uint8_t uart1BufferRx[UART_MIN_BUFFER], uart1BufferTx[UART_MIN_BUFFER],
      uart2BufferRx[UART_BUFFER_RX_SIZE], uart2BufferTx[UART_BUFFER_RX_SIZE],
      uart6BufferRx[UART_BUFFER_RX_SIZE], uart6BufferTx[UART_BUFFER_RX_SIZE];

uint32_t UARTS[NUM_UARTS] =                                   {1,2,6};
uint32_t UART_TX_GPIO_PINS[NUM_UARTS] =                       {LL_GPIO_PIN_9,   LL_GPIO_PIN_2, LL_GPIO_PIN_11};
uint32_t UART_RX_GPIO_PINS[NUM_UARTS] =                       {LL_GPIO_PIN_10,  LL_GPIO_PIN_3, LL_GPIO_PIN_12};
GPIO_TypeDef *UART_TX_GPIO_PORTS[NUM_UARTS] =                 {GPIOA,  GPIOA,  GPIOA};
GPIO_TypeDef *UART_RX_GPIO_PORTS[NUM_UARTS] =                 {GPIOA,  GPIOA,  GPIOA};
uint32_t UART_GPIO_AF[NUM_UARTS] =                            {7,  7,  8 };
uint32_t UART_RX_DMA_STREAM[NUM_UARTS] =                      {5,  5,  2 };
uint32_t UART_TX_DMA_STREAM[NUM_UARTS] =                      {7,  6,  6 };
DMA_TypeDef *UART_TX_DMA_NUMBER[NUM_UARTS] =                  {DMA2,    DMA1,   DMA2};
DMA_TypeDef *UART_RX_DMA_NUMBER[NUM_UARTS] =                  {DMA2,    DMA1,   DMA2};
uint32_t UART_TX_DMA_CHANNEL[NUM_UARTS] =                     {LL_DMA_CHANNEL_4, LL_DMA_CHANNEL_4, LL_DMA_CHANNEL_5};
uint32_t UART_RX_DMA_CHANNEL[NUM_UARTS] =                     {LL_DMA_CHANNEL_4, LL_DMA_CHANNEL_4, LL_DMA_CHANNEL_5};
uint8_t* UARTSRXBUFFER[NUM_UARTS] =                           {uart1BufferRx, uart2BufferRx, uart6BufferRx};
uint8_t* UARTSTXBUFFER[NUM_UARTS] =                           {uart1BufferTx, uart2BufferTx, uart6BufferTx};
