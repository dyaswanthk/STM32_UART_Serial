#include "main.h"

uint8_t serialTxBuffer[128] = "hello";
uint8_t serialRxBuffer[128];
uint8_t size;
void main(void)
{
  size = strlen(serialTxBuffer);
  clockInit();
  serialPort1 = serialOpen(USART1, 1, 57600, 0, 0, 0, RxCallBack, 0);
  timer2Init();
  while(1)
  {
    serialProcessRx(serialPort1);
  }
}

void TIM2_IRQHandler(void)
{
  if(TIM2->SR & TIM_SR_UIF)
  {
    TIM2->SR &= ~TIM_SR_UIF;
    serialScheduleTx(serialPort1,serialTxBuffer,size,SERIAL_NOTICE_MESSAGE);
    serialSendListItem(serialPort1);
    //debug_printf("hi");
  }    
}
