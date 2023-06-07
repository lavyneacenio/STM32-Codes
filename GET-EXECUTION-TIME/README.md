# Exemplo de medição de tempo de execução.

Na perspectiva do CubeMX, abra Timers e selecione TIM16. Defina o prescaler (PSC) para 79. Vou escrever “80 - 1” para mostrar que um valor prescaler de 79 na verdade significa usar um divisor de relógio ou 80. O prescaler está desligado em 1 porque é baseado em 0: um valor PSC de “0” significa usar um prescaler (divisor de clock) de 1.

![Imagem de Exemplo 1](https://github.com/Well-IDESCO/STM32-Codes/assets/135154280/e9457d70-0085-4533-8d27-635dc91bced3)

Salve para gerar o código e abra **"main.c"**. Lá, para que possamos usar **"sprintf"** escreva:
~~~C
/ * USER CODE BEGIN Includes * / 
#include <stdio.h> 
/ * USER CODE END Includes * / 
~~~

 Altere **"main()"**" para que possamos medir o tempo que leva para executar a função **"HAL_Delay(50)"**. 
 
 Aqui está a aparência do código:
 (Observe que deixei tudo de fora depois de main(), pois deveria ter sido gerado pelo CubeMX).
 
 ~~~C
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
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
TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM16_Init(void);
/* USER CODE BEGIN PFP */

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
  char uart_buf[50];
  int uart_buf_len;
  uint16_t timer_val;

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
  MX_USART2_UART_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */

  // Say something
  uart_buf_len = sprintf(uart_buf, "Timer Test\r\n");
  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);

  // Starta o timer
  HAL_TIM_Base_Start(&htim16);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // Obtém o tempo atual (microssegundos) 
    timer_val = __HAL_TIM_GET_COUNTER(&htim16);

    // Espera por 50 ms
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    // Obtém o tempo decorrido
    timer_val = __HAL_TIM_GET_COUNTER(&htim16) - timer_val;

    // Mostra o tempo decorrido 
    uart_buf_len = sprintf(uart_buf, "%u us\r\n", timer_val);
    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);

    // Esperar 1seg de novo, pra não encher o terminal
    HAL_Delay(1000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* Resto do MAIN.C */
 ~~~
 
 Observe que o método apresentado nos permite medir o tempo entre os eventos, mesmo que o cronômetro seja interrompido. No entanto, não funcionará se a diferença entre os timestamps for maior que 65.536 microssegundos (o valor máximo que nosso cronômetro pode contar).