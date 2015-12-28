#include "avar_hndl.h"
//#include "eeprom_map.h"
#include "full_can.h"
//#include "25lc640.h"
#include <LPC17xx.H>
#include "main.h"
#include "control.h"
#include "beeper_drv.h"
#include "led_break_drv.h"


     
//***********************************************
//������
unsigned avar_stat;	 	//"�����������" ���� ��������� � ������ ������ ��������� � ����� �����
unsigned avar_ind_stat; 	//"�����������" ���� �� ������������� ��������� ��������� � ����� �����
unsigned avar_stat_old;
unsigned avar_stat_new,avar_stat_offed;
//��������� ����������
//1���  - �������� ����
//2���� - �������
//12��� - ����
//5���  - ���������
//4���� - ������� ������� �����������
//4���� - ������� ����� ��������

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
//�������


//***********************************************
//��������� ��������� ����
//char u_net_av_stat,u_net_av_stat_;
extern signed short net_U,net_Ustore;
extern char bFF,bFF_;
extern signed short net_F,hz_out,hz_out_cnt;
extern signed char unet_drv_cnt;
extern char net_av;



//-----------------------------------------------
void avar_hndl(void)
{
//static unsigned avar_stat_old;
char i;
//unsigned avar_stat_new,avar_stat_offed;

if(net_av)		SET_REG(avar_stat,1,0,1);
else	   			SET_REG(avar_stat,0,0,1);

//for(i=0;i<2;i++)
//	{
//	if(bat[i]._av&1)	SET_REG(avar_stat,1,1+i,1);
//	else	   		SET_REG(avar_stat,0,1+i,1);
//	}

for(i=0;i<12;i++)
	{
 	if(bps[i]._av&&bps[i]._device==dSRC)	SET_REG(avar_stat,1,3+i,1);
	else if (bps[i]._av&&bps[i]._device==dINV) SET_REG(avar_stat,1,15+i,1);
	else
		{
		SET_REG(avar_stat,0,3+i,1);
		SET_REG(avar_stat,0,15+i,1);
		}					 
	}


/*for(i=0;i<4;i++)
	{
	if(av_dt[i])	SET_REG(avar_stat,1,21+i,1);
	else	   		SET_REG(avar_stat,0,21+i,1);
	}  */
//for(i=0;i<4;i++)
//	{
//	if(sk_av_stat[i]==sasON)	SET_REG(avar_stat,1,25+i,1);
//	else	   		SET_REG(avar_stat,0,25+i,1);
//	}

avar_stat_new=(avar_stat^avar_stat_old)&avar_stat;

avar_ind_stat|=avar_stat_new;

//if((SK_ZVUK_EN[0])) avar_ind_stat&=(~(1UL<<25));
//if((SK_ZVUK_EN[1])) avar_ind_stat&=(~(1UL<<26));
//if((SK_ZVUK_EN[2])) avar_ind_stat&=(~(1UL<<27));
//if((SK_ZVUK_EN[3])) avar_ind_stat&=(~(1UL<<28));	


avar_stat_offed=~((avar_stat^avar_stat_old)&avar_stat_old);

//if(!AV_OFF_AVT)avar_stat_offed|=0xfffffffe;

avar_ind_stat&=avar_stat_offed; 

avar_stat_old=avar_stat;
}

////-----------------------------------------------
//void reload_hndl(void)
//{
//char data[4];
//unsigned int event_ptr,lc640_adr/*,event_ptr_find*/,event_cnt;
//
//event_ptr=lc640_read_int(PTR_EVENT_LOG);
//event_ptr++;	
//if(event_ptr>63)event_ptr=0;	
//lc640_write_int(PTR_EVENT_LOG,event_ptr);	
//	
//event_cnt=lc640_read_int(CNT_EVENT_LOG);
//if(event_cnt!=63)event_cnt=event_ptr;
//lc640_write_int(CNT_EVENT_LOG,event_cnt); 
//	
//lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
//	
//data[0]='U';
//data[1]=0;
//data[2]='R';
//data[3]=0;
//lc640_write_long_ptr(lc640_adr,data);
//
//data[0]=0;
//data[1]=0;
//data[2]=0;
//data[3]=0;
//lc640_write_long_ptr(lc640_adr+4,data);
//
//data[0]=LPC_RTC->YEAR;
//data[1]=LPC_RTC->MONTH;
//data[2]=LPC_RTC->DOM;
//data[3]=0;
//lc640_write_long_ptr(lc640_adr+8,data);
//
//data[0]=LPC_RTC->HOUR;
//data[1]=LPC_RTC->MIN;
//data[2]=LPC_RTC->SEC;
//data[3]=0;
//lc640_write_long_ptr(lc640_adr+12,data);
//	
//data[0]='A';
//data[1]='A';
//data[2]='A';
//data[3]='A';
//lc640_write_long_ptr(lc640_adr+16,data);
//	
//data[0]='A';
//data[1]='A';
//data[2]='A';
//data[3]='A';
//lc640_write_long_ptr(lc640_adr+20,data);
//	
//data[0]='A';
//data[1]='A';
//data[2]='A';
//data[3]='A';
//lc640_write_long_ptr(lc640_adr+24,data);
//	
//data[0]='A';
//data[1]='A';
//data[2]='A';
//data[3]='A';
//lc640_write_long_ptr(lc640_adr+28,data);				
//	
//	
//}
//
////-----------------------------------------------
void avar_unet_hndl(char in)
{
if(in==1) 
	{
	work_at=acb;
	beep(1,50,0,500,30);
//	if(!(bps[NUMB]._cnt==CNT_SRC_MAX)) blink(0,0,0,0); //�� ������ �� ��������� �� ������ ���
	net_av=1;
	bps[NUMB]._av&=~(0x17);// ��� ����������� �� ������ �������
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
	bps[NUMB]._av&=~(0x17);// ��� ����������� �� ������ �������
	bps[NUMB]._temp_av_cnt=0;
	bps[NUMB]._overload_av_cnt=0;
	bps[NUMB]._light_overload_av_cnt=0;
	bps[NUMB]._umax_av_cnt=0;
	bps[NUMB]._umin_av_cnt=0;
	if(MAIN_POWER_TRAP_SEND_OF_NO_AV)snmp_trap_send("Main power alarm clear. Power source is main power",1,0);
	}
//
//char data[4];
//unsigned int event_ptr,lc640_adr,event_ptr_find,event_cnt;
//
//
//if(in==1) 
//	{
//	net_av=1;
//
//	//beep_init(0x01L,'O');
//	//a.av.bAN=1;
//
//
//	//beep_init(0x33333333,'A');
//	 
//	event_ptr=lc640_read_int(PTR_EVENT_LOG);
//	event_ptr++;	
//	if(event_ptr>63)event_ptr=0;	
//	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
//	
//     event_cnt=lc640_read_int(CNT_EVENT_LOG);
//	if(event_cnt!=63)event_cnt=event_ptr;
//	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
//	
//	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
//	
//	data[0]='P';
//	data[1]=0;
//	data[2]='A';
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr,data);
//
//	data[0]=0;//*((char*)&Unet_store);
//	data[1]=0;//*(((char*)&Unet_store)+1);
//	data[2]=0;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+4,data);
//
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+8,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+12,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+16,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+20,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+28,data);				
//	
///*	memo_out0[0]=0x55;
//     memo_out0[1]=0x00+2;
//     memo_out0[2]=1;
//     memo_out0[3]=0x0b;
//     memo_out0[4]=0x55;
//     memo_out0[5]=0x55; 
//     	
//     memo_out0[6]=crc_87(memo_out0,6);
//	memo_out0[7]=crc_95(memo_out0,6);
//     usart_out_adr0(memo_out0,8); 
//	*/
//	
//	}
//
//else if(in==0)
//	{
//	net_av=0;
//
//  /*
//	SET_REG(C2GSR,3,24,8);
//	C2MOD=0;
//	bOUT_FREE2=1;*/
//
//
//	//C2MOD=0;
//
//	//can2_init(7,8,CANBitrate250k_60MHz);
//
//     //beep_init(0x02L,'O');
//	//a_.av.bAN=0;
//	SET_REG(avar_stat,0,0,1);
//
//	//if(AV_OFF_AVT)a.av.bAN=0;
//	
//	if(AV_OFF_AVT) SET_REG(avar_ind_stat,0,0,1);
//
//     event_ptr=lc640_read_int(PTR_EVENT_LOG);
//	event_ptr_find=event_ptr;
//avar_unet_hndl_lbl1:
//	lc640_adr=EVENT_LOG+(event_ptr_find*32);
//
//     lc640_read_long_ptr(lc640_adr,data);
//     
//     if(!((data[0]=='P')&&(data[1]==0)&&(data[2]=='A')))
//     	{        
//     	if(event_ptr_find)event_ptr_find--;
//     	else event_ptr_find=63;
//     	if(event_ptr_find==event_ptr)goto avar_unet_hndl_end;
//     	else goto avar_unet_hndl_lbl1;
//     	}
//     else 
//     	{
//     	lc640_read_long_ptr(lc640_adr+16,data);
//     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
//     		{        
//     		if(event_ptr_find)event_ptr_find--;
//         		else event_ptr_find=63;
//         		if(event_ptr_find==event_ptr)goto avar_unet_hndl_end;
//     		else goto avar_unet_hndl_lbl1;
//     		}
//
//     	}	
//	
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+16,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+20,data); 
//	
//	data[0]=*((char*)(&net_Ustore));
//	data[1]=*(((char*)(&net_Ustore))+1);
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='B';
//	data[1]='B';
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+28,data);	
//	
///*	memo_out0[0]=0x55;
//     memo_out0[1]=0x00+2;
//     memo_out0[2]=1;
//     memo_out0[3]=0x0b;
//     memo_out0[4]=0xaa;
//     memo_out0[5]=0xaa; 
//     	
//     memo_out0[6]=crc_87(memo_out0,6);
//	memo_out0[7]=crc_95(memo_out0,6);
//     usart_out_adr0(memo_out0,8); */
//     	
//	}
//avar_unet_hndl_end:
//	__nop();		
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

	//beep_init(0x33333333,'A');

//	event_ptr=lc640_read_int(PTR_EVENT_LOG);
//	event_ptr++;	
//	if(event_ptr>63)event_ptr=0;	
//	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
	
//     event_cnt=lc640_read_int(CNT_EVENT_LOG);
//	if(event_cnt!=63)event_cnt=event_ptr;
//	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
	
//	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
 	
//	if (bps[dev]._device==dSRC)
//		{
//		data[0]='S';
//		data[1]=dev; 
//		}
//	else
//		{
//		data[0]='I';
//		data[1]=dev-NUMIST; 
//		}	 
//	data[2]=avar_simbol;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr,data);
//
//	data[0]=0;
//	data[1]=0;
//	data[2]=0;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+4,data);
//
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+8,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+12,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+16,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+20,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+28,data);		
 	
	}

else if(in==0&&dev==NUMB)
	{      
//	av_bps[bps]=0;

	//SET_REG(avar_stat,0,3+bps,1);
	//if(AV_OFF_AVT) SET_REG(avar_ind_stat,0,3+bps,1);

	if(v==0)
		{
		net_av=0;
		bps[NUMB]._av&=~(0x3F);// ��� ����������� �� ������ �������
		bps[NUMB]._overload_av_cnt=0;	   // ������ ��������, �� ��������������
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
		bps[NUMB]._av&=~(0x3F);// ��� ����������� �� ������ �������
		bps[NUMB]._overload_av_cnt=0;	   // ������ ��������, �� ��������������
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
		bps[NUMB]._av&=~(0x3F);// ��� ����������� �� ������ �������
		bps[NUMB]._overload_av_cnt=0;	   // ������ ��������, �� ��������������
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
		bps[NUMB]._av&=~(0x3F);// ��� ����������� �� ������ �������
		bps[NUMB]._overload_av_cnt=0;	   // ������ ��������, �� ��������������
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
		bps[NUMB]._av&=~(0x3F);// ��� ����������� �� ������ �������
		bps[NUMB]._overload_av_cnt=0;	   // ������ ��������, �� ��������������
		bps[NUMB]._light_overload_av_cnt=0;
		bps[NUMB]._temp_av_cnt=0;
		bps[NUMB]._umax_av_cnt=0;
		bps[NUMB]._umin_av_cnt=0;
		blink(0,0,0,0);
		beep(0,0,0,0,0);
		}
     
//	if((bps[dev]._av&0x0f==0))
//	     {
		//SET_REG(avar_stat,0,3+bps,1);
		//if(AV_OFF_AVT) SET_REG(avar_ind_stat,0,3+bps,1);
//	     }
 
//	event_ptr=lc640_read_int(PTR_EVENT_LOG);
//	event_ptr_find=event_ptr;
//	
//avar_src_hndl_lbl1: 
//
//	lc640_adr=EVENT_LOG+(event_ptr_find*32);
//
//     lc640_read_long_ptr(lc640_adr,data);
///*     
//     if(!((data[0]=='S')&&(data[1]==dev)&&(data[2]==avar_simbol)))
//     	{        
//     	if(event_ptr_find)event_ptr_find--;
//     	else event_ptr_find=63;
//     	if(event_ptr_find==event_ptr)goto avar_src_hndl_end;
//     	else goto avar_src_hndl_lbl1;
//     	}
//     else 
//     	{
//     	lc640_read_long_ptr(lc640_adr+16,data);
//     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
//     		{        
//     		if(event_ptr_find)event_ptr_find--;
//         		else event_ptr_find=63;
//         		if(event_ptr_find==event_ptr)goto avar_src_hndl_end;
//     		else goto avar_src_hndl_lbl1;
//     		}
//
//     	}	
//*/
// 
//     if(((data[0]=='S')&&(data[1]==dev))||((data[0]=='I')&&(data[1]==dev-NUMIST))&&(data[2]==avar_simbol))
//     	{
//		lc640_read_long_ptr(lc640_adr+16,data);
//     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
//     		{        
//     		if(event_ptr_find)event_ptr_find--;
//         	else event_ptr_find=63;
//         	if(event_ptr_find==event_ptr)goto avar_src_hndl_end;
//     		else goto avar_src_hndl_lbl1;
//     		}        
//     	}
//     else 
//     	{
//     	if(event_ptr_find)event_ptr_find--;
//     	else event_ptr_find=63;
//     	if(event_ptr_find==event_ptr) goto avar_src_hndl_end;
//     	else goto avar_src_hndl_lbl1;
//     	}							  
//	
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+16,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+20,data);
//	
//	data[0]='B';
//	data[1]='B';
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='B';
//	data[1]='B';
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+28,data);
//	
	}
//	
//avar_src_hndl_end:
__nop();		
}

////-----------------------------------------------
//void wrk_mem_hndl(char b)
//{
//char data[4];
//unsigned short event_ptr,lc640_adr/*,event_ptr_find*/,event_cnt;
//
//signed short temp_temp;
//
//if(bat[b]._Iintegr_<5) goto wrk_mem_hndl_end;
//
//temp_temp=bat[b]._u_old[((bat_u_old_cnt+6)&0x07)]; 
//
//
//event_ptr=lc640_read_int(PTR_EVENT_LOG);
//event_ptr++;	
//if(event_ptr>63)event_ptr=0;	
//lc640_write_int(PTR_EVENT_LOG,event_ptr);	
//	
//event_cnt=lc640_read_int(CNT_EVENT_LOG);
//if(event_cnt!=63)event_cnt=event_ptr;
//lc640_write_int(CNT_EVENT_LOG,event_cnt); 
//	
//lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
//	
//data[0]='B';
//data[1]=b; 
//data[2]='W';
//data[3]=0;
//
//lc640_write_long_ptr(lc640_adr,data);
//
//data[0]=*((char*)&bat[b]._Iintegr_);
//data[1]=*(((char*)(&bat[b]._Iintegr_))+1);
//data[2]=*((char*)&temp_temp);
//data[3]=*(((char*)(&temp_temp))+1);
//lc640_write_long_ptr(lc640_adr+4,data);
//
//lc640_write_long_ptr(lc640_adr+8,(char*)&bat[b]._wrk_date[0]);
//	
//lc640_write_long_ptr(lc640_adr+12,(char*)&bat[b]._wrk_date[1]);
//
//data[0]=LPC_RTC->YEAR;
//data[1]=LPC_RTC->MONTH;
//data[2]=LPC_RTC->DOM;
//data[3]=0;
//lc640_write_long_ptr(lc640_adr+16,data);
//
//data[0]=LPC_RTC->HOUR;
//data[1]=LPC_RTC->MIN;
//data[2]=LPC_RTC->SEC;
//data[3]=0;
//lc640_write_long_ptr(lc640_adr+20,data);
//	
//
//
//	
//wrk_mem_hndl_end:	
//__nop();
//}  
//
////-----------------------------------------------
//void avar_bat_hndl(char b, char in)
//{
//char data[4];
//unsigned short event_ptr,lc640_adr,event_ptr_find,event_cnt;
//
//if(in==1)
//	{
//	bat[b]._av|=1;
//    
//	event_ptr=lc640_read_int(PTR_EVENT_LOG);
//	event_ptr++;	
//	if(event_ptr>63)event_ptr=0;	
//	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
//	
//     event_cnt=lc640_read_int(CNT_EVENT_LOG);
//	if(event_cnt!=63)event_cnt=event_ptr;
//	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
//	
//	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
//	
//	data[0]='B';
//	data[1]=b;
//	data[2]='C';
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr,data);
//
//	data[0]=0;
//	data[1]=0;
//	data[2]=0;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+4,data);
//
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+8,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+12,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+16,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+20,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+28,data);				
//	
//	}
//
//else if(in==0)
//	{
//	bat[b]._av&=~1;
//
//     event_ptr=lc640_read_int(PTR_EVENT_LOG);
//	event_ptr_find=event_ptr;
//	
//avar_bat_hndl_lbl1: 
//
//	lc640_adr=EVENT_LOG+(event_ptr_find*32);
//
//     lc640_read_long_ptr(lc640_adr,data);
//     
//     if(!((data[0]=='B')&&(data[1]==b)&&(data[2]=='C')))
//     	{        
//     	if(event_ptr_find)event_ptr_find--;
//     	else event_ptr_find=63;
//     	if(event_ptr_find==event_ptr)goto avar_bat_hndl_end;
//     	else goto avar_bat_hndl_lbl1;
//     	}
//     else 
//     	{
//     	lc640_read_long_ptr(lc640_adr+16,data);
//     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
//     		{        
//     		if(event_ptr_find)event_ptr_find--;
//         		else event_ptr_find=63;
//         	    	if(event_ptr_find==event_ptr)goto avar_bat_hndl_end;
//     		else goto avar_bat_hndl_lbl1;
//     		}
//
//     	}
//     		
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+16,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+20,data);
//	
//	data[0]='B';
//	data[1]='B';
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='B';
//	data[1]='B';
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+28,data);
//	
//
//	
//	}
//	
//avar_bat_hndl_end:
//__nop();		
//}
//
////-----------------------------------------------
//void avar_bat_as_hndl(char b, char in)
//{
//char data[4];
//unsigned short event_ptr,lc640_adr,event_ptr_find,event_cnt;
//
//if(in==1)
//	{
//	bat[b]._av|=2;
//    
//	event_ptr=lc640_read_int(PTR_EVENT_LOG);
//	event_ptr++;	
//	if(event_ptr>63)event_ptr=0;	
//	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
//	
//     event_cnt=lc640_read_int(CNT_EVENT_LOG);
//	if(event_cnt!=63)event_cnt=event_ptr;
//	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
//	
//	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
//	
//	data[0]='B';
//	data[1]=b;
//	data[2]='S';
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr,data);
//
//	data[0]=0;
//	data[1]=0;
//	data[2]=0;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+4,data);
//
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+8,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+12,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+16,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+20,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+28,data);				
//	
//	}
//
//else if(in==0)
//	{
//	//bat[b]._av=0;
//
//     event_ptr=lc640_read_int(PTR_EVENT_LOG);
//	event_ptr_find=event_ptr;
//	
//avar_bat_as_hndl_lbl1: 
//
//	lc640_adr=EVENT_LOG+(event_ptr_find*32);
//
//     lc640_read_long_ptr(lc640_adr,data);
//     
//     if(!((data[0]=='B')&&(data[1]==b)&&(data[2]=='C')))
//     	{        
//     	if(event_ptr_find)event_ptr_find--;
//     	else event_ptr_find=63;
//     	if(event_ptr_find==event_ptr)goto avar_bat_as_hndl_end;
//     	else goto avar_bat_as_hndl_lbl1;
//     	}
//     else 
//     	{
//     	lc640_read_long_ptr(lc640_adr+16,data);
//     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
//     		{        
//     		if(event_ptr_find)event_ptr_find--;
//         		else event_ptr_find=63;
//         	    	if(event_ptr_find==event_ptr)goto avar_bat_as_hndl_end;
//     		else goto avar_bat_as_hndl_lbl1;
//     		}
//
//     	}
//     		
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+16,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+20,data);
//	
//	data[0]='B';
//	data[1]='B';
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='B';
//	data[1]='B';
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+28,data);
//	
//
//	
//	}
//	
//avar_bat_as_hndl_end:
//__nop();		
//}
//
//
////-----------------------------------------------
//void ke_mem_hndl(char b,unsigned short in)
//{
//char data[4];
//unsigned int event_ptr=0,lc640_adr/*,event_ptr_find*/,event_cnt;
////unsigned char temp,temp_;
////unsigned int tempUI;
////unsigned long tempUL; 
//signed temp_temp;
//
//temp_temp=bat[b]._u_old[bat_u_old_cnt+1]; 
//
//event_ptr=lc640_read_int(PTR_EVENT_LOG);
//event_ptr++;	
//if(event_ptr>63)event_ptr=0;	
//lc640_write_int(PTR_EVENT_LOG,event_ptr);	
//	
//event_cnt=lc640_read_int(CNT_EVENT_LOG);
//if(event_cnt!=63)event_cnt=event_ptr;
//lc640_write_int(CNT_EVENT_LOG,event_cnt); 
//	
//lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
//	
//data[0]='B';
//data[1]=b; 
//data[2]='K';
//data[3]=0;
//
//lc640_write_long_ptr(lc640_adr,data);
//
//data[0]=*((char*)&in);
//data[1]=*(((char*)(&in))+1);
//data[2]=*((char*)&temp_temp);
//data[3]=*(((char*)(&temp_temp))+1);
//lc640_write_long_ptr(lc640_adr+4,data);
//
//lc640_write_long_ptr(lc640_adr+8,(char*)&ke_date[0]);
//	
//lc640_write_long_ptr(lc640_adr+12,(char*)&ke_date[1]);
//
//data[0]=LPC_RTC->YEAR;
//data[1]=LPC_RTC->MONTH;
//data[2]=LPC_RTC->DOM;
//data[3]=0;
//lc640_write_long_ptr(lc640_adr+16,data);
//
//data[0]=LPC_RTC->HOUR;
//data[1]=LPC_RTC->MIN;
//data[2]=LPC_RTC->SEC;
//data[3]=0;
//lc640_write_long_ptr(lc640_adr+20,data);
// 
//}
//
//
////-----------------------------------------------
//void vz_mem_hndl(unsigned short in)
//{
//char data[4];
//unsigned int event_ptr=0,lc640_adr,event_ptr_find=0,event_cnt;
////char avar_simbol;
//
//if(in==1)
//	{
//	event_ptr=lc640_read_int(PTR_EVENT_LOG);
//	event_ptr++;	
//	if(event_ptr>63)event_ptr=0;	
//	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
//	
//     event_cnt=lc640_read_int(CNT_EVENT_LOG);
//	if(event_cnt!=63)event_cnt=event_ptr;
//	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
//	
//	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
//	
//	data[0]='B';
//	data[1]=0; 
//	data[2]='Z';
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr,data);
//
//	data[0]=0;
//	data[1]=0;
//	data[2]=0;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+4,data);
//
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+8,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+12,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+16,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+20,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='A';
//	data[1]='A';
//	data[2]='A';
//	data[3]='A';
//	lc640_write_long_ptr(lc640_adr+28,data);		
// 	
//	}
//
//else if(in==0)
//	{      
//     
//vz_mem_hndl_lbl1: 
//
//	lc640_adr=EVENT_LOG+(event_ptr_find*32);
//
//     lc640_read_long_ptr(lc640_adr,data);
//     
//     if(!((data[0]=='B')&&(data[2]=='Z')))
//     	{        
//     	if(event_ptr_find)event_ptr_find--;
//     	else event_ptr_find=63;
//     	if(event_ptr_find==event_ptr)goto vz_mem_hndl_end;
//     	else goto vz_mem_hndl_lbl1;
//     	}
//     else 
//     	{
//     	lc640_read_long_ptr(lc640_adr+16,data);
//     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
//     		{        
//     		if(event_ptr_find)event_ptr_find--;
//         		else event_ptr_find=63;
//         		if(event_ptr_find==event_ptr)goto vz_mem_hndl_end;
//     		else goto vz_mem_hndl_lbl1;
//     		}
//
//     	}	
//
//
//	
//	data[0]=LPC_RTC->YEAR;
//	data[1]=LPC_RTC->MONTH;
//	data[2]=LPC_RTC->DOM;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+16,data);
//
//	data[0]=LPC_RTC->HOUR;
//	data[1]=LPC_RTC->MIN;
//	data[2]=LPC_RTC->SEC;
//	data[3]=0;
//	lc640_write_long_ptr(lc640_adr+20,data);
//	
//	data[0]='B';
//	data[1]='B';
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+24,data);
//	
//	data[0]='B';
//	data[1]='B';
//	data[2]='B';
//	data[3]='B';
//	lc640_write_long_ptr(lc640_adr+28,data);
//	
//	}
//
//vz_mem_hndl_end:
//__nop(); 
//
//}
//  



