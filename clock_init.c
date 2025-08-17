#include "clock_init.h"

/*
  Refer to Fig. 12 Clock tree, page 94, reference manual

  External crystal - 25MHz
  HSE - 25 MHz
  /M - /25
  Input frequency to PLL - 1MHz (Typical PLL input clock frequency is 1 MHz, refer to Table 41, page 81, datasheet )
  xN = x336
  VCO output - 336 MHz
  /P - /4
  PLLCLK - 84 MHz
  /Q - /7
  PLL48CK - 48 MHz

Max frequency allowed for: (Table 14, page 59 - datasheet)
  AHB - 84 Mhz
  APB2 peripheral clock - 84 MHz
  APB1 peripheral clock - 42 MHz

  Refer to Fig. 16, page no. 152, reference manual 
  AHB prescalar - 1
  APB2 prescalar - 1
  APB1 prescalar - 2

  APB2 timer clock - 84 MHz (x1)
  APB1 timer clock - 84 MHz (x2)


*/

void clockInit(void) {
FLASH->ACR |= FLASH_ACR_PRFTEN;

  PWR->CR &= ~PWR_CR_VOS;
  PWR->CR |= (0b10<<PWR_CR_VOS_Pos);  /* scale 3 mode*/

  RCC->CR |= RCC_CR_HSEON;
  while(!(RCC->CR & RCC_CR_HSERDY));

  RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;

  RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
  RCC->PLLCFGR |= (25<<RCC_PLLCFGR_PLLM_Pos);

  RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
  RCC->PLLCFGR |= (336<<RCC_PLLCFGR_PLLN_Pos);

  RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
  RCC->PLLCFGR |= (0b01<<RCC_PLLCFGR_PLLP_Pos);

  RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ;
  RCC->PLLCFGR |= (7<<RCC_PLLCFGR_PLLQ_Pos);

  RCC->CR |= RCC_CR_PLLON;
  while(!(RCC->CR & RCC_CR_PLLRDY));

  // latency - 2 Wait state - table 6, page 46 - reference manual  
  // with 84 Mhz clock frequency, 2 wait states are required 
  FLASH->ACR |= (0x2<<FLASH_ACR_LATENCY_Pos);
  while((FLASH->ACR & FLASH_ACR_LATENCY) != 0x2);

  RCC->CFGR &= ~RCC_CFGR_HPRE;

/* According reference manual prescaling values for PPRE2 and PPRE1:
    0xx - divide by 1
    100 - divide by 2
    101 - divide by 4
    110 - divide by 8
    111 - divide by 16
*/
  RCC->CFGR &= ~RCC_CFGR_PPRE2;   /* AHB clock not divided for APB2 */
//  RCC->CFGR |= (0b100<<RCC_CFGR_PPRE2_Pos);

  RCC->CFGR &= ~RCC_CFGR_PPRE1;   /* AHB clock divided by 2 for APB1 */
  RCC->CFGR |= (0b100<<RCC_CFGR_PPRE1_Pos);


  RCC->CFGR |= (0b10 << RCC_CFGR_SW_Pos);
  while((RCC->CFGR & RCC_CFGR_SWS) != (0b10 << RCC_CFGR_SWS_Pos));

  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  SYSCFG->CMPCR = SYSCFG_CMPCR_CMP_PD;
  
  RCC->CSR |= RCC_CSR_RMVF;


  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  RCC->APB2ENR |= RCC_APB2ENR_USART6EN;

  //RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

}