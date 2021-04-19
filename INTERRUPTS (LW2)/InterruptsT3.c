#include <stm32g431xx.h>

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA | SYSCFG_EXTICR1_EXTI1_PA | SYSCFG_EXTICR1_EXTI2_PC | SYSCFG_EXTICR1_EXTI3_PC;

	EXTI->IMR1 |= EXTI_IMR1_IM0 | EXTI_IMR1_IM1 | EXTI_IMR1_IM2 | EXTI_IMR1_IM3;
	EXTI->RTSR1 |= EXTI_RTSR1_RT0 | EXTI_RTSR1_RT1 | EXTI_RTSR1_RT2 | EXTI_RTSR1_RT3;
	EXTI->FTSR1 |= EXTI_FTSR1_FT0 | EXTI_FTSR1_FT1 | EXTI_FTSR1_FT2 | EXTI_FTSR1_FT3;

	GPIOA->MODER &= ~(GPIO_MODER_MODE5_Msk | GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE8_Msk);
	GPIOA->MODER |= (1<<GPIO_MODER_MODE5_Pos | 1<<GPIO_MODER_MODE6_Pos | 1<<GPIO_MODER_MODE7_Pos | 1<<GPIO_MODER_MODE8_Pos);

	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk);
	GPIOC->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);

	while(1)
	{

	}
}

void EXTI0_IRQHandler()
{
	if(GPIOA->ODR & GPIO_ODR_OD5)
	{
		GPIOA->ODR &= ~GPIO_ODR_OD5;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_OD5;
	}
	EXTI->PR1 = EXTI_PR1_PIF0;
}
void EXTI1_IRQHandler()
{
	if(GPIOA->ODR & GPIO_ODR_OD6)
	{
		GPIOA->ODR &= ~GPIO_ODR_OD6;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_OD6;
	}
	EXTI->PR1 = EXTI_PR1_PIF1;
}
void EXTI2_IRQHandler()
{
	if(GPIOA->ODR & GPIO_ODR_OD7)
	{
		GPIOA->ODR &= ~GPIO_ODR_OD7;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_OD7;
	}
	EXTI->PR1 = EXTI_PR1_PIF2;
}
void EXTI3_IRQHandler()
{
	if(GPIOA->ODR & GPIO_ODR_OD8)
	{
		GPIOA->ODR &= ~GPIO_ODR_OD8;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_OD8;
	}
	EXTI->PR1 = EXTI_PR1_PIF3;
}
