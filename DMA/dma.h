#ifndef DMA_DMA_H_
#define DMA_DMA_H_

#include "system.h"


/**
 * @brief DMA initialization function.
 *
 * This function initializes the specified DMA channel with the given parameters.
 *
 * @param DMAy_Channelx: Selects the DMA channel, where x can be 1 to 7.
 * @param par: Specifies the peripheral base address for DMA transfers.
 * @param mar: Specifies the memory base address for DMA transfers.
 * @param ndtr: Specifies the number of data to be transferred.
 *
 * @return None
 */
void DMAx_Init(DMA_Channel_TypeDef* DMAy_Channelx, unit32_t par, unit32_t mar, uint16_t ndtr);

/**
 * @brief Enables a single DMA transfer.
 *
 * This function enables a single DMA transfer on the specified channel with the given data transfer count.
 *
 * @param DMAy_Channelx: Selects the DMA channel, where x can be 1 to 7.
 * @param ndtr: Specifies the number of data to be transferred.
 *
 * @return None
 */
void DMAx_Enable(DMA_Channel_TypeDef *DMAy_Channelx, uint16_t ndtr);

#endif  // DMA_DMA_H_
