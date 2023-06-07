### BIBLIOTECAS
https://blog.naver.com/eziya76/221188701172

Dentro da pasta Core/Inc, cole o arquivo **"fatfs_sd.h"**.

Dentro da pasta Core/Src, cole o arquivo **"fatfs_sd.c"**.

### MUDANÇAS NO CÓDIGO
	
ATENÇÃO, dentro do arquivo **"fatfs_sd.c"** deve-se fazer a mudança do primeiro **"#include"** para a familia certa do chip que você estiver utilizando, como no exemplo abaixo:
~~~C
#include "stm32f1xx_hal.h"
~~~
Para
~~~C
#include "stm32g0xx_hal.h"
~~~
	
No arquivo **"stm32xx_it.c", localizado na pasta Core/Src**, faça as seguintes mudanças:

~~~C
/* USER CODE BEGIN 0 */
extern uint16_t Timer1, Timer2;
/* USER CODE END 0 */
~~~ 
 
 E
 
~~~C
/* USER CODE BEGIN SysTick_IRQn 0 */
if(Timer1 > 0)
	Timer1--;
if(Timer2 > 0)
	Timer2--;
/* USER CODE END SysTick_IRQn 0 */
~~~

Já no arquivo **"user_diskio.c", localizado na pasta FATFS/Target Folder**, faça as seguintes mudanças:

~~~C
/* USER CODE BEGIN INIT */
    // Stat = STA_NOINIT; **Apague ou comente esta linha.**
    // return Stat;  **Apague ou comente esta linha.**
	return SD_disk_initialize(pdrv);
/* USER CODE END INIT */
~~~

~~~C
/* USER CODE BEGIN STATUS */
    // Stat = STA_NOINIT; **Apague ou comente esta linha.**
    // return Stat; **Apague ou comente esta linha.**
	return SD_disk_status(pdrv);
/* USER CODE END STATUS */
~~~

~~~C
/* USER CODE BEGIN READ */
    // return RES_OK; **Apague ou comente esta linha.**
	return SD_disk_read(pdrv, buff, sector, count);
/* USER CODE END READ */
 ~~~
 
 ~~~C
/* USER CODE HERE */
    // return RES_OK; **Apague ou comente esta linha.**
	return SD_disk_write(pdrv, buff, sector, count);
/* USER CODE END WRITE */
 ~~~
 
 ~~~C
 /* USER CODE BEGIN IOCTL */
    // DRESULT res = RES_ERROR; **Apague ou comente esta linha.**
    // return res; **Apague ou comente esta linha.**
    return SD_disk_ioctl(pdrv, cmd, buff);
/* USER CODE END IOCTL */
 ~~~
 
### MANIPULANDO O CARTÃO SD
#### As seguintes mudanças devem ser feitas no arquivo **"main.c"**.
##### Para criar um arquivo de texto no SDCARD:
&nbsp;

 ~~~C
/* USER CODE BEGIN PD */
FATFS fs;
FIL fil;
/* USER CODE END PD */
 ~~~
 E
~~~C
 /* USER CODE BEGIN 2 */
  HAL_Delay(500);
  f_mount(&fs, "", 0);
  f_open(&fil, "write.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
  f_lseek(&fil, fil.fsize);
  f_puts("Hello from Nizar\n", &fil);
  f_close(&fil);
/* USER CODE END 2 */
~~~
 
##### Para checar o tamanho total e o espaço livre no SDCARD:
&nbsp;
~~~C
/* USER CODE BEGIN PD */
FATFS *pfs;
DWORD fre_clust;
uint32_t totalSpace, freeSpace;
/* USER CODE END PD */
~~~
E
~~~C
  /* USER CODE BEGIN 2 */
  f_getfree("", &fre_clust, &pfs);
  totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
  freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);
  /* USER CODE END 2 */
~~~
##### Para ler arquivos do SDCARD:
&nbsp;
~~~C
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */
/* USER CODE BEGIN PD */
char buffer[100];
/* USER CODE END PD */
~~~
E
~~~C
  /* USER CODE BEGIN 2 */
  f_open(&fil, "read.txt", FA_READ);
  // Lê linha por linha, até o final.
  while(f_gets(buffer, sizeof(buffer), &fil))
  {
    // Pode usar o buffer para algo útil.
    memset(buffer,0,sizeof(buffer));
  }
  f_close(&fil);
  /* USER CODE END 2 */
~~~











