#ifndef _LED_BREAK_DRV_	 //читать, если файл ранее не считан

#define _LED_BREAK_DRV_	  //установить, что файл прочитан

#define LED_RED 26
#define INIT_LED_RED		LPC_GPIO0->FIODIR|=(1<<26)
#define LED_RED_ON	LPC_GPIO0->FIOSET|=(1<<26)
#define LED_RED_OFF	LPC_GPIO0->FIOCLR|=(1<<26)

#define LED_GREEN 25
#define INIT_LED_GREEN		LPC_GPIO0->FIODIR|=(1<<25)
#define LED_GREEN_ON	LPC_GPIO0->FIOSET|=(1<<25)
#define LED_GREEN_OFF	LPC_GPIO0->FIOCLR|=(1<<25)
 
void blink(char,signed short,signed short,signed short);

void blinker(void);

#endif
