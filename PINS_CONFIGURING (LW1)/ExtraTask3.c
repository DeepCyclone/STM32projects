#include <stm32g431xx.h>

#define ALLOWED_ATTEMPTS 3

enum sequence
{
	first = 1<<0 | 1<<7,
	second = 1<<1 | 1<<6,
	third = 1<<2 | 1<<5,
	fourth = 1<<3 | 1<<4
};

void turnoff_leds();
void dummy_delay(uint32_t);
void run_victory_animation();
void run_error_animation();

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE7_Pos | 1 << GPIO_MODER_MODE6_Pos | 1 << GPIO_MODER_MODE5_Pos);

	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk);
	GPIOC->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);

	uint32_t attempt = 1;
	uint32_t led1_pos = 0;
	uint32_t led2_pos = 0;
	uint32_t led3_pos = 0;
	uint32_t led4_pos = 0;
	uint32_t current_pos = 0;

	while(1)
	{
		if(GPIOA->IDR & GPIO_IDR_ID0)
		{
			GPIOA->ODR |= GPIO_ODR_OD5;
			led1_pos |= 1 << current_pos;
			dummy_delay(1000000);
			GPIOA->ODR &= ~GPIO_ODR_OD5;
			current_pos++;
			while(GPIOA->IDR & GPIO_IDR_ID0);
		}
		if(GPIOA->IDR & GPIO_IDR_ID1)
		{
			GPIOA->ODR |= GPIO_ODR_OD6;
			led2_pos |= 1 << current_pos;
			dummy_delay(1000000);
			GPIOA->ODR &= ~GPIO_ODR_OD6;
			current_pos++;
			while(GPIOA->IDR & GPIO_IDR_ID1);
		}
		if(GPIOC->IDR & GPIO_IDR_ID2)
		{
			GPIOA->ODR |= GPIO_ODR_OD7;
			led3_pos |= 1 << current_pos;
			dummy_delay(1000000);
			GPIOA->ODR &= ~GPIO_ODR_OD7;
			current_pos++;
			while(GPIOC->IDR & GPIO_IDR_ID2);
		}
		if(GPIOC->IDR & GPIO_IDR_ID3)
		{
			GPIOA->ODR |= GPIO_ODR_OD8;
			led4_pos |= 1 << current_pos;
			dummy_delay(1000000);
			GPIOA->ODR &= ~GPIO_ODR_OD8;
			current_pos++;
			while(GPIOC->IDR & GPIO_IDR_ID3);
		}
		if(current_pos == 8)
		{
			turnoff_leds();
			if(led1_pos == first && led2_pos == second && led3_pos == third && led4_pos == fourth)
			{
				while(1)
				{
					run_victory_animation();
				}
			}
			else
			{
				for(uint32_t i = 0;i<=3;i++)
				{
					run_error_animation();
				}
			}
			if(attempt == ALLOWED_ATTEMPTS)
			{
				while(1)
				{
					run_error_animation();
				}
			}
			attempt++;
			current_pos = 0;
			led1_pos = led2_pos = led3_pos = led4_pos = 0;
		}
	}
}

void dummy_delay(uint32_t duration)
{
   for(int32_t i = 0; i < duration; ++i);
}

void turnoff_leds()
{
	GPIOA->ODR &= ~(GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8);
}

void run_victory_animation()
{
	GPIOA->ODR |= GPIO_ODR_OD5;
	dummy_delay(500000);
	GPIOA->ODR |= GPIO_ODR_OD6;
	dummy_delay(500000);
	GPIOA->ODR |= GPIO_ODR_OD7;
	GPIOA->ODR &= ~GPIO_ODR_OD5;
	dummy_delay(500000);
	GPIOA->ODR |= GPIO_ODR_OD8;
	GPIOA->ODR &= ~GPIO_ODR_OD6;
	dummy_delay(500000);
	GPIOA->ODR &= ~GPIO_ODR_OD7;
	dummy_delay(500000);
	GPIOA->ODR &= ~GPIO_ODR_OD8;
	dummy_delay(500000);
}

void run_error_animation()
{
	GPIOA->ODR |= (GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8);
	dummy_delay(1000000);
	GPIOA->ODR &= ~(GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8);
	dummy_delay(1000000);
}
