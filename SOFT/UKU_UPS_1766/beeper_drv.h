#ifndef _BEEPER_DRV_	 //������, ���� ���� ����� �� ������

#define _BEEPER_DRV_	  //����������, ��� ���� ��������

#define BP 27
#define INIT_BP		LPC_GPIO1->FIODIR|=(1<<27)
#define BEEPER_ON	LPC_GPIO1->FIOSET|=(1<<27)
#define BEEPER_OFF	LPC_GPIO1->FIOCLR|=(1<<27) 


void beep(char,signed short,signed short,signed short,char);

void beeper(void);

#endif
