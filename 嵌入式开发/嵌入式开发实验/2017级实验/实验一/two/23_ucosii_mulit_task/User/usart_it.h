/**
  ******************************************************************************
  * File Name          : usart_it.h
  * Description        : USATR driver & ISR code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 jkuang@BUPT
  *
  ******************************************************************************
  */

#ifndef   UASRT_IT
#define   UASRT_IT
#ifdef __cplusplus
		 extern "C" {
#endif

void USER_USART1_print(char *);
void Task_USART1_Creat(void);

void task_USART1 (void* p_arg);

void OS_CPU_USART1_IRQHandler(void);

#ifdef __cplusplus
}
#endif 
#endif  //UASRT_IT
