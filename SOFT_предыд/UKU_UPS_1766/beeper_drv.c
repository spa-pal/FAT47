#include "beeper_drv.h"
#include "main.h"
#include "LPC17xx.H"

/*
������������� �������, �.�. ������������� ������� 1= 10�� 100��
1�=100���
������:
beep(2,20,50,100,30)
beep(���-�� � �����,������������ ������,����� � �����,�������� ����� �����, ���� � ��� ���� �������)
*/
char quantity,restart=0,count_q,single;
signed short duration,pause,delay,timer_b;
signed short count_b,count_t;

void beep(char q,signed short d,signed short p,signed short dl,char t)
{
if (q!=quantity||d!=duration||p!=pause||dl!=delay)//���� ����� �������, �������� ������ � �������
	{
	quantity=q;
	duration=d;
	pause=p;
	delay=dl;
	timer_b=t*100;
	restart=1;
	}
}

void beeper (void)
{
	INIT_BP;						   //������������� �����
	if (restart)					   //��� ����� ������� ����� ���� ���������
		{
		BEEPER_OFF;
		count_q=1;
		count_b=0;
		count_t=0;
		restart=0;
		}
	else if (quantity)				  // ������� �� ������
		{
		if (count_b<duration)
			{
			BEEPER_ON;					//��� ���� �� ����� ����
			++count_b;
			}		    
		else if(count_q<quantity)		  //���� ����� �� ����� ��� 1
			{
			if(count_b<(duration+pause))
				{
				BEEPER_OFF; //���� ���� �� ����� �����
				++count_b;
				}
			else
				{
				count_b=0;			 	//�� ������
				++count_q;
				}					
			}
		else if(count_b<(duration+delay))
			{
			BEEPER_OFF;						//���� ����	�� ����� �������� �/� �������
			++count_b;
			}
		else
			{
			count_b=0;			 	//�� ������ ���� �����
			count_q=1;
			}					
		
		if(timer_b)
			{
			if(count_t++==timer_b) beep (0,0,0,0,0);
			}
		}
}
