#include "led_break_drv.h"
#include "main.h"
#include "LPC17xx.H"

/*
������������� �������, �.�. ������������� ������� 1= 10�� 100��
1�=100���
������	blink(2,20,50,100)
		blink(���-�� � �����,������������ ������,����� � �����,�������� ����� �����)
*/
char b_quantity,b_restart=0,b_count_q;
signed short b_duration,b_pause,b_delay;
signed short b_count_b;

void blink(char q,signed short d,signed short p,signed short dl)
{
if (q!=b_quantity||d!=b_duration||p!=b_pause||dl!=b_delay)//���� ����� �������, �������� ������ � �������
	{
	b_quantity=q;
	b_duration=d;
	b_pause=p;
	b_delay=dl;
	b_restart=1;
	}
}

void blinker (void)
{
	INIT_LED;						   //������������� �����
	if (b_restart)					   //��� ����� ������� ����� ���� ���������
		{
		LED_OFF;
		b_count_q=1;
		b_count_b=0;
		b_restart=0;
		}
	else if (b_quantity)				  // ������� �� ������
		{
		if (b_count_b<b_duration)
			{
			LED_ON;					//��� ���� �� ����� ����
			++b_count_b;
			}		    
		else if(b_count_q<b_quantity)		  //���� ����� �� ����� ��� 1
			{
			if(b_count_b<(b_duration+b_pause))
				{
				LED_OFF; //���� ���� �� ����� �����
				++b_count_b;
				}
			else
				{
				b_count_b=0;			 	//�� ������
				++b_count_q;
				}					
			}
		else if(b_count_b<(b_duration+b_delay))
			{
			LED_OFF;						//���� ����	�� ����� �������� �/� �������
			++b_count_b;
			}
		else
			{
			b_count_b=0;			 	//�� ������ ���� �����
			b_count_q=1;
			}					
		}
}
