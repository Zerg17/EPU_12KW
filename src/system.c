#include "system.h"

void rccInit(){
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIODEN | RCC_AHB4ENR_GPIOEEN;
    RCC->APB1LENR |= RCC_APB1LENR_USART3EN;
}

void gpioInit(){
    GPIOB->MODER &= ~(GPIO_MODER_MODER0_1);  // LED GREEN
    GPIOE->MODER &= ~(GPIO_MODER_MODER1_1);  // LED YELLOW
    GPIOB->MODER &= ~(GPIO_MODER_MODER14_1); // LED RED

    GPIOD->MODER &= ~(GPIO_MODER_MODER8_0); // USART3 TX
    GPIOD->AFR[1] |= 0x00000007;

    GPIOD->MODER &= ~(GPIO_MODER_MODER9_0); // USART3 TX
    GPIOD->AFR[1] |= 0x00000070;
}

void uartInit(){
    USART3->BRR = (F_CPU+BOAD/2)/BOAD;
    USART3->CR1 = USART_CR1_TE | USART_CR1_RE;
    //USART3->CR2 = USART_CR2_ABREN | USART_CR2_ABRMODE_Msk;
    USART3->CR1 |= USART_CR1_UE;
}

void uartWrite(uint8_t d){
    while(!(USART3->ISR & USART_ISR_TXE));
    USART3->TDR=d;
}

void sysInit(){
    xdev_out(uartWrite);
    rccInit();
    delayInit();
    gpioInit();
    uartInit();
}

