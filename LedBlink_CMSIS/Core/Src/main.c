#include "stm32f1xx.h"

void delay_1s(void) {
    SysTick->LOAD = 8000000 - 1;  // Tính toán Reload value
    SysTick->VAL = 0;                                  // Đặt lại giá trị hiện tại
    SysTick->CTRL = 0x7;                               // Bật timer, chọn sysclk làm nguồn clock, và kích thích ngắt

    while ((SysTick->CTRL & 0x10000) == 0) {
        // Đợi cho đến khi cờ COUNT flag được thiết lập
    }

    SysTick->CTRL = 0;  // Dừng SysTick timer (Enable = 0)
}

int main(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;  // Bật clock cho GPIOC
    GPIOC->CRH = (GPIOC->CRH & 0xFF0FFFFF) | 0x00200000;  // Cấu hình PC13 làm đầu ra (mode 2)

    while (1) {
        delay_1s();  // Chờ 1 giây
    }
}
