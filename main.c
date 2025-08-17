#include "main.h"

uint8_t serialTxBuffer[128] = "hello";
uint8_t serialRxBuffer[128];
uint8_t size;
void main(void)
{
  size = strlen(serialTxBuffer);
  clockInit();
  serialPort6 = serialOpen(USART6, 6, 57600, 0, 0, 0, RxCallBack, 0);
  timer2Init();
  while(1)
  {
    serialProcessRx(serialPort6);
  }
}

void TIM2_IRQHandler(void)
{
  if(TIM2->SR & TIM_SR_UIF)
  {
    TIM2->SR &= ~TIM_SR_UIF;
    serialScheduleTx(serialPort6,serialTxBuffer,size,SERIAL_NOTICE_MESSAGE);
    //serialTx(serialPort6, serialTxBuffer, size);
    serialSendListItem(serialPort6);
    //debug_printf("hi");
  }    
}
