#include "dma.h"

void DMAx_Init(DMA_Channel_TypeDef* DMAy_Channelx, unit32_t par, unit32_t mar, uint16_t ndtr) {
    DMA_InitTypeDef  DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  // Enable DMA1 clock

    /* Configure DMA */
    DMA_InitStructure.DMA_PeripheralBaseAddr = par;  // DMA peripheral address
    DMA_InitStructure.DMA_MemoryBaseAddr = mar;  // DMA memory address
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  // Memory to peripheral mode
    DMA_InitStructure.DMA_BufferSize = ndtr;  // Data size
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  // Peripheral non-increment mode
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  // Memory increment mode
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  // Peripheral data length: 8 bits
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  // Memory data length: 8 bits
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMAy_Channelx, &DMA_InitStructure);
}

void DMAx_Enable(DMA_Channel_TypeDef *DMAy_Channelx, uint16_t ndtr) {
    DMA_Cmd(DMAy_Channelx, DISABLE);
    DMA_SetCurrDataCounter(DMAy_Channelx, ndtr);
    DMA_Cmd(DMAy_Channelx, ENABLE);
}
