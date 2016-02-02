#include "25lc640.h"
#include "control.h"
#include "eeprom_map.h"
#include "avar_hndl.h"
#include "main.h"
#include "beeper_drv.h"
#include <LPC17xx.h>
#include "led_break_drv.h"
#include "snmp_data_file.h"
char chch;

#define  RELE1_OFF LPC_GPIO1->FIOCLR|=(1<<24)
#define  RELE1_ON LPC_GPIO1->FIOSET|=(1<<24)
#define  RELE2_OFF LPC_GPIO1->FIOCLR|=(1<<25)
#define  RELE2_ON LPC_GPIO1->FIOSET|=(1<<25)

long adc_buff[16][16];
char adc_self_ch_cnt/*,adc_ch_net*/;
short adc_buff_[16];
char adc_cnt,adc_cnt1,adc_ch,adc_ch_cnt;
unsigned short net_buff[32],net_buff_;
char net_buff_cnt;
signed short adc_self_ch_buff[3],adc_self_ch_disp[3];
short adc_result;
short adc_net_buff_cnt;

extern unsigned char avar_seti, avar_akb_umin;
extern signed short out_stat_cnt;
extern unsigned char out_av;
////-----------------------------------------------
void unet_drv(void)
{   
if ((snmp_main_voltage<1800)&&(main_cnt>3))//(LPC_GPIO1->FIOPIN&(1<<28))
	{
	net_stat_cnt--;
	}
else 
	{
	net_stat_cnt++;
	}
if(net_stat_cnt<-10) net_stat_cnt=-10;
if(net_stat_cnt>10)	net_stat_cnt=10;

if((net_stat_cnt<-5)&&(!net_av))
	{
	avar_unet_hndl(1);
	snmp_main_power_on_off=0;
	avar_seti=1;
	}
										 
else if((net_stat_cnt>5)&&(net_av))
	{
	avar_unet_hndl(0);
	snmp_main_power_on_off=1;
	avar_seti=0;
	}
//************** следилка за выходом 
if ((snmp_inverter_voltage<1800)&&(main_cnt>3))//(LPC_GPIO1->FIOPIN&(1<<28))
	{
	out_stat_cnt--;
	}
else 
	{
	out_stat_cnt++;
	}
if(out_stat_cnt<-10) out_stat_cnt=-10;
if(out_stat_cnt>10)	out_stat_cnt=10;

if((out_stat_cnt<-5)&&(!out_av))
	{
		out_av=1;
	}
										 
else if((out_stat_cnt>5)&&(out_av))
	{
		out_av=0;
	}


}

//-----------------------------------------------
extern signed short inverter_temperature_usr[10];
void matemat(void)
{
char i;
signed long temp_SL/*,temp_SL_*/;

/*
temp_SL=(signed long)adc_buff_[0]; //2618 (73V)
temp_SL*=Kubat[0]; // min=1500
temp_SL/=6400L;
snmp_battery_voltage=(signed short)temp_SL;
*/

temp_SL=(signed long)adc_buff_[1];
temp_SL-=(signed long)Kibat0[0];
temp_SL*=(signed long)Kibat1[0];
temp_SL/=1000L;
snmp_battery_current=-1*(signed short)temp_SL;
if(snmp_battery_current<-12 && count_iakb<200) count_iakb+=1;
else count_iakb=0;

temp_SL=0;
for(i=0;i<10;i++) temp_SL=temp_SL+inverter_temperature_usr[i];					  
snmp_inverter_temperature=temp_SL/10;
}

////-----------------------------------------------
void adc_init(void)
{

//SET_REG(LPC_PINCON->PINSEL1,1,(25-16)*2,2);
SET_REG(LPC_PINCON->PINSEL1,1,(24-16)*2,2);
SET_REG(LPC_PINCON->PINSEL1,1,(23-16)*2,2);
SET_REG(LPC_PINCON->PINSEL3,3,(31-16)*2,2);

//SET_REG(LPC_PINCON->PINMODE1,2,(25-16)*2,2);
SET_REG(LPC_PINCON->PINMODE1,2,(24-16)*2,2);
SET_REG(LPC_PINCON->PINMODE1,2,(23-16)*2,2);
SET_REG(LPC_PINCON->PINMODE3,2,(31-16)*2,2);

SET_REG(LPC_ADC->ADCR,0,24,3);	   // adc stopped

SET_REG(LPC_ADC->ADCR,1,21,1);   // adc active
SET_REG(LPC_ADC->ADCR,0,16,1);   // burst 0
SET_REG(LPC_ADC->ADCR,1,8,8);		// clock


LPC_ADC->ADINTEN     =  (1<< 8);      /* global enable interrupt            */

NVIC_EnableIRQ(ADC_IRQn);             /* enable ADC Interrupt               */


}

//-----------------------------------------------
void adc_drv7(void) //(Uсети - постоянка)
{

adc_self_ch_disp[0]=abs_pal(adc_self_ch_buff[1]-adc_self_ch_buff[0]);//adc_self_ch_buff[0]&0x0f80;
adc_self_ch_disp[1]=abs_pal(adc_self_ch_buff[2]-adc_self_ch_buff[1]);//adc_self_ch_buff[1]&0x0f80;
adc_self_ch_disp[2]=abs_pal(adc_self_ch_buff[2]-adc_self_ch_buff[0]);//adc_self_ch_buff[2]&0x0f80;


if(adc_self_ch_disp[2]<300)//==adc_self_ch_disp[2])
	{
	adc_result=adc_self_ch_buff[2];
	} 
else if(adc_self_ch_disp[1]<300)//==adc_self_ch_disp[2])
	{
	adc_result=adc_self_ch_buff[1];
	}
else if(adc_self_ch_disp[0]<300)//==adc_self_ch_disp[1])
	{
	adc_result=adc_self_ch_buff[0];
	}


	adc_buff[adc_ch][adc_ch_cnt]=(long)adc_result;
	
	if((adc_ch_cnt&0x03)==0)
		{
		long temp_L;
		char i;
		temp_L=0;
		for(i=0;i<16;i++)
			{
			temp_L+=adc_buff[adc_ch][i];
			}
		adc_buff_[adc_ch]= (short)(temp_L>>4);

		//adc_buff_[3]=346;
		}
	if(++adc_ch>=3) 
		{
		adc_ch=0;
		adc_ch_cnt++;
		if(adc_ch_cnt>=16)adc_ch_cnt=0;
		}



adc_self_ch_cnt=0;


if(adc_ch==0)		SET_REG(LPC_ADC->ADCR,1<<0,0,8);   // AD0.0 P0.23
else if(adc_ch==1) 	SET_REG(LPC_ADC->ADCR,1<<1,0,8);	   // AD0.1 P0.24
else if(adc_ch==2) 	SET_REG(LPC_ADC->ADCR,1<<5,0,8);	   // AD0.5 P1.31


LPC_ADC->ADCR |=  (1<<24);	   // start conversion

}
//*******************
void sk_init (void){
LPC_GPIO1->FIODIR&=~(1<<26);
LPC_GPIO1->FIODIR&=~(1<<27);
LPC_GPIO1->FIODIR|=(1<<28);
LPC_GPIO1->FIODIR|=(1<<29);
}
//*******************
void rele_init (void){
LPC_GPIO1->FIODIR|=(1<<22);	// калибровка нуля Iбат
LPC_GPIO1->FIODIR|=(1<<24);
LPC_GPIO1->FIODIR|=(1<<25);

}

//*************-----------------------------------------------
extern unsigned char id_rele1, id_rele2;
void rele_hndl(void)
{
	switch (id_rele1){
	case 0:{
		 if(avar_seti) RELE1_OFF;
		 else RELE1_ON;
	break;}
	case 1:{
		 if(avar_seti) RELE1_ON;
		 else RELE1_OFF;
	break;}
	case 2:{
		 if(out_av)  RELE1_OFF;
		 else RELE1_ON;
	break;}
	case 3:{
		 if(out_av) RELE1_ON;
		 RELE1_OFF;  
	break;}
	case 4:{
		 if(avar_akb_umin) RELE1_OFF;
		 else RELE1_ON;
	break;}
	case 5:{
		 if(avar_akb_umin) RELE1_ON;
		 else RELE1_OFF;
	break;}
	}// end switch (id_rele1){

	switch (id_rele2){
	case 0:{
		 if(avar_seti) RELE2_OFF;
		 else RELE2_ON;
	break;}
	case 1:{
		 if(avar_seti) RELE2_ON;
		 else RELE2_OFF;
	break;}
	case 2:{
		 if(out_av)  RELE2_OFF;
		 else RELE2_ON;
	break;}
	case 3:{
		 if(out_av) RELE2_ON;
		 else RELE2_OFF;  
	break;}
	case 4:{
		 if(avar_akb_umin) RELE2_OFF;
		 else RELE2_ON;
	break;}
	case 5:{
		 if(avar_akb_umin) RELE2_ON;
		 else RELE2_OFF;
	break;}
	}// end switch (id_rele1){

}

//биты аварий в приходящих сообщениях от источников
#define AV_OVERLOAD	0 
#define AV_T	1

#define AVUMAX	3
#define AVUMIN	4


//-----------------------------------------------
void inv_drv(char in)
{
char temp;
//if (bps[in]._device==dSRC) return;	   /**/

temp=bps[in]._flags_tm;

if(bps[in]._Ii>=110&&bps[in]._Ii<=200)
	{
	if(bps[in]._light_overload_av_cnt<10) 
		{
		bps[in]._light_overload_av_cnt++;
		if(bps[in]._light_overload_av_cnt>=10)
			{ 
			bps[in]._light_overload_av_cnt=10;
			if(!(bps[in]._av&(1<<5)))avar_bps_hndl(in,5,1);				
			}
		} 
	}		
else if((bps[in]._Ii<110)&&(bps[in]._Ii>-1))
	{
	if(bps[in]._light_overload_av_cnt>0) 
		{
		bps[in]._light_overload_av_cnt--;
		if(bps[in]._light_overload_av_cnt<=0)
			{
			bps[in]._light_overload_av_cnt=0;
			if(bps[in]._av&(1<<5))avar_bps_hndl(in,5,0);  ///////////
			}
		}
	else if(bps[in]._light_overload_av_cnt<0) bps[in]._light_overload_av_cnt=0;		 
	}


if((temp&(1<<AV_OVERLOAD)))
	{
	if(bps[in]._overload_av_cnt<10) 
		{
		bps[in]._overload_av_cnt++;
		if(bps[in]._overload_av_cnt>=10)
			{ 
			bps[in]._overload_av_cnt=10;
			if(!(bps[in]._av&(1<<4)))avar_bps_hndl(in,4,1);				
			}
		} 
	}		
else if(!(temp&(1<<AV_OVERLOAD)))
	{
	if(bps[in]._overload_av_cnt>0) 
		{
		bps[in]._overload_av_cnt--;
		if(bps[in]._overload_av_cnt<=0)
			{
			bps[in]._overload_av_cnt=0;
			if(bps[in]._av&(1<<4))avar_bps_hndl(in,4,0);  ///////////
			}
		}
	else if(bps[in]._overload_av_cnt<0) bps[in]._overload_av_cnt=0;		 
	}

if(temp&(1<<AV_T))
	{
	if(bps[in]._temp_av_cnt<1200) 
		{
		bps[in]._temp_av_cnt++;
		if(bps[in]._temp_av_cnt>=1200)
			{
			bps[in]._temp_av_cnt=1200;
		   	if(!(bps[in]._av&(1<<0)))avar_bps_hndl(in,0,1);
			}
		}
	}
else if(!(temp&(1<<AV_T)))
	{
	if(bps[in]._temp_av_cnt) 
		{
		bps[in]._temp_av_cnt--;
		if(!bps[in]._temp_av_cnt)
			{
			if(bps[in]._av&(1<<0))avar_bps_hndl(in,0,0);
			}
		} 	
	}

//temp&=(~((1<<AVUMAX)|((1<<AVUMIN))));

if((temp&(1<<AVUMAX)))
	{
	if(bps[in]._umax_av_cnt<40) 
		{
		bps[in]._umax_av_cnt++;
		if(bps[in]._umax_av_cnt>=40)
			{ 
			bps[in]._umax_av_cnt=40;
			if(!(bps[in]._av&(1<<1)))avar_bps_hndl(in,1,1);				
			}
		} 
	}		
else if(!(temp&(1<<AVUMAX)))
	{
	if(bps[in]._umax_av_cnt>0) 
		{
		bps[in]._umax_av_cnt--;
		if(bps[in]._umax_av_cnt==0)
			{
			bps[in]._umax_av_cnt=0;
			avar_bps_hndl(in,1,0);
			}
		}
	else if(bps[in]._umax_av_cnt<0) bps[in]._umax_av_cnt=0;		 
	}

if(temp&(1<<AVUMIN))
	{
	if(bps[in]._umin_av_cnt<40) 
		{
		bps[in]._umin_av_cnt++;
		if(bps[in]._umin_av_cnt>=40)
			{ 
			bps[in]._umin_av_cnt=40;
			if(!(bps[in]._av&(1<<2)))avar_bps_hndl(in,2,1);
			}
		} 
	}	
else if(!(temp&(1<<AVUMIN)))
	{
	if(bps[in]._umin_av_cnt) 
		{
		bps[in]._umin_av_cnt--;
		if(bps[in]._umin_av_cnt==0)
			{
			bps[in]._umin_av_cnt=0;
			avar_bps_hndl(in,2,0);
			}
		}
	else if(bps[in]._umin_av_cnt>10)bps[in]._umin_av_cnt--;	 
	}
//
//
//
//if (bps[in]._av&0x1f)						bps[in]._state=bsAV;
//else if (bps[in]._Uii<200)					bps[in]._state=bsOFF_AV_NET;	  /**/
//else if (bps[in]._flags_tm&BIN8(100000))	bps[in]._state=bsRDY;
//else if (bps[in]._cnt<20)					bps[in]._state=bsWRK;
//
}											 


