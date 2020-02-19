/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include <stdlib.h>
#include <time.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int snake[1000][2];
int bean[2]={120,70};
int stone[2]={100,100};
int direction = 0;
int speed=100;
int tail = 3;
int last_direction;
int t=0;
uint32_t score =0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void reset_array(int snake[][2],int len){
	LCD_Fill(snake[0][0],snake[0][1],snake[0][0]+10,snake[0][1]+10,RED);
	LCD_Fill(snake[len][0],snake[len][1],snake[len][0]+10,snake[len][1]+10,BACK_COLOR);
	for (int i=len;i>0;i--){
		snake[i][0]=snake[i-1][0];
		snake[i][1]=snake[i-1][1];
	}
}


void CreateStone(){
	LCD_Fill(stone[0],stone[1],stone[0]+10,stone[1]+10,BACK_COLOR);
	int rands;
	srand(score);
	int x = 30+10*(rand()%18);
	int y = 50+10*(rand()%18);
	int right = 1;
	while(right == 1){
	right = 0;
	for(int i = 1 ;i<tail;i++){
		if((snake[i][0] == x & snake[i][1] == y)||(bean[0]==x&bean[1]==y)){
			right = 1;
			//srand((unsigned)time(NULL));
			x = 30+10*(rand()%18);
			y = 50+10*(rand()%18);
			break;
		}
	}
	}
	stone[0] = x;
	stone[1] = y;
	LCD_Fill(stone[0],stone[1],stone[0]+10,stone[1]+10,WHITE);

}

void CreateBean(){
	LCD_Fill(bean[0],bean[1],bean[0]+10,bean[1]+10,BACK_COLOR);
	int rands;
	srand(score);
	int x = 30+10*(rand()%18);
	int y = 50+10*(rand()%18);
	int right = 1;
	while(right == 1){
	right = 0;
	for(int i = 1 ;i<tail;i++){
		if((snake[i][0] == x & snake[i][1] == y)||(stone[0]==x&stone[1]==y)){
			right = 1;
			//srand((unsigned)time(NULL));
			x = 30+10*(rand()%18);
			y = 50+10*(rand()%18);
			break;
		}
	}
	}
	bean[0] = x;
	bean[1] = y;
	LCD_Fill(bean[0],bean[1],bean[0]+10,bean[1]+10,GREEN);

}



void add_one_node(){
    LCD_Fill(bean[0],bean[1],bean[0]+10,bean[1]+10,RED);
    for (int i=tail+1;i>0;i--){
        snake[i][0]=snake[i-1][0];
        snake[i][1]=snake[i-1][1];
    }
    snake[1][0]=bean[0];
    snake[1][1]=bean[1];
    tail++;
}

int check_gameover(){
    if (snake[0][0]==10 | snake[0][0]==220 | snake[0][1]==40 | snake[0][1]==280 | (snake[0][0]==stone[0] & snake[0][1]==stone[1])){
        return 1;
    }
    for (int i=1;i<tail;i++){
        if(snake[0][0]==snake[i][0]& snake[0][1]==snake[i][1]){
            return 1;
        }
    }
    return 0;
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t x = 120;
  BACK_COLOR = BLACK;
  LCD_Clear(BACK_COLOR);
  LCD_Fill(x, x, x+10, x+30, RED);
  snake[0][0] = x;
  snake[0][1] = x-10;
  snake[1][0] = x;
  snake[1][1] = x;
  snake[2][0] = x;
  snake[2][1] = x+10;
  snake[3][0] = x;
  snake[3][1] = x+20;
  LCD_Fill(120, 70, 130, 80, GREEN);
  POINT_COLOR = WHITE;
  LCD_ShowString(10, 10, 200, 24, 24, (uint8_t*) "Score:");
  LCD_Fill(10, 40, 230, 50, CYAN);
  LCD_Fill(10, 40, 20, 290, CYAN);
  LCD_Fill(220,40, 230,290, CYAN);
  LCD_Fill(10, 280, 230, 290,  CYAN);
  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
  while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  t++;
	LCD_ShowNum(100,10,score,4,24);
	switch (direction){
	case 0:
		snake[0][1] = snake[1][1] - 10;
		break;
	case 1:
		snake[0][0] = snake[1][0] + 10;
		break;
	case 2:
		snake[0][1] = snake[1][1] + 10;
		break;
	case 3:
		snake[0][0] = snake[1][0] - 10;
		break;
	}

	if(snake[0][0]==snake[1][0]&&snake[0][1]==snake[1][1]){
		switch (last_direction){
			case 0:
				snake[0][1] = snake[1][1] - 10;
				break;
			case 1:
				snake[0][0] = snake[1][0] + 10;
				break;
			case 2:
				snake[0][1] = snake[1][1] + 10;
				break;
			case 3:
				snake[0][0] = snake[1][0] - 10;
				break;
			}
	}

	if(check_gameover()==1){
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		HAL_Delay(100);
		break;
	}
	if(snake[0][0] == bean[0] & snake[0][1] == bean[1]){
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(50);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(50);
//		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//		HAL_Delay(100);
//		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//		HAL_Delay(100);
//		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//		HAL_Delay(100);
//		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//		HAL_Delay(100);
		add_one_node();
		score+=10;
		CreateBean();
		CreateStone();
		t=0;
	}
	reset_array(snake,tail);
	score ++;
	if	(score>800){
		speed = 10;
	}else if (score>500){
		speed = 20;
	}else if(score>400){
		speed = 30;
	}else if(score>300){
		speed = 40;
	}else if(score>200){
		speed = 60;
	}else if(score>100){
		speed = 80;
	}
	if(t==40){
		t=0;
		CreateBean();
		CreateStone();
	}
	HAL_Delay(speed);


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	HAL_Delay(100);

	switch (GPIO_Pin) {
	case KEY0_Pin:
	 if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET) {
		 last_direction=direction;
		if(direction == 3){
			direction = 0;
		}else{
			direction++;
		}
	 }
	 break;
	case KEY1_Pin:
	 if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) {
		 last_direction=direction;
			if(direction == 0){
				direction = 3;
			}else{
				direction--;
			}
	 }
	 break;
	case KEY_WK_Pin:
	 if (HAL_GPIO_ReadPin(KEY_WK_GPIO_Port, KEY_WK_Pin) == GPIO_PIN_SET) {
	 }
	 break;
	default:
	 break;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
