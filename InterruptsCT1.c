#include <stm32g431xx.h>
#define LONG_PRESSING_TIME 3000000

void turnoff_leds();
void dummy_delay(uint32_t duration);
uint32_t score = 0;
int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;

	EXTI->RTSR1 |= EXTI_RTSR1_RT0;
	EXTI->IMR1 |= EXTI_IMR1_IM0;

	NVIC_EnableIRQ(EXTI0_IRQn);

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE7_Pos | 1 << GPIO_MODER_MODE6_Pos | 1 << GPIO_MODER_MODE5_Pos);
	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk);

	while(1)
	{

	}
}

void EXTI0_IRQHandler()
{
	uint32_t pressing_duration = 0;
	while(GPIOA->IDR & GPIO_IDR_ID0)
	{
		pressing_duration++;
	}
	if(pressing_duration > LONG_PRESSING_TIME)
	{
		score = 0;
		turnoff_leds();
	}
	if(pressing_duration < LONG_PRESSING_TIME && pressing_duration > 0)
	{
		score += 1;
		turnoff_leds();
		GPIOA->ODR |= (score & 0x0F) << 5;
	}
	EXTI->PR1 = EXTI_PR1_PIF0;
}
void turnoff_leds()
{
	GPIOA->ODR &= ~(GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8);
}

void dummy_delay(uint32_t duration)
{
   for(int32_t i = 0; i < duration; ++i);
}
