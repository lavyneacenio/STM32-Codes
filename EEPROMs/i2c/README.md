# Escreva e leia uma EEPROM I2C com STM32

**Configuração dos pinos:**
- Serial Clock (SCL)
- Serial Data (SDA) 
- Os endereços do dispositivo (A2, A1, A0). (são pinos de entrada para definir o endereço do dispositivo.)
- Write Protect (WP)
- Fonte de alimentação do dispositivo (VCC)
- Terra (GND)

Configure o I2C1 como no exemplo abaixo. Vai operar no modo polling.
![image](https://github.com/Well-IDESCO/STM32-Codes/assets/135154280/6b64874d-bac3-4f8e-b8d8-dfe535b6efb6)

Selecione Debug Serial Wire em SYS, para isso clique em System Core (no canto superior direito) e depois selecione SYS. Marque “Serial Wire”.
![image](https://github.com/Well-IDESCO/STM32-Codes/assets/135154280/73093ac8-8a9c-4afb-be77-e689027b9e90)

Selecione "Internal Clock" como fonte de relógio no periférico TIM2. Para fazer isso, clique em Timers e selecione TIM2. Agora vá para "Clock Source" e selecione no menu suspenso “Internal Clock”.

![image](https://github.com/Well-IDESCO/STM32-Codes/assets/135154280/fc5c8025-dd6d-4e72-84e5-b573c3ad7ba1)

Selecione Timers -> TIM2 e altere o Prescaler para 16000 e o Counter Period para 1000.

![image](https://github.com/Well-IDESCO/STM32-Codes/assets/135154280/74a6b12e-db72-47cc-9259-9cb6f864aafe)


Por último no CubeMX, cheque se os sinais "SYS_SWDIO", "TCK", "SDA I2C1" e "SCL I2C1" estão alocados em pinos. (Não necessariamente nos mesmos pinos que no exemplo abaixo.)
![image](https://github.com/Well-IDESCO/STM32-Codes/assets/135154280/a49cc111-bf14-49a7-85ec-6c0cec2b05ec)

Salve para gerar o código.
![image](https://github.com/Well-IDESCO/STM32-Codes/assets/135154280/a44ca6b5-7c5d-493c-8e8e-2b87f21abdb5)

## Alterações no código:

Vamos incluir a biblioteca HAL em nosso programa.

    /* Includes ------------------------------------------------------------------*/
    #include "main.h"
    #include "stm32g0xx_hal.h"
    
##### ATENÇÃO

Note que como estou utilizando uma placa da família g0, o meu "#include" é "stm32g0xx_hal.h". Entretanto, outras famílias irão usar outro "#include".
(Por exemplo: a placa "NUCLEO-L053R8", usaria o "#include" "stm32l0xx_hal.h")

