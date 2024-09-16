/* 
 * Author: Mahmoud Ahmed 
 * Date: 16 Sep, 2024
 *
 * Target: PY32F002Ax5
 * Project name: Control LED Intensity with POT 
 * Description:
 * 
*/

#include "main.h"

void delay(uint32_t nTime)
{
		while(nTime--);
}

int main(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	
	GPIO_InitTypeDef led;
	led.Mode = GPIO_MODE_OUTPUT_PP;
	led.Pin = GPIO_PIN_1;
	led.Pull = GPIO_NOPULL;
	led.Speed = GPIO_SPEED_FREQ_LOW;
	led.Alternate = 0;
	
	HAL_GPIO_Init(GPIOA, &led);
	
	USART_HandleTypeDef bmHandle;
	bmHandle.Init.BaudRate = 9600;
	bmHandle.Init.WordLength = USART_WORDLENGTH_8B;
	bmHandle.Init.StopBits = USART_STOPBITS_1;
	bmHandle.Init.Parity = USART_PARITY_NONE;
	bmHandle.Init.Mode = USART_MODE_TX_RX;
	bmHandle.Init.CLKPolarity = USART_POLARITY_LOW;
	bmHandle.Init.CLKPhase = USART_PHASE_1EDGE;
	bmHandle.Init.CLKLastBit = USART_LASTBIT_DISABLE;
	bmHandle.Instance = USART1;
	
	HAL_USART_Init(&bmHandle);
	
	uint8_t data[6] = "Hello\n";
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		HAL_USART_Transmit(&bmHandle, data, 6, 5000);
		delay(0x3FFFF);
  }
}
