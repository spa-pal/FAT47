#include "avar_hndl.h"
//#include "eeprom_map.h"
#include "full_can.h"
//#include "25lc640.h"
#include <LPC17xx.H>
#include "main.h"
#include "control.h"
#include "beeper_drv.h"
#include "led_break_drv.h"
#include "snmp_data_file.h" 


     
//***********************************************
//јварии
unsigned avar_stat;	 	//"ќтображение" всех аварийных в данный момент устройств в одном месте
unsigned avar_ind_stat; 	//"ќтображение" всех не просмотренных аварийных устройств в одном месте
unsigned avar_stat_old;
unsigned avar_stat_new,avar_stat_offed;
//—труктура переменных
//1бит  - питающа€ сеть
//2бита - батареи
//12бит - Ѕѕ—ы
//5бит  - инверторы
//4бита - внешние датчики температуры
//4бита - внешние сухие контакты

char /*av_net*//*,av_bat[2]*//*av_bps[12],*/av_inv[6];//,/*av_dt[4],av_sk[4]*/;

extern char bOUT_FREE2;	






//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//**********************************************
//¬нешние


//***********************************************
//—осто€ние первичной сети
//char u_net_av_stat,u_net_av_stat_;
extern signed short net_U,net_Ustore;
extern char bFF,bFF_;
extern signed short net_F,hz_out,hz_out_cnt;
extern signed char unet_drv_cnt;
extern char net_av;
extern unsigned char sw_red, sw_green;
extern unsigned char avar_seti;

//-----------------------------------------------
void avar_hndl(void)
{
if(count_iakb>8 || avar_seti==1) rejim_led=2;
else rejim_led=1;

if(sw_red){ LED_RED_ON; LED_GREEN_OFF; }
else if(sw_green){
		switch(rejim_led){
		case 1: {  // работа от сети, ј Ѕ не разр€жаетс€
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
else { LED_RED_OFF; LED_GREEN_OFF; }

}

////-----------------------------------------------
void avar_unet_hndl(char in)
{
if(in==1) 
	{
	work_at=acb;
	beep(1,50,0,500,30);
//	if(!(bps[NUMB]._cnt==CNT_SRC_MAX)) blink(0,0,0,0); //не гасить кр светодиод по потере кан
	net_av=1;
	bps[NUMB]._av&=~(0x17);// дл€ перезапуска по другим авари€м
	bps[NUMB]._temp_av_cnt=0;
	bps[NUMB]._overload_av_cnt=0;
	bps[NUMB]._light_overload_av_cnt=0;
	bps[NUMB]._umax_av_cnt=0;
	bps[NUMB]._umin_av_cnt=0;
	if(MAIN_POWER_TRAP_SEND_OF_AV)snmp_trap_send("Main power alarm. Power source is ACB",1,1);
	}	
else
	{
	work_at=power_net;
	beep(0,0,0,0,0);
//	if(!(bps[NUMB]._cnt==CNT_SRC_MAX)) blink(0,0,0,0);
	net_av=0;
	bps[NUMB]._av&=~(0x17);// дл€ перезапуска по другим авари€м
	bps[NUMB]._temp_av_cnt=0;
	bps[NUMB]._overload_av_cnt=0;
	bps[NUMB]._light_overload_av_cnt=0;
	bps[NUMB]._umax_av_cnt=0;
	bps[NUMB]._umin_av_cnt=0;
	if(MAIN_POWER_TRAP_SEND_OF_NO_AV)snmp_trap_send("Main power alarm clear. Power source is main power",1,0);
	}
		
}


//-----------------------------------------------
void avar_bps_hndl(char dev, char v, char in)
{
//char data[4];
//unsigned short event_ptr,lc640_adr,event_ptr_find,event_cnt;
//char avar_simbol;
//
//avar_simbol='T';
//if(v==0)avar_simbol='T';
//else if(v==1)avar_simbol='U';
//else if(v==2)avar_simbol='u';
//else if(v==3)avar_simbol='L';
//else if(v==4)avar_simbol='O';	   

if(in==1&&dev==NUMB)
	{
	//av_src[bps]=1;

//	SET_REG(avar_ind_stat,1,3+dev,1);
//	SET_REG(avar_stat,1,3+dev,1);
	
	if(v==0)		  // t hight
		{
		bps[dev]._av|=(1<<0);
		blink(1,25,0,275);
		}
	else if(v==1)
		{
		bps[dev]._av|=(1<<1);
		blink(3,25,25,225);
		beep (3,25,25,225,0);
		}
	else if(v==2)
		{
		bps[dev]._av|=(1<<2);
		blink(4,25,25,200);
		beep (4,25,25,200,0);
		}
	else if(v==3) // CAN off
		{
		bps[dev]._av|=(1<<3);
		blink(1,100,0,0);
		work_stat=breakdown;
		}
 	else if(v==4)	// overload		  
		{
		bps[dev]._av|=(1<<4);
		blink(2,25,25,150);
		beep (2,25,25,150,0);
		}
 	else if(v==5)	//light overload		  
		{
		bps[dev]._av|=(1<<5);
		blink(1,25,0,250);
		beep (1,25,0,250,30);
		}

	bps[dev]._last_avar=v;

		
 	
	}

else if(in==0&&dev==NUMB)
	{      

	if(v==0)
		{
		net_av=0;
		bps[NUMB]._av&=~(0x3F);// дл€ перезапуска по другим авари€м
		bps[NUMB]._overload_av_cnt=0;	   // аварии остались, то перезапуст€тс€
		bps[NUMB]._light_overload_av_cnt=0;
		bps[NUMB]._temp_av_cnt=0;
		bps[NUMB]._umax_av_cnt=0;
		bps[NUMB]._umin_av_cnt=0;
		blink(0,0,0,0);							  
		}
	else if(v==1)
		{
		bps[dev]._av&=(~(1<<1));
		net_av=0;
		bps[NUMB]._av&=~(0x3F);// дл€ перезапуска по другим авари€м
		bps[NUMB]._overload_av_cnt=0;	   // аварии остались, то перезапуст€тс€
		bps[NUMB]._light_overload_av_cnt=0;
		bps[NUMB]._temp_av_cnt=0;
		bps[NUMB]._umax_av_cnt=0;
		bps[NUMB]._umin_av_cnt=0;
		blink(0,0,0,0);
		beep(0,0,0,0,0);
		}
	else if(v==2)
		{
		bps[dev]._av&=(~(1<<2));
		net_av=0;
		bps[NUMB]._av&=~(0x3F);// дл€ перезапуска по другим авари€м
		bps[NUMB]._overload_av_cnt=0;	   // аварии остались, то перезапуст€тс€
		bps[NUMB]._light_overload_av_cnt=0;
		bps[NUMB]._temp_av_cnt=0;
		bps[NUMB]._umax_av_cnt=0;
		bps[NUMB]._umin_av_cnt=0;
		blink(0,0,0,0);
		beep(0,0,0,0,0);
		}
	else if(v==3)
		{
		net_av=0;
		bps[dev]._av&=~(0x3F);
		blink(0,0,0,0);
		work_stat=active;
		}
 	else if(v==4)	    
		{
		net_av=0;
		bps[NUMB]._av&=~(0x3F);// дл€ перезапуска по другим авари€м
		bps[NUMB]._overload_av_cnt=0;	   // аварии остались, то перезапуст€тс€
		bps[NUMB]._light_overload_av_cnt=0;
		bps[NUMB]._temp_av_cnt=0;
		bps[NUMB]._umax_av_cnt=0;
		bps[NUMB]._umin_av_cnt=0;
		blink(0,0,0,0);
		beep(0,0,0,0,0);
		}
 	else if(v==5)	    
		{
		net_av=0;
		bps[NUMB]._av&=~(0x3F);// дл€ перезапуска по другим авари€м
		bps[NUMB]._overload_av_cnt=0;	   // аварии остались, то перезапуст€тс€
		bps[NUMB]._light_overload_av_cnt=0;
		bps[NUMB]._temp_av_cnt=0;
		bps[NUMB]._umax_av_cnt=0;
		bps[NUMB]._umin_av_cnt=0;
		blink(0,0,0,0);
		beep(0,0,0,0,0);
		}
     
__nop();		
}

}



