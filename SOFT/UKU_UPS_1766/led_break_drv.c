#include "led_break_drv.h"
#include "beeper_drv.h"
#include "main.h"
#include "LPC17xx.H"




void led_beep (void){
	if(rejim_avar_led==0){
		switch(rejim_led){
		case 1: {  // работа от сети, АКБ не разряжается
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
периодицность отсчета, т.е. периодичность опросов 1= 10мс 100Гц
1с=100отс
формат	blink(2,20,50,100)
		blink(кол-во в пачке,длительность одного,пауза в пачке,задержка после пачки)
*/
char b_quantity,b_restart=0,b_count_q;
signed short b_duration,b_pause,b_delay;
signed short b_count_b;

void blink(char q,signed short d,signed short p,signed short dl)
{
if (q!=b_quantity||d!=b_duration||p!=b_pause||dl!=b_delay)//если новая команда, обновить данные и рестарт
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
	INIT_LED;						   //инициализация порта
	if (b_restart)					   //при новой команде сброс всех счетчиков
		{
		LED_OFF;
		b_count_q=1;
		b_count_b=0;
		b_restart=0;
		}
	else if (b_quantity)				  // команда не пустая
		{
		if (b_count_b<b_duration)
			{
			LED_ON;					//вкл звук на время длит
			++b_count_b;
			}		    
		else if(b_count_q<b_quantity)		  //если пачка из более чем 1
			{
			if(b_count_b<(b_duration+b_pause))
				{
				LED_OFF; //выкл звук на время паузы
				++b_count_b;
				}
			else
				{
				b_count_b=0;			 	//на повтор
				++b_count_q;
				}					
			}
		else if(b_count_b<(b_duration+b_delay))
			{
			LED_OFF;						//выкл звук	на время задержки м/у пачками
			++b_count_b;
			}
		else
			{
			b_count_b=0;			 	//на повтор всей пачки
			b_count_q=1;
			}					
		}
}
*/

