#include "SysTick.h"
#include "dma.h"
#include "key.h"
#include "led.h"
#include "system.h"
#include "usart.h"

#define send_buf_len 5000

unit8_t send_buf[send_buf_len];
void Send_Data(unit8_t *p) {
    uint16_t i;
    for (i = 0; i < send_buf_len; i++) {
        *p = '5';
        p++;
    }
}

int main() {
    unit8_t i = 0;
    unit8_t key;

    SysTick_Init(72);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
    USART1_Init(9600);
    KEY_Init();
    DMAx_Init(DMA1_Channel4, (unit32_t)&USART1->DR, (unit32_t)send_buf, send_buf_len);
    Send_Data(send_buf);

    while (1) {
        key = KEY_Scan(0);
        if (key == KEY_UP) {
            USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
            DMAx_Enable(DMA1_Channel4, send_buf_len);

            while (1) {
                if (DMA_GetFlagStatus(DMA1_FLAG_TC4) != 0) {
                    DMA_ClearFlag(DMA1_FLAG_TC4);
                    break;
                }
                led2 = !led2;
                delay_ms(300);
            }
        }

        i++;
        if (i % 20 == 0) {
            led1 = !led1;
        }

        delay_ms(10);
    }
}
