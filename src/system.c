#include "system.h"

void rccInit(){
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOCEN 
                 |  RCC_AHB4ENR_GPIODEN | RCC_AHB4ENR_GPIOEEN | RCC_AHB4ENR_GPIOGEN
                 |  RCC_APB4ENR_SYSCFGEN| ;
    RCC->APB1LENR |= RCC_APB1LENR_USART3EN;
}

void sysCfgInit(){
    SYSCFG->PMCR |= SYSCFG_PMCR_EPIS_SEL_2;
}

void gpioInit(){
    // LEDS
    GPIOB->MODER &= ~(GPIO_MODER_MODER0_1);     // LED GREEN
    GPIOE->MODER &= ~(GPIO_MODER_MODER1_1);     // LED YELLOW
    GPIOB->MODER &= ~(GPIO_MODER_MODER14_1);    // LED RED

    // USART3
    GPIOD->MODER &= ~(GPIO_MODER_MODER8_0);     // USART3 TX
    GPIOD->AFR[1] |= 7<<4*0;
    GPIOD->MODER &= ~(GPIO_MODER_MODER9_0);     // USART3 TX
    GPIOD->AFR[1] |= 7<<4*1;

    // ETH
    GPIOA->MODER &= ~(GPIO_MODER_MODER1_0);     // ETH_REF_CLK
    GPIOA->AFR[0] |= 11<<4*1;
    GPIOA->MODER &= ~(GPIO_MODER_MODER2_0);     // ETH_MDIO
    GPIOA->AFR[0] |= 11<<4*2;
    GPIOA->MODER &= ~(GPIO_MODER_MODER7_0);     // ETH_CRS_DV
    GPIOA->AFR[0] |= 11<<4*7;
    GPIOB->MODER &= ~(GPIO_MODER_MODER13_0);    // ETH_TXD1
    GPIOB->AFR[1] |= 11<<4*5;
    GPIOC->MODER &= ~(GPIO_MODER_MODER1_0);     // ETH_MDC
    GPIOC->AFR[0] |= 11<<4*1;
    GPIOC->MODER &= ~(GPIO_MODER_MODER4_0);     // ETH_RXD0
    GPIOC->AFR[0] |= 11<<4*4;
    GPIOC->MODER &= ~(GPIO_MODER_MODER5_0);     // ETH_RXD1
    GPIOC->AFR[0] |= 11<<4*5;
    GPIOG->MODER &= ~(GPIO_MODER_MODER11_0);    // ETH_TX_EX
    GPIOG->AFR[1] |= 11<<4*3;
    GPIOG->MODER &= ~(GPIO_MODER_MODER13_0);    // ETH_TXD0
    GPIOG->AFR[1] |= 11<<4*5;
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

void ethInit(){
    ETH->DMAMR |= ETH_DMAMR_SWR;
    while(ETH->DMAMR & ETH_DMAMR_SWR);
}

void sysInit(){
    xdev_out(uartWrite);
    rccInit();
    sysCfgInit();
    delayInit();
    gpioInit();
    uartInit();
}

