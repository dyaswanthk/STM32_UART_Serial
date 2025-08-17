#ifndef __DMA_H
#define __DMA_H

#include "stm32f4xx_ll_dma.h"

extern void DMA_ClearFlag_TC(DMA_TypeDef *DMAx, uint8_t stream);
extern uint32_t DMA_IsActiveFlag_TC(DMA_TypeDef *DMAx, uint8_t stream);

extern void DMA_ClearFlag(void *DMAx, uint8_t stream_channel);
extern uint32_t DMA_IsActiveFlag(void *DMAx, uint8_t stream_channel);


#endif
