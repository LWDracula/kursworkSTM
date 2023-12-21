#include "RTE_Components.h" 
#include CMSIS_device_header 
#include <stdio.h> 
#include <stdlib.h>

// текущие огоньки
static volatile int8_t fireworks = 1; 

// текущий режим
typedef enum 
{
	  Reflection,
    Diverging,
    Colliding
} WorkMode;

WorkMode CurrentMode;

// текущая скорость
volatile int speed = 3;


void initKeypad() { 
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // разрешаем работу GPIO A 
	// обнуляем значения регистров 
	GPIOA->CRL = 0;  
	GPIOA->CRH = 0; 
	//PA0-PA9 Input, Pull up 
	SET_BIT(GPIOA->CRL, GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 | GPIO_CRL_CNF2_1 ); 
	// pull up 
	SET_BIT(GPIOA->ODR, GPIO_ODR_ODR0 | GPIO_ODR_ODR1 | GPIO_ODR_ODR2);   
	// выбираем в качестве внешних входов EXTI линии: 
	// EXTIn = PAn 
	AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PA | AFIO_EXTICR1_EXTI1_PA | 
	AFIO_EXTICR1_EXTI2_PA | AFIO_EXTICR1_EXTI3_PA;  
} 

void initOutput() { 
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // разрешаем работу GPIO  B
	// PC13, Output mode, max speed 50 MHz, General purpose output push-pull 
	GPIOB->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13); 
	SET_BIT(GPIOB->CRH, GPIO_CRH_MODE13);
} 

void initIRQ() { 
	// прерывание на спад сигнала 
	SET_BIT(EXTI->FTSR, EXTI_FTSR_TR0 | EXTI_FTSR_TR1 | EXTI_FTSR_TR2); 
	// разрешаем прерывания внешних линий 0-2, 10 - софтовое прерывание 
	SET_BIT(EXTI->IMR, EXTI_IMR_MR0 | EXTI_IMR_MR1 | EXTI_IMR_MR2); 
	NVIC_EnableIRQ(EXTI0_IRQn); 
	NVIC_EnableIRQ(EXTI1_IRQn); 
	NVIC_EnableIRQ(EXTI2_IRQn);  
	
	NVIC_SetPriority(EXTI0_IRQn, 1); 
	NVIC_SetPriority(EXTI1_IRQn, 1); 
	NVIC_SetPriority(EXTI2_IRQn, 1); 
	
} 



void Delay(volatile int speeds) 
{  
volatile int counters = 0;
volatile int speedcounter = 0;
    while(counters != 10)
        {
          while(speedcounter != speeds)
            
           {speedcounter++;}
            speedcounter = 0;
            counters++;
        }
        counters = 0;
}

void reflection()
{
	
	float speedLocal = speed;
	int8_t fireworksLocal = fireworks;
	static volatile int counter = 0;
	if (fireworksLocal == 1)
	{
		// Right
		GPIOB->ODR|=GPIO_ODR_ODR2;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR2;
		GPIOB->ODR|=GPIO_ODR_ODR3;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR3;
		GPIOB->ODR|=GPIO_ODR_ODR4;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR4;
		GPIOB->ODR|=GPIO_ODR_ODR5;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR6;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR6;
		GPIOB->ODR|=GPIO_ODR_ODR7;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR7;
		GPIOB->ODR|=GPIO_ODR_ODR8;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR8;
		GPIOB->ODR|=GPIO_ODR_ODR9;
		// Left
		GPIOB->ODR&= ~GPIO_ODR_ODR9;
		GPIOB->ODR|=GPIO_ODR_ODR8;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR8;
		GPIOB->ODR|=GPIO_ODR_ODR7;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR7;
		GPIOB->ODR|=GPIO_ODR_ODR6;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR6;
		GPIOB->ODR|=GPIO_ODR_ODR5;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR4;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR4;
		GPIOB->ODR|=GPIO_ODR_ODR3;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR3;
		GPIOB->ODR|=GPIO_ODR_ODR2;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR2;
	}
	else if (fireworksLocal == 2)
	{
		// Right
		GPIOB->ODR|=GPIO_ODR_ODR2;
		GPIOB->ODR|=GPIO_ODR_ODR3;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR2;
		GPIOB->ODR|=GPIO_ODR_ODR4;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR3;
		GPIOB->ODR|=GPIO_ODR_ODR5;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR4;
		GPIOB->ODR|=GPIO_ODR_ODR6;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR7;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR6;
		GPIOB->ODR|=GPIO_ODR_ODR8;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR7;
		GPIOB->ODR|=GPIO_ODR_ODR9;
		// Left
		GPIOB->ODR&= ~GPIO_ODR_ODR9;
		GPIOB->ODR|=GPIO_ODR_ODR7;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR8;
		GPIOB->ODR|=GPIO_ODR_ODR6;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR7;
		GPIOB->ODR|=GPIO_ODR_ODR5;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR6;
		GPIOB->ODR|=GPIO_ODR_ODR4;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR3;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR4;
		GPIOB->ODR|=GPIO_ODR_ODR2;
	}
}

void diverging()
{
	float speedLocal = speed;
	int8_t fireworksLocal = fireworks;
	if (fireworksLocal == 1)
	{
		GPIOB->ODR|=GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR6;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR6;
		GPIOB->ODR&= ~GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR4;
		GPIOB->ODR|=GPIO_ODR_ODR7;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR4;
		GPIOB->ODR&= ~GPIO_ODR_ODR7;
		GPIOB->ODR|=GPIO_ODR_ODR3;
		GPIOB->ODR|=GPIO_ODR_ODR8;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR3;
		GPIOB->ODR&= ~GPIO_ODR_ODR8;
		GPIOB->ODR|=GPIO_ODR_ODR2;
		GPIOB->ODR|=GPIO_ODR_ODR9;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR2;
		GPIOB->ODR&= ~GPIO_ODR_ODR9;
	}
	else if (fireworksLocal == 2)
	{
		GPIOB->ODR|=GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR6;
		GPIOB->ODR|=GPIO_ODR_ODR4;
		GPIOB->ODR|=GPIO_ODR_ODR7;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR6;
		GPIOB->ODR&= ~GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR3;
		GPIOB->ODR|=GPIO_ODR_ODR8;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR4;
		GPIOB->ODR&= ~GPIO_ODR_ODR7;
		GPIOB->ODR|=GPIO_ODR_ODR2;
		GPIOB->ODR|=GPIO_ODR_ODR9;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR3;
		GPIOB->ODR&= ~GPIO_ODR_ODR8;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR2;
		GPIOB->ODR&= ~GPIO_ODR_ODR9;
		Delay(speed);
	}
}
void colliding()
{
	float speedLocal = speed;
	int8_t fireworksLocal = fireworks;
	if (fireworksLocal == 1)
	{
		GPIOB->ODR|=GPIO_ODR_ODR2;
		GPIOB->ODR|=GPIO_ODR_ODR9;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR2;
		GPIOB->ODR&= ~GPIO_ODR_ODR9;
		GPIOB->ODR|=GPIO_ODR_ODR3;
		GPIOB->ODR|=GPIO_ODR_ODR8;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR3;
		GPIOB->ODR&= ~GPIO_ODR_ODR8;
		GPIOB->ODR|=GPIO_ODR_ODR4;
		GPIOB->ODR|=GPIO_ODR_ODR7;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR4;
		GPIOB->ODR&= ~GPIO_ODR_ODR7;
		GPIOB->ODR|=GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR6;
		Delay(speed);
		GPIOB->ODR|=GPIO_ODR_ODR4;
		GPIOB->ODR|=GPIO_ODR_ODR7;
		GPIOB->ODR|=GPIO_ODR_ODR3;
		GPIOB->ODR|=GPIO_ODR_ODR8;
		GPIOB->ODR|=GPIO_ODR_ODR2;
		GPIOB->ODR|=GPIO_ODR_ODR9;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR5;
		GPIOB->ODR&= ~GPIO_ODR_ODR6;
		GPIOB->ODR&= ~GPIO_ODR_ODR4;
		GPIOB->ODR&= ~GPIO_ODR_ODR7;
		GPIOB->ODR&= ~GPIO_ODR_ODR3;
		GPIOB->ODR&= ~GPIO_ODR_ODR8;
		GPIOB->ODR&= ~GPIO_ODR_ODR2;
		GPIOB->ODR&= ~GPIO_ODR_ODR9;
	}
	else if (fireworksLocal == 2)
	{
		GPIOB->ODR|=GPIO_ODR_ODR2;
		GPIOB->ODR|=GPIO_ODR_ODR9;
		GPIOB->ODR|=GPIO_ODR_ODR3;
		GPIOB->ODR|=GPIO_ODR_ODR8;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR2;
		GPIOB->ODR&= ~GPIO_ODR_ODR9;
		GPIOB->ODR|=GPIO_ODR_ODR4;
		GPIOB->ODR|=GPIO_ODR_ODR7;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR3;
		GPIOB->ODR&= ~GPIO_ODR_ODR8;
		GPIOB->ODR|=GPIO_ODR_ODR5;
		GPIOB->ODR|=GPIO_ODR_ODR6;
		Delay(speed);
		GPIOB->ODR|=GPIO_ODR_ODR3;
		GPIOB->ODR|=GPIO_ODR_ODR8;
		GPIOB->ODR|=GPIO_ODR_ODR2;
		GPIOB->ODR|=GPIO_ODR_ODR9;
		Delay(speed);
		GPIOB->ODR&= ~GPIO_ODR_ODR5;
		GPIOB->ODR&= ~GPIO_ODR_ODR6;
		GPIOB->ODR&= ~GPIO_ODR_ODR4;
		GPIOB->ODR&= ~GPIO_ODR_ODR7;
		GPIOB->ODR&= ~GPIO_ODR_ODR3;
		GPIOB->ODR&= ~GPIO_ODR_ODR8;
		GPIOB->ODR&= ~GPIO_ODR_ODR2;
		GPIOB->ODR&= ~GPIO_ODR_ODR9;
		Delay(speed);
	}
};

int main() 
{ 
	initKeypad();
	initOutput();
	initIRQ();
	while(1)
	{
		if (CurrentMode == Reflection)
		{
			reflection();
		} 
		else if (CurrentMode == Diverging)
		{
			diverging();
		}
		else if (CurrentMode == Colliding)
		{
			colliding();
		}
	}
} 

void Firerun()
{
	if (fireworks == -1)
	{
		fireworks = 1;
	};
	if (speed == -1)
	{
		speed = 3;
	}
	
	printf("Fire = %d\n", fireworks);
	printf("Speed = %d\n", speed);
	
	switch (CurrentMode) 
	{
		case Reflection:
			printf("Current work mode: Reflection\n");
			break;
    case Diverging:
      printf("Current work mode: Diverging\n");
      break;
    case Colliding:
      printf("Current work mode: Colliding\n");
      break;
    default:
      printf("Unknown work mode\n");
      break;
	}
}

void EXTI0_IRQHandler(void) 
{  
	EXTI->PR = EXTI_PR_PR0; 
	
	if (fireworks == 1){
		fireworks = 2;
	}
	else {fireworks = 1;
	}
		Firerun();
		// снимаем флаг прерывания
		EXTI->PR = 1; 
	} 

void EXTI1_IRQHandler(void) 
{  
	EXTI->PR = EXTI_PR_PR1; 
	if (speed == 3){
		speed = 1;
	}
	else if (speed == 1){
		speed = 5;
	}
	else {speed = 3;}
		Firerun();
		EXTI->PR = 2; 
	
} 

void EXTI2_IRQHandler(void) 
{  
	EXTI->PR = EXTI_PR_PR2; 
	if (CurrentMode == Reflection){
		CurrentMode =Diverging;
	}
	else if (CurrentMode ==Diverging){
		CurrentMode =Colliding;
	}
	else {CurrentMode = Reflection;}
	Firerun();
  EXTI->PR = 3; 
} 
