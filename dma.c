#include "dma.h"

void DMA_ClearFlag_TC(DMA_TypeDef *DMAx, uint8_t stream)
{
  switch (stream)
  {
    case LL_DMA_STREAM_0:
      LL_DMA_ClearFlag_TC0(DMAx);
      break;
    case LL_DMA_STREAM_1:
      LL_DMA_ClearFlag_TC1(DMAx);
      break;
    case LL_DMA_STREAM_2:
      LL_DMA_ClearFlag_TC2(DMAx);
      break;
    case LL_DMA_STREAM_3:
      LL_DMA_ClearFlag_TC3(DMAx);
      break;
    case LL_DMA_STREAM_4:
      LL_DMA_ClearFlag_TC4(DMAx);
      break;
    case LL_DMA_STREAM_5:
      LL_DMA_ClearFlag_TC5(DMAx);
      break;
    case LL_DMA_STREAM_6:
      LL_DMA_ClearFlag_TC6(DMAx);
      break;
    case LL_DMA_STREAM_7:
      LL_DMA_ClearFlag_TC7(DMAx);
      break;
    default:
      break;
  }
}


uint32_t DMA_IsActiveFlag_TC(DMA_TypeDef *DMAx, uint8_t stream)
{
  switch (stream)
  {
    case LL_DMA_STREAM_0:
      return LL_DMA_IsActiveFlag_TC0(DMAx);
    case LL_DMA_STREAM_1:
      return LL_DMA_IsActiveFlag_TC1(DMAx);
    case LL_DMA_STREAM_2:
      return LL_DMA_IsActiveFlag_TC2(DMAx);
    case LL_DMA_STREAM_3:
      return LL_DMA_IsActiveFlag_TC3(DMAx);
    case LL_DMA_STREAM_4:
      return LL_DMA_IsActiveFlag_TC4(DMAx);
    case LL_DMA_STREAM_5:
      return LL_DMA_IsActiveFlag_TC5(DMAx);
    case LL_DMA_STREAM_6:
      return LL_DMA_IsActiveFlag_TC6(DMAx);
    case LL_DMA_STREAM_7:
      return LL_DMA_IsActiveFlag_TC7(DMAx);
    default:
      break;
  }

}


/* NOT NEEDED FOR THIS PROJECT
void DMA_ClearFlag(void *DMAx, uint8_t stream_channel)
{
  if (DMAx == BDMA)
  {
    switch (stream_channel)
    {
      case LL_BDMA_CHANNEL_0:
        LL_BDMA_ClearFlag_TC0(DMAx);
        break;
      case LL_BDMA_CHANNEL_1:
        LL_BDMA_ClearFlag_TC1(DMAx);
        break;
      case LL_BDMA_CHANNEL_2:
        LL_BDMA_ClearFlag_TC2(DMAx);
        break;
      case LL_BDMA_CHANNEL_3:
        LL_BDMA_ClearFlag_TC3(DMAx);
        break;
      case LL_BDMA_CHANNEL_4:
        LL_BDMA_ClearFlag_TC4(DMAx);
        break;
      case LL_BDMA_CHANNEL_5:
        LL_BDMA_ClearFlag_TC5(DMAx);
        break;
      case LL_BDMA_CHANNEL_6:
        LL_BDMA_ClearFlag_TC6(DMAx);
        break;
      case LL_BDMA_CHANNEL_7:
        LL_BDMA_ClearFlag_TC7(DMAx);
        break;
      default:
        break;
    }
  }
  else
  {
    switch (stream_channel)
    {
      case LL_DMA_STREAM_0:
        LL_DMA_ClearFlag_TC0(DMAx);
        break;
      case LL_DMA_STREAM_1:
        LL_DMA_ClearFlag_TC1(DMAx);
        break;
      case LL_DMA_STREAM_2:
        LL_DMA_ClearFlag_TC2(DMAx);
        break;
      case LL_DMA_STREAM_3:
        LL_DMA_ClearFlag_TC3(DMAx);
        break;
      case LL_DMA_STREAM_4:
        LL_DMA_ClearFlag_TC4(DMAx);
        break;
      case LL_DMA_STREAM_5:
        LL_DMA_ClearFlag_TC5(DMAx);
        break;
      case LL_DMA_STREAM_6:
        LL_DMA_ClearFlag_TC6(DMAx);
        break;
      case LL_DMA_STREAM_7:
        LL_DMA_ClearFlag_TC7(DMAx);
        break;
      default:
        break;
    }
  }
}



uint32_t DMA_IsActiveFlag(void *DMAx, uint8_t stream_channel)
{
  if (DMAx == BDMA)
  {
    switch (stream_channel)
    {
      case LL_BDMA_CHANNEL_0:
        return LL_BDMA_IsActiveFlag_TC0(DMAx);
      case LL_BDMA_CHANNEL_1:
        return LL_BDMA_IsActiveFlag_TC1(DMAx);
      case LL_BDMA_CHANNEL_2:
        return LL_BDMA_IsActiveFlag_TC2(DMAx);
      case LL_BDMA_CHANNEL_3:
        return LL_BDMA_IsActiveFlag_TC3(DMAx);
      case LL_BDMA_CHANNEL_4:
        return LL_BDMA_IsActiveFlag_TC4(DMAx);
      case LL_BDMA_CHANNEL_5:
        return LL_BDMA_IsActiveFlag_TC5(DMAx);
      case LL_BDMA_CHANNEL_6:
        return LL_BDMA_IsActiveFlag_TC6(DMAx);
      case LL_BDMA_CHANNEL_7:
        return LL_BDMA_IsActiveFlag_TC7(DMAx);
      default:
        break;
    }
  }
  else
  {
    switch (stream_channel)
    {
      case LL_DMA_STREAM_0:
        return LL_DMA_IsActiveFlag_TC0(DMAx);
      case LL_DMA_STREAM_1:
        return LL_DMA_IsActiveFlag_TC1(DMAx);
      case LL_DMA_STREAM_2:
        return LL_DMA_IsActiveFlag_TC2(DMAx);
      case LL_DMA_STREAM_3:
        return LL_DMA_IsActiveFlag_TC3(DMAx);
      case LL_DMA_STREAM_4:
        return LL_DMA_IsActiveFlag_TC4(DMAx);
      case LL_DMA_STREAM_5:
        return LL_DMA_IsActiveFlag_TC5(DMAx);
      case LL_DMA_STREAM_6:
        return LL_DMA_IsActiveFlag_TC6(DMAx);
      case LL_DMA_STREAM_7:
        return LL_DMA_IsActiveFlag_TC7(DMAx);
      default:
        break;
    }
  }
}

*/
