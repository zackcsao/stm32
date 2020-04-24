/*********************************************************************
*
*	Copyright (c) dreamczf@aliyun.com
*	All rights reserved.
*
*      Filename:	system_clock.c
*      Abstract:	��Ҫ�����ļ�������
*
*      Filename:	system_clock.c
*        Author:	caozhaofei
*       Version:	0.0.1
*          Date:	2017-11-07 10:41:17
*   Description:	�޸�˵��
*
*
*********************************************************************/

#include "system_clock.h"
#include "stm32f2xx_ll_rcc.h"
#include "stm32f2xx_ll_system.h"
#include "stm32f2xx_ll_pwr.h"
#include "stm32f2xx_ll_bus.h"
#include "stm32f2xx_ll_utils.h"
#include "stm32f2xx_ll_cortex.h"


void system_clock_init(void)
{
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	NVIC_SetPriorityGrouping(3);
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);

	if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_4){
		while(1);//Error_Handler();  
	}

	LL_RCC_HSE_Enable();
	LL_PWR_EnableBkUpAccess();

	/* Wait till HSE is ready */
	while(LL_RCC_HSE_IsReady() != 1);

	LL_RCC_LSI_Enable();

	/* Wait till LSI is ready */
	while(LL_RCC_LSI_IsReady() != 1);
	LL_PWR_EnableBkUpAccess();
	LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
	
	LL_RCC_EnableRTC();
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 240;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 5;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);
//	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 240, LL_RCC_PLLP_DIV_2);
//	LL_RCC_PLL_Enable();

	/* Wait till PLL is ready */
	while(LL_RCC_PLL_IsReady() != 1);

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	/* Wait till System clock is ready */
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);
	
	LL_Init1msTick(120000000);
	LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	LL_SetSystemCoreClock(120000000);
	LL_SYSTICK_EnableIT();

}

void system_tick_init(void)
{
	SysTick_Config(120000000);
}
static uint32_t _msec = 0;

void SysTick_Handler(void)
{
	_msec++;
}

uint32_t HAL_GetTick(void)
{
	return _msec;
}
