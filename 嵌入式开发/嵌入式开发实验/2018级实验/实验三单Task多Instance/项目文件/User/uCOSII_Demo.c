/**
  ******************************************************************************
  * File Name          : uCOSII_Demo.c
  * Description        : demo code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 jkuang@BUPT
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/


/* USER CODE BEGIN Includes */
#include	"uCOSII_Demo.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

APP_RECORD App_Record[APP_RECORD_NUM];

//DEMO_03: Timer test demo
#define DEMO_04

#ifdef DEMO_01
#define TASK1_PRIO    								11
#define TASK2_PRIO    								12

static OS_STK task1_stk[STK_SIZE_DEF];
static OS_STK task2_stk[STK_SIZE_DEF];

static void task1(void *p_arg);
static void task2(void *p_arg);
#endif //DEMO_01

#ifdef DEMO_02
#define TASK_SENDER_PRIO    					17
#define TASK_RECIVER_PRIO    					16

static OS_STK task_sender_stk[STK_SIZE_DEF];
static OS_STK task_reciver_stk[STK_SIZE_DEF];

static void task_sender(void *p_arg);
static void task_reciver(void *p_arg);

OS_EVENT *demo_semp;
#endif //DEMO_02

#ifdef DEMO_03
#define TASK_TMRTST_PRIO    					19
static OS_STK task_tmrtst_stk[STK_SIZE_DEF];
static void task_tmrtst(void *p_arg);
#endif //DEMO_03

// ****************************************** DEMO_04 ��������******************************************
#ifdef DEMO_04
#define TASK_TMRTST_PRIO    					19
static OS_STK LEDx_Task_stk[STK_SIZE_DEF];
static void LEDx_Task(void* p_arg);
#endif //DEMO_03

//============================================================
int User_App_Initial(void)
{
	int 	i;
	INT8U err;

	//BEEP off
	BEEP_OFF;
	
	//4 leds off
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;


	//Task record array initial
	for(i=0; i<APP_RECORD_NUM; i++)
	{
		APP_TQID(i) 	= 0;
		APP_TPRIO(i) = 0xFF;
	}

#if OS_TMR_EN > 0u
	APP_TPRIO(OS_TID_Timer) = OS_TASK_TMR_PRIO;  //Timer task record init
#endif

	//Message mem partition Init
	err = Msg_MemInit();
	if(err)
		return(err);
	
	//UART Send buffer init
	Uart_Sendbuf_Init();

	//task USART1 Create
	err = Task_USART1_Creat();
	if(err)
		return(err);
	
	//task KeyScan Create
	err = Task_KeyScan_Creat();
	if(err)
		return(err);


#ifdef DEMO_01
	OSTaskCreate(task1, (void*)0, &task1_stk[STK_SIZE_DEF-1], TASK1_PRIO);
	OSTaskCreate(task2, (void*)0, &task2_stk[STK_SIZE_DEF-1], TASK2_PRIO);
#endif //DEMO_01

#ifdef DEMO_02
	demo_semp = OSSemCreate(0);
	if(demo_semp == 0)
		return(255);
	
	err = OSTaskCreate(task_sender, (void*)0, &task_sender_stk[STK_SIZE_DEF-1], TASK_SENDER_PRIO);
	if(err)
		return(err);

  err = OSTaskCreate(task_reciver, (void*)0, &task_reciver_stk[STK_SIZE_DEF-1], TASK_RECIVER_PRIO);
	if(err)
		return(err);
#endif //DEMO_02

#ifdef DEMO_03
	err = OSTaskCreate(task_tmrtst, (void*)0, &task_tmrtst_stk[STK_SIZE_DEF-1], TASK_TMRTST_PRIO);
	if(err)
		return(err);
#endif //DEMO_03

	// ****************************��ʼDEMO04������LEDx_Task����*****************************************************
#ifdef DEMO_04
	err = OSTaskCreate(LEDx_Task, (void*)0, &LEDx_Task_stk[STK_SIZE_DEF - 1], TASK_TMRTST_PRIO);
	if (err)
		return(err);
#endif //DEMO_03
	return(0);
}

//============================================================
void USER_Print_Decimal(INT32U value)
{
	char* aStr;

	aStr = Uart_Sendbuf_Get();
	if(aStr)
	{
		sprintf((char*)aStr, "%d", value);
		USER_USART1_print(aStr);
	}
	else
		USER_USART1_print("^.^");
}

//============================================================
//static char aStr[16];
void USER_Print_OSIdleCtr(void)
{
//	static char aStr[16];	//ע�⣺�ٽ���Դ��
	char* aStr;

	aStr = Uart_Sendbuf_Get();
	if(aStr)
	{
		sprintf((char*)aStr, "[%08X]", OSIdleCtr);
		USER_USART1_print(aStr);
	}
	else
		USER_USART1_print("[..]");
}


#ifdef DEMO_01
//------------ DEMO 01 ----------------
//============================================================
static void task1(void *p_arg)
{
	USER_USART1_print("\n====Task1 Created====\n");

	while(1)  
	{	       
		USER_Print_OSIdleCtr();
		USER_USART1_print(":Task1\n");

		LED1_TOGGLE;
		OSTimeDlyHMSM(0,0,0,400);

  }
}

//============================================================
static void task2(void *p_arg)
{
	USER_USART1_print("\n====Task2 Created====\n");

	while(1)
	{
		USER_Print_OSIdleCtr();
		USER_USART1_print(":Task2\n");

		LED2_TOGGLE;
		BEEP_TOGGLE;
		OSTimeDly(OS_TICKS_PER_SEC);
//		OSTimeDlyHMSM(0,0,0,1000);
    
    }
}
#endif //DEMO_01

#ifdef DEMO_02
//------------ DEMO 02 ----------------
//#define PRINT_EN_DEMO02

//============================================================
static void task_sender(void *p_arg)
{
	INT32U task_active_cnt = 0;

	APP_TPRIO(APP_TID_sender) = TASK_SENDER_PRIO;

	USER_USART1_print("\n====Task Sender Created====\n");

	while(1)  
	{	       
		if(KEYSWITCH(1))	//key1 switch
		{
			LED1_TOGGLE;
		}
		if(OSSemPost(demo_semp))
			USER_USART1_print("Task Sender SEM-POST ERR!\n");

		task_active_cnt++;
#ifdef PRINT_EN_DEMO02
		USER_Print_OSIdleCtr();
		USER_USART1_print(" Task Sender active:");
		USER_Print_Decimal(task_active_cnt);
		USER_USART1_print("\n");
#endif
		OSTimeDlyHMSM(0,0,0,400);

  }
}

//============================================================
static void task_reciver(void *p_arg)
{
	INT8U  				err;
  GPIO_PinState bitstatus;
	INT32U 				task_active_cnt = 0;
	
	APP_TPRIO(APP_TID_receiver)= TASK_RECIVER_PRIO;

	USER_USART1_print("\n====Task Reciver Created====\n");

	while(1)
	{
		OSSemPend (demo_semp, 0, &err);
		if(err)
			USER_USART1_print("Task Reciver SEM-PEND ERR!\n");

		if(KEYSWITCH(2))	//key2 switch
		{
			bitstatus = LED1_READ;
			if(bitstatus == GPIO_PIN_RESET) //led2 set reverse state of led1 
			{
				LED2_OFF;
			}else{
				LED2_ON;
			}
//			if(KEYSWITCH(4))	//key4 switch
//				BEEP_TOGGLE;
		}

		task_active_cnt++;
#ifdef PRINT_EN_DEMO02
		USER_Print_OSIdleCtr();
		USER_USART1_print(" Task Reciver active:");
		USER_Print_Decimal(task_active_cnt);
		USER_USART1_print("\n");
#endif
	}
}
#endif //DEMO_02

#ifdef DEMO_03
//------------ DEMO 03 ----------------
#define PRINT_EN_DEMO03

static OS_TMR *tstTmr1; // һ�Ķ�ʱ��
static OS_TMR *tstTmr2; // ���ڼ�ʱ��


//��ʱ�����������msgQ
#define TASK_TMRTST_QSIZE		10
static void *TaskTmrtst_Qarray[TASK_TMRTST_QSIZE];


//============================================================
static void Tmr1CallbackFnct (void *p_arg)
{
/* Do something when timer #1 expires ʱ����1����ʱ��ȡ��ʩ */
	INT8U err;

	OSTmrStart(tstTmr1, &err);  //restart timer

	//send msg to tmetst task Q
	Msg_SendShort(MC_TMRTST_TMR1, OS_TID_Timer, APP_TID_tmrtest, 0, 0);
}

//============================================================
static void Tmr2CallbackFnct(void *p_arg)
{
/* Do something when timer #2 expires ��ʱ����2���ں��ȡ��ʩ */

	//send msg to tmetst task Q
	Msg_SendShort(MC_TMRTST_TMR2, OS_TID_Timer, APP_TID_tmrtest, 0, 0);
}


//============================================================
static void task_tmrtst(void *p_arg)
{
	INT8U 				err;
	MESSAGE_HEAD *msgP;
	INT8U 				beep_on = 1;			// ����������
	INT8U					beeptmr = 0;		// the timer beep followed
	INT32U				mcode = mcode;		// message code for print
	INT32U				msgcnt = 0;				// message recv counter for print

	//Create Q of timer test task
	APP_TQID(APP_TID_tmrtest) = 
							OSQCreate(&TaskTmrtst_Qarray[0], TASK_TMRTST_QSIZE);
	if(APP_TQID(APP_TID_tmrtest) == NULL)
	{
		APP_TPRIO(APP_TID_tmrtest) = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}

	//timer create
	tstTmr1 = OSTmrCreate((INT32U )5,
												(INT32U )0,
												(INT8U  )OS_TMR_OPT_ONE_SHOT,
												(OS_TMR_CALLBACK)Tmr1CallbackFnct,
												(void * )0,
												(INT8U *)"Tmr1",
												(INT8U *)&err);
	if(err)
	{
		OSQDel(APP_TQID(APP_TID_tmrtest),OS_DEL_ALWAYS,&err);
		APP_TQID(APP_TID_tmrtest) = NULL;
		APP_TPRIO(APP_TID_tmrtest) = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	
	tstTmr2 = OSTmrCreate((INT32U )0,
												(INT32U )2,
												(INT8U  )OS_TMR_OPT_PERIODIC,
												(OS_TMR_CALLBACK)LED_light,
												(void * )0,
												(INT8U *)"Tmr2",
												(INT8U *)&err);
	if(err)
	{
		OSTmrDel(tstTmr1,&err);
		OSQDel(APP_TQID(APP_TID_tmrtest),OS_DEL_ALWAYS,&err);
		APP_TQID(APP_TID_tmrtest) = NULL;
		APP_TPRIO(APP_TID_tmrtest) = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	
	OSTmrStart(tstTmr1, &err);
	if(err)
		return;
	OSTmrStart(tstTmr2, &err);
	if(err)
		return;


	APP_TPRIO(APP_TID_tmrtest) = TASK_TMRTST_PRIO;

	USER_USART1_print("\n====Task Timer Test Initialized====\n");

	while(1)  
	{	
		msgP = (MESSAGE_HEAD *)OSQPend(APP_TQID(APP_TID_tmrtest), 0, &err);

		// ��Ϣ�Ϸ��Լ��
		if(msgP->mRecvTsk != APP_TID_tmrtest)
		{
			Msg_MemPut(msgP);
			continue;
		}

		// ͨ��mCode������Ϣ����
		switch(msgP->mCode)
		{
			case MC_KEYx_SWITCH:
				{
				  // ��Ϣʵ������
					switch(msgP->mRecvInst)
					{
						case 3: //Key3����������ʱ�����ļ�
							beeptmr ^= 1;
							break;

						case 4:	//Key4��beep on/off key
							beep_on ^= 1;
							if(beep_on == 0){
								BEEP_OFF;
							}
							break;

						default:
							USER_USART1_print("!!! Invalid Key.\n");
							break;
					}
				}
				break;

			case MC_TMRTST_TMR1:
				LED3_TOGGLE;	//�л�LED3
				if((beep_on) && (beeptmr==0))
						BEEP_TOGGLE;
				break;

			case MC_TMRTST_TMR2:
				LED4_TOGGLE;	//toggle led4
				if((beep_on) && (beeptmr))
						BEEP_TOGGLE;
				break;

			default:
				USER_USART1_print("!!! Invalid mCode.\n");
				break;
		}

		mcode = msgP->mCode;
		//release msg mem
		Msg_MemPut(msgP);
//		msgP = NULL;

		msgcnt++;
#ifdef PRINT_EN_DEMO03
		USER_Print_OSIdleCtr();
		USER_USART1_print("Msg:");
		USER_Print_Decimal(mcode);
		USER_USART1_print(" Msgcnt:");
		USER_Print_Decimal(msgcnt);
		USER_USART1_print(":Task Timer Test\n");
#endif
  }
}

#endif //DEMO_03


#ifdef DEMO_04
//------------************** DEMO 04����ʵ�鵥�����ʵ��ʵ������ƺ���ʵ�� *********************----------------

// ����LED_timer
static OS_TMR* LED_timer[3]; 
// ����LED�Ƶ�״̬��
static int LED_state[3] = { 0, 0, 0 };
//��ʱ�����������msgQ
#define TASK_TMRTST_QSIZE		10
static void* TaskTmrtst_Qarray[TASK_TMRTST_QSIZE];


// ͨ��LED_num���ı��Ӧ��LED��״̬��
static void changeLED_state(int LED_num)
{
	LED_state[LED_num - 1] = (LED_state[LED_num - 1] + 1) % 4;
	switch (LED_state[LED_num - 1])
	{
	case 0:
		LED_timer[LED_num - 1]->OSTmrPeriod = 10; // ���ü�ʱ������Ϊ10
		break;
	case 1:	
		LED_timer[LED_num - 1]->OSTmrPeriod = 5; // ���ü�ʱ������Ϊ5
		break;
	default:
		break;
	}
}

//===================ͨ��LED�Ƶ�״̬���ı�LED�Ƶ���˸���===================================
static void LED1_light()
{
	if (LED_state[0] == 0 || LED_state[0] == 1) LED1_TOGGLE;  // LED����˸
	else if (LED_state[0] == 2) LED1_ON;                      // LED�Ƴ���
	else if (LED_state[0] == 3) LED1_OFF;                     // LED��Ϩ��
	return;
}

static void LED2_light()
{
	if (LED_state[1] == 0 || LED_state[1] == 1) LED2_TOGGLE;
	else if (LED_state[1] == 2) LED2_ON;
	else if (LED_state[1] == 3) LED2_OFF;
	return;
}

static void LED3_light()
{
	if (LED_state[2] == 0 || LED_state[2] == 1) LED3_TOGGLE;
	else if (LED_state[2] == 2) LED3_ON;
	else if (LED_state[2] == 3) LED3_OFF;
	return;
}
//==========================������==================================
static void LEDx_Task(void* p_arg)
{
	// �����Ϣָ��
	MESSAGE_HEAD*       msgP;
	INT8U 				err;

	//������Ϣ����
	APP_TQID(APP_TID_tmrtest) = OSQCreate(&TaskTmrtst_Qarray[0], TASK_TMRTST_QSIZE);
	if (APP_TQID(APP_TID_tmrtest) == NULL)
	{
		APP_TPRIO(APP_TID_tmrtest) = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}

	//��������LED��timer
	LED_timer[0] = OSTmrCreate((INT32U)5,
		(INT32U)10,
		(INT8U)OS_TMR_OPT_PERIODIC,
		(OS_TMR_CALLBACK)LED1_light,
		(void*)0,
		(INT8U*)"LED_Tmr1",
		(INT8U*)&err);

	LED_timer[1] = OSTmrCreate((INT32U)5,
		(INT32U)10,
		(INT8U)OS_TMR_OPT_PERIODIC,
		(OS_TMR_CALLBACK)LED2_light,
		(void*)0,
		(INT8U*)"LED_Tmr2",
		(INT8U*)&err);

	LED_timer[2] = OSTmrCreate((INT32U)5,
		(INT32U)10,
		(INT8U)OS_TMR_OPT_PERIODIC,
		(OS_TMR_CALLBACK)LED3_light,
		(void*)0,
		(INT8U*)"LED_Tmr3",
		(INT8U*)&err);

	OSTmrStart(LED_timer[0], &err);
	OSTmrStart(LED_timer[1], &err);
	OSTmrStart(LED_timer[2], &err);


	APP_TPRIO(APP_TID_tmrtest) = TASK_TMRTST_PRIO;
	USER_USART1_print("\n====Task Timer Test Initialized====\n");

	while (1)
	{
		msgP = (MESSAGE_HEAD*)OSQPend(APP_TQID(APP_TID_tmrtest), 0, &err);

		// ��Ϣ�Ϸ��Լ��
		if (msgP->mRecvTsk != APP_TID_tmrtest)
		{
			Msg_MemPut(msgP);
			continue;
		}

		// ���ݽ��յĵİ�����Ϣ���ı��Ӧ��LEDx��״̬��
		switch (msgP->mRecvInst)
		{
		case 1:
			changeLED_state(1);
			break;

		case 2:
			changeLED_state(2);
			break;

		case 3:
			changeLED_state(3);
			break;

		case 4:
			// �ر�LED1~3 ��֤�Ƶ���˸һ�¡�
			LED1_OFF;
			LED2_OFF;
			LED3_OFF;

			// ����LED1~3��״̬��Ϊ0
			LED_state[0] = 0;  
			LED_state[1] = 0;  
			LED_state[2] = 0;  

			// ��������ʱ������
			LED_timer[0]->OSTmrPeriod = 10;
			LED_timer[1]->OSTmrPeriod = 10;
			LED_timer[2]->OSTmrPeriod = 10;
			break;

		default:
			USER_USART1_print("!!! Invalid Key.\n");
			break;
		}

		//release msg mem
		Msg_MemPut(msgP);
	}
}

#endif //DEMO_03

/************************ (C) COPYRIGHT jkuang@BUPT *****END OF FILE****/
