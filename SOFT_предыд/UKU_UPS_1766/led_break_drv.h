#ifndef _LED_BREAK_DRV_	 //������, ���� ���� ����� �� ������

#define _LED_BREAK_DRV_	  //����������, ��� ���� ��������

#define LED 26
#define INIT_LED		LPC_GPIO0->FIODIR|=(1<<26)
#define LED_ON	LPC_GPIO0->FIOSET|=(1<<26)
#define LED_OFF	LPC_GPIO0->FIOCLR|=(1<<26) 
void blink(char,signed short,signed short,signed short);

void blinker(void);

#endif
