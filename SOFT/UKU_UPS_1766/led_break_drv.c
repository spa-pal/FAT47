#include "led_break_drv.h"
#include "beeper_drv.h"
#include "main.h"
#include "LPC17xx.H"




void led_beep (void){
	if(rejim_avar_led==0){
		switch(rejim_led){
		case 1: {  // ������ �� ����, ��� �� �����������
			LED_RED_OFF;
			LED_GREEN_ON;
		break;}
		case 2: {
			LED_RED_ON;
			LED_GREEN_ON;
		break;}
		default:{
			LED_RED_OFF;
			LED_GREEN_OFF;
		}
		}// end switch(rejim_led){
	}
	else {
		switch(rejim_avar_led){
		case 1: {
			  if(count_rejim_led==1){
			  	LED_GREEN_OFF;
				LED_RED_ON;				
			  }
			  else if(count_rejim_led==20){
			  	if(rejim_led==1){
					LED_RED_OFF;
					LED_GREEN_ON;
				}
				else if(rejim_led==2){
					LED_RED_ON;
					LED_GREEN_ON;
				}
			 }
			 else if(count_rejim_led==40){
			  	LED_GREEN_OFF;
				LED_RED_ON;				
			}
			else if(count_rejim_led>60){
				if(rejim_led==1){
					LED_RED_OFF;
					LED_GREEN_ON;
				}
				else if(rejim_led==2){
					LED_RED_ON;
					LED_GREEN_ON;
				}
				if(count_rejim_led>250) count_rejim_led=0;  
			}

		break;}
		case 2: {
			LED_GREEN_OFF;
			LED_RED_ON;
		break;}
		case 3: {
			if(count_rejim_led==1){
			  	LED_GREEN_OFF;
				LED_RED_ON;				
			}
			else if(count_rejim_led>20){
				if(rejim_led==1){
					LED_RED_OFF;
					LED_GREEN_ON;
				}
				else if(rejim_led==2){
					LED_RED_ON;
					LED_GREEN_ON;
				}
				if(count_rejim_led>350) count_rejim_led=0;  
			}


		break;}
		case 4: {
		  	if(count_rejim_led==1){
			  	LED_GREEN_OFF;
				LED_RED_ON;				
			}
			else if(count_rejim_led>20){
				if(rejim_led==1){
					LED_RED_OFF;
					LED_GREEN_ON;
				}
				else if(rejim_led==2){
					LED_RED_ON;
					LED_GREEN_ON;
				}
				if(count_rejim_led>120) count_rejim_led=0;  
			}

		break;}
		case 5: {
		 	if(count_rejim_led==1){
			  	LED_GREEN_OFF;
				LED_RED_OFF;				
			}
			else if(count_rejim_led==20){
				if(rejim_led==1){
					LED_RED_OFF;
					LED_GREEN_ON;
				}
				else if(rejim_led==2){
					LED_RED_ON;
					LED_GREEN_ON;
				}
		   	}
		   	else if(count_rejim_led==40){
			  	LED_GREEN_OFF;
				LED_RED_OFF;				
			}
			else if(count_rejim_led==60){
				if(rejim_led==1){
					LED_RED_OFF;
					LED_GREEN_ON;
				}
				else if(rejim_led==2){
					LED_RED_ON;
					LED_GREEN_ON;
				}
		   	}
			if(count_rejim_led>200) count_rejim_led=0;
		break;}
		case 6: {
			if(count_rejim_led==1){
			  	LED_GREEN_OFF;
				LED_RED_OFF;				
			}
			else if(count_rejim_led==20){
				if(rejim_led==1){
					LED_RED_OFF;
					LED_GREEN_ON;
				}
				else if(rejim_led==2){
					LED_RED_ON;
					LED_GREEN_ON;
				}
		   	}
		   	else if(count_rejim_led==40){
			  	LED_GREEN_OFF;
				LED_RED_OFF;				
			}
			else if(count_rejim_led==60){
				if(rejim_led==1){
					LED_RED_OFF;
					LED_GREEN_ON;
				}
				else if(rejim_led==2){
					LED_RED_ON;
					LED_GREEN_ON;
				}
		   	}
			if(count_rejim_led==80){
			  	LED_GREEN_OFF;
				LED_RED_OFF;				
			}
			else if(count_rejim_led==100){
				if(rejim_led==1){
					LED_RED_OFF;
					LED_GREEN_ON;
				}
				else if(rejim_led==2){
					LED_RED_ON;
					LED_GREEN_ON;
				}
		   	}
			if(count_rejim_led>250) count_rejim_led=0;
		

		break;}
		}//end switch(rejim_avar_led){
	}

}



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

/*
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
*/

