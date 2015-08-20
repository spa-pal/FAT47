#include "button_drv.h"
#include "main.h"
#include "LPC17xx.H"

unsigned long but=0;
char but_acc=butOFF,but_i=0,but_ii=0,LP,butt_on;

void button_on(void)
{

LPC_GPIO1->FIODIR&=~BUT_MASK;
LPC_PINCON->PINMODE3&=~(0x3f<<12);
#if(BUT0<16)
	{
	LPC_PINCON->PINMODE3&=~(1<<(BUT0*2))&~(1<<((BUT0*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINMODE3&=~(1<<((BUT0-16)*2))&~(1<<(((BUT0-16)*2)+1));
	}
#endif
#if(BUT1<16)
	{
	LPC_PINCON->PINMODE3&=~(1<<(BUT1*2))&~(1<<((BUT1*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINMODE3&=~(1<<((BUT1-16)*2))&~(1<<(((BUT1-16)*2)+1));
	}
#endif
#if(BUT2<16)
	{
	LPC_PINCON->PINMODE3&=~(1<<(BUT2*2))&~(1<<((BUT2*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINMODE3&=~(1<<((BUT2-16)*2))&~(1<<(((BUT2-16)*2)+1));
	}
#endif

//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();

but=LPC_GPIO1->FIOPIN&(7<<BUT0);	  // ������ 3 ���� � �����
//but=LPC_GPIO1->FIOPIN|(~(1UL<<BUT0))&(~(1UL<<BUT1))&(~(1UL<<BUT2))&(~(1UL<<BUT3))&(~(1UL<<BUT4));

but>>=BUT0;		// ����������� � ������� ���

if(but!=butOFF|but_i!=0)			// ���� �����-���� �� ������ ������ ���� ��� ���� ������� ������
	{						
	//if (but_i==0) but_acc=but; 	//��� ������ ������ ���������� ������� ������
	but_i++;
	if (but_i>=10)				   // ���� 100 �� �� ������� ����� ���� ����� ������ ��������� 
		{
		if (but_i==10) but_acc=but;		   // ����� �������� �� ������� ���������� ������� ������
		if (but==butOFF|but_ii!=0)		   // ������������� ������� ������ ���� ���� ��� ����� �������
			{
			if (but_ii==0)				  // ��� ������ ������ 
				{
				if(!LP) butt_on=but_acc;  // ��������� ��� ���� �������� �������? ���� �� ���� �������� �������
				but_ii=but_i;			  // �������� ������ 100 �� �� �������
				}
			if (but_i>=but_ii+10)		  // ������� 100 �� �� �������
				{
				but_i=0;				  //����� 
				but_ii=0;
				LP=0;
				}
			}
		else if (but_i>=50)				// ����� �������� ��������� 500��
			{
				butt_on=but_acc+LongPush;	 // ��������� ������� �������
				but_i=11;
				LP=1;				   		 // ��������� ����� �� ������� �������
			}
		}
	}






}




