#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "tm4c123gh6pm.h"

void RedTask(void);
void BlueTask(void);

void Portf_init(void);

int main(void){
	
	Portf_init();

	xTaskCreate( RedTask,"rt", 200, NULL, 1, NULL );
	xTaskCreate( BlueTask,"rt", 200, NULL, 1, NULL );
	vTaskStartScheduler();
	
	while(1){
		
	}
	
}

void Portf_init(void){
	SYSCTL_RCGCGPIO_R|=0x20;
  while((SYSCTL_PRGPIO_R&0x20)==0){};
  GPIO_PORTF_LOCK_R=0x4C4F434B;
  GPIO_PORTF_CR_R=0x0F;
  GPIO_PORTF_DIR_R=0x0F;
  GPIO_PORTF_PUR_R=0x01;
  GPIO_PORTF_DEN_R=0x0F;
}

void RedTask(void){
	

	while(1){
		GPIO_PORTF_DATA_R^= 0x02;
	
		vTaskDelay( 1000 / portTICK_RATE_MS );
	}
}
void BlueTask(void){
	

	while(1){
		GPIO_PORTF_DATA_R^= 0x04;
	
		vTaskDelay( 2000 / portTICK_RATE_MS );
	}
}

void vApplicationIdleHook( void )
{
	GPIO_PORTF_DATA_R^= 0x08;
}

