# Exemplo de interrupção com timer.

É uma interrupção simples. Quando o timer atingir seu valor máximo, ele retornará a 0 e acionará uma interrupção.

Para isso, definiremos o prescaler do Timer 16 para 8000, de modo que ele funcione a uma taxa de 10 kHz. Em seguida, definiremos seu valor máximo como 10.000 (na verdade, definiremos como 9.999, pois queremos que a interrupção seja acionada no rollover) para que demore 1 segundo para atingir o valor máximo. 

Cada vez que a interrupção ocorrer, o LED vai ser alternado.

##### No CubeMX, altere o período do contador para 9.999 (“10000 - 1”).

![img2](https://github.com/Well-IDESCO/STM32-Codes/assets/135154280/faca7e69-5884-44d7-9baf-9dc1613d8e26)

##### Clique na guia **"NVIC Settings"** e ative a interrupção de atualização TIM1 e a configuração de interrupção global TIM16.

![imgTIMER](https://github.com/Well-IDESCO/STM32-Codes/assets/135154280/bd603f87-8dd0-4aa1-93db-5a5e18c592ca)

Salve para gerar o código.

Em **"main.c"**, altere a função **"main()"**" para o seguinte:

~~~C
  * @brief O ponto de entrada do aplicativo. 
  * @retval int 
  * / 
int main(void) 
{ 
  / * USER CODE BEGIN  1 * / 

  / * USER CODE END  1 * / 

  / * MCU Configuration------------------ --------------------------------------* / 

  / * Reset de todos os periféricos, Inicializa o Flash interface e o Systick. * / 
  HAL_Init(); 

  / * USER CODE BEGIN Init * / 

  / * USER CODE END Init * /

  / * Configurar o relógio do sistema * / 
  SystemClock_Config(); 

  / * USER CODE BEGIN SysInit * / 

  / * USER CODE END SysInit * / 

  / * Inicializar todos os periféricos configurados * / 
  MX_GPIO_Init(); 
  MX_USART2_UART_Init(); 
  MX_TIM16_Init(); 
  / * USER CODE BEGIN  2 * / 

  / / Iniciar cronômetro 
  HAL_TIM_Base_Start_IT(&htim16); 

  / * USER CODE END  2 * / 

  / * Loop infinito * / 
  /* USER CODE BEGIN WHILE * / 
  while (1) 
  { 
    / * USER CODE END WHILE * / 

    / * USER CODE BEGIN  3 * / 
  } 
  / * USER CODE END  3 * / 
}
~~~

Observe que a única coisa que temos no **"main()"** agora é **"HAL_TIM_Base_Start_IT(&htim16)"**, que inicia o cronômetro no modo de interrupção. O while está em branco. O blink vai ser manipulado por interrupções.

**Mais abaixo, em "/* USER CODE BEGIN 4 */", adicione o seguinte:**
~~~C


//cronometro acabou
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) 
{ 
  // Verifique qual versão do cronômetro acionou este retorno de chamada e alterne o LED 
  if (htim == &htim16 ) 
  { 
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); 
  } 
} 

~~~



