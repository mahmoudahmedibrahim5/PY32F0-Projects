/* 
 * Author: Mahmoud Ahmed 
 * Date: 20 Aug, 2024
 *
 * Target: PY32F002Ax5
 * Project name: LED Remote Control
 * Description: Controlling LED using Bluetooth Module 
*/

#include <py32f0xx.h>

void RCC_init(void);
void GPIO_init(void);
void USART_init(void);
void USART_sendData(uint8_t data);
void USART_receiveData(uint8_t* data);
void delay(uint32_t nTime);

int main(void)
{
		/* Initialization */
		RCC_init();
		GPIO_init();
		USART_init();
		
		uint8_t ledState = 1;
		uint8_t data;
		uint8_t onMsg[3] = "ON\n";
		uint8_t offMsg[4] = "OFF\n";

		while(1)
		{
			USART_receiveData(&data);
			if(data == 'N' || data == 'n')
				ledState = 1;
			else if(data == 'F' || data == 'f')
				ledState = 0;
			
			if(ledState)
			{
				/* Set The PA1 pin, Turn on the LED */
				SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS1);
				
				/* Send On Message */
				for(uint8_t i = 0; i < 3; i++)
					USART_sendData(onMsg[i]);
			}
			
			else
			{
				/* Reset The PA1 pin, Turn off the LED */
				SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
				
				/* Send Off Message */
				for(uint8_t i = 0; i < 4; i++)
					USART_sendData(offMsg[i]);
			}
			
			delay(0x3FFFF);
		}
}

void RCC_init(void)
{
		/* RCC Clock enable for GPIOA and USART1 */
		SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);
		SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOFEN);
		SET_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN);
}

void GPIO_init(void)
{
		/* Set Pin PA1 as OUTPUT (MODE = 01) */
		MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE1_1, GPIO_MODER_MODE1_0);
	
		/* Set Pin PF0 and PF1 as Rx and Tx */
		MODIFY_REG(GPIOF->MODER, GPIO_MODER_MODE0_0, GPIO_MODER_MODE0_1);  	// Set PF0 Mode as Alternate Function
		MODIFY_REG(GPIOF->MODER, GPIO_MODER_MODE1_0, GPIO_MODER_MODE1_1);		// Set PF1 Mode as Alternate Function


		GPIOF->AFR[0] |= (1 << 3);	// Set PF0 to AF8
		GPIOF->AFR[0] |= (1 << 7);	// Set PF1 to AF8
}

void USART_init(void)
{
		USART1->CR1 |= (1 << 13); // USART Enable
		USART1->BRR = 0x00000341U; //0x1D4C;	// Baud Rate 9600
		USART1->CR1 |= (1 << 3); 	// Transmission Enable
		USART1->CR1 |= (1 << 2); 	// Receiving Enable
}

void USART_sendData(uint8_t data)
{
		while(!(USART1->SR & (1<<7)));
		USART1->DR = data;
}

void USART_receiveData(uint8_t* data)
{
		while(!(USART1->SR & (1<<5)));
		*data = USART1->DR;
}

void delay(uint32_t nTime)
{
		while(nTime--);
}
