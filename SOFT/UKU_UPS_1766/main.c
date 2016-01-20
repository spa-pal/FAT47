#include "LPC17xx.H"

unsigned char delete_temp;

#include "main.h"                   /* LPC17xx definitions                */
//#include "ports_operations.h"
//#include "button_drv.h"
//include "button_action.h"
#include "net_config.h"
//#include "ind_drv.h"
#include "beeper_drv.h"
#include "control.h"
#include "gran.h"
#include "25lc640.h"
#include "full_can.h"
#include "cmd.h"
#include "avar_hndl.h"
#include "led_break_drv.h"
#include "rtl.h"
#include "snmp_data_file.h"
#include "eeprom_map.h"
#include "ssd1306.h"
#include "i2c.h"
#include "ssd_1306.h"
//#include "simbol.h"
#include "simbol16x9.h"
#include "simbol17x16.h"
#include "simbol_p27CircleCyr_10ptBitmaps.h"
#include "memo.h"
#include "stdio.h"
#include "string.h"


#define BUT_ON 4
#define BUT_ONL 20 

#define BUT0	0	 //L
#define BUT1	1	 //R
#define BUT2	2	 //D
#define BUT3	3	 //U
#define BUT4	4	 //F
#define BUT_MASK (1UL<<BUT0)|(1UL<<BUT1)|(1UL<<BUT2)|(1UL<<BUT3)|(1UL<<BUT4)
unsigned char poz_display, poz_display_bf, poz_display_bf2, poz_kursor, poz_kursor_bf, poz_kursor_bf2;
unsigned char poz_display_temp_gm;
unsigned delay_scrin_saver;
unsigned char count_right,count_left,count_down,count_up,count_f;
unsigned short flag_right,flag_left,flag_down,flag_up,flag_f;
unsigned short count_kalibr_i_bat;
bool flag_l_r, flash_1S;
#define K_U (LPC_GPIO2->FIOPIN&(1<<BUT3))
#define K_D (LPC_GPIO2->FIOPIN&(1<<BUT2))
#define K_R (LPC_GPIO2->FIOPIN&(1<<BUT1))
#define K_L (LPC_GPIO2->FIOPIN&(1<<BUT0))
#define K_F (LPC_GPIO2->FIOPIN&(1<<BUT4))
unsigned short password, password_obr;
unsigned char pass_error; 
unsigned char poz_flash, data_can_reset;

unsigned char par_glav_menu[10]; // [0]-включение/отключение гл. меню
								 // [1]задержка перед включением
							   	 // [2]интервал переключения параметров
unsigned char delay_glav_menu, intelval_glav_menu, nomer_glav_menu;
unsigned char u_bat_on, u_bat_off;
void led_beep(void);
extern LOCALM localm[];
extern U8 own_hw_adr[];

extern U16  snmp_PortNum;
extern U16  snmp_TrapPort;

unsigned char count_iakb; // длительность непрерывных данных отрицательного тока АКБ

const char sm_mont[13][4]={"упс","янв","фев","мар","апр","май","июн","июл","авг","сен","окт","ноя","дек"}; //
char tcp_init_cnt;
unsigned char canzz_tmp, canzx_tmp;
unsigned char kontrol_seti, upravl_shim;
unsigned char rejim_led, rejim_avar_led; // режим свечения светодиода
unsigned short count_rejim_led;
unsigned char sw_red, sw_green;

void sk_init(void);
#define SK_X18 (LPC_GPIO1->FIOPIN&(1<<26))
#define SK_X19 (LPC_GPIO1->FIOPIN&(1<<27))
#define  X16_OFF LPC_GPIO1->FIOCLR|=(1<<29)
#define  X16_ON LPC_GPIO1->FIOSET|=(1<<29)
#define  X17_OFF LPC_GPIO1->FIOCLR|=(1<<28)
#define  X17_ON LPC_GPIO1->FIOSET|=(1<<28)                                           

void rele_init(void);
#define  RELE1_OFF LPC_GPIO1->FIOCLR|=(1<<24)
#define  RELE1_ON LPC_GPIO1->FIOSET|=(1<<24)
#define  RELE2_OFF LPC_GPIO1->FIOCLR|=(1<<25)
#define  RELE2_ON LPC_GPIO1->FIOSET|=(1<<25)
#define  RELE_I_OFF LPC_GPIO1->FIOCLR|=(1<<22)
#define  RELE_I_ON LPC_GPIO1->FIOSET|=(1<<22)

//------Таймер
short t100=10-10,t50=20-5,t10=100-25,t5=200-45,t2=500-65,t1=1000-85;   // подобрана фаза для несовпадения событий
char f1000Hz,f100Hz,f50Hz,f10Hz,f5Hz,f2Hz,f1Hz;								  // флаги срабатывания событий
BOOL tick;
bool bDTS; 
//-----Индикация
char init; 
 
//-----------------------------------------------
//Индикация
stuct_ind a,b[10];
short ind_out[3];
char lcd_bitmap[1024];
char lcd_buffer[70];//={"QWERTYUIOP12345ZXCVBNMASDFGHJKL12345ФЫВА"};
//-----Состояние
//typedef enum work{power_net,acb} work;
work work_at=power_net;
//typedef enum stat{breakdown,active} stat;
stat work_stat;
signed short flash_net_def_cnt;	   
//-----
//**********************************************
//Коэффициенты, отображаемые из EEPROM
//signed short Ktsrc[2];
//signed short Kusrc[2];
//signed short Kisrc[2];
//signed short Ki0src[2];
signed short Kubat[2];
//signed short Kubatm[2];
signed short Kibat0[2];
signed short Kibat1[2];
//signed short Ktbat[2];
signed short Kunet;
//signed short Kunet_ext[3];
//signed short Ktext[3];
//signed short Kuload;
//
//signed short MAIN_IST;
//signed short UMAX;
//signed short UB0;
//signed short UB20;
//signed short TMAX;
//signed short TSIGN;
//signed short AV_OFF_AVT;
//signed short USIGN;
//signed short UMN;
//signed short ZV_ON;
//signed short IKB;
//signed short KVZ;
//signed short IMAX;
//signed short KIMAX;
//signed short APV_ON;
//signed short IZMAX;
//signed short U0B;
//signed short TZAS;
//signed short VZ_HR;
//signed short TBAT;
//signed short U_AVT;
//signed short DU;
//signed short PAR;
//signed short TBATMAX;
//signed short TBATSIGN;
//signed short UBM_AV;
//signed short TBOXMAX;
//signed short TBOXREG;
//signed short TBOXVENTMAX;
//signed short TLOADDISABLE;
//signed short TLOADENABLE;
//signed short TBATDISABLE;
//signed short TBATENABLE;
//
//signed short NUMBAT;
//signed short NUMIST;
//signed short NUMINV;
//signed short NUMDT;
//signed short NUMSK;
//signed short NUMEXT;
//signed short NUMAVT;
//
//enum_apv_on APV_ON1,APV_ON2;
//signed short APV_ON2_TIME;
//
//enum_bat_is_on BAT_IS_ON[2];
//signed short BAT_DAY_OF_ON[2];
//signed short BAT_MONTH_OF_ON[2];
//signed short BAT_YEAR_OF_ON[2];
//signed short BAT_C_NOM[2];
//signed short BAT_RESURS[2];
//signed short BAT_C_REAL[2];
//
//unsigned short AUSW_MAIN;
//unsigned long 	AUSW_MAIN_NUMBER;
//unsigned short AUSW_DAY;
//unsigned short AUSW_MONTH;
//unsigned short AUSW_YEAR;
//unsigned short AUSW_UKU;
//unsigned short AUSW_UKU_SUB;
//unsigned long AUSW_UKU_NUMBER;
//unsigned long	AUSW_BPS1_NUMBER;
//unsigned long  AUSW_BPS2_NUMBER;
//unsigned short AUSW_RS232;
//unsigned short AUSW_PDH;
//unsigned short AUSW_SDH;
//unsigned short AUSW_ETH;
//
//signed short TMAX_EXT_EN[3];
//signed short TMAX_EXT[3];
//signed short TMIN_EXT_EN[3];
//signed short TMIN_EXT[3];
//signed short T_EXT_REL_EN[3];
//signed short T_EXT_ZVUK_EN[3];
//signed short T_EXT_LCD_EN[3];
//signed short T_EXT_RS_EN[3];
//
//signed short SK_SIGN[4];
//signed short SK_REL_EN[4];
//signed short SK_ZVUK_EN[4];
//signed short SK_LCD_EN[4];
//signed short SK_RS_EN[4];
//
//enum_avz AVZ;
//
//unsigned short HOUR_AVZ;
//unsigned short MIN_AVZ;
//unsigned short SEC_AVZ;
//unsigned short DATE_AVZ;
//unsigned short MONTH_AVZ;
//unsigned short YEAR_AVZ;
//unsigned short AVZ_TIME;
//
//enum_mnemo_on MNEMO_ON;
//unsigned short MNEMO_TIME;
//
//signed short POWER_CNT_ADRESS;
//
//signed short ETH_IS_ON;
signed long SERIAL_NUMBER;

//***********************************************
//ETH-настройки
signed short ETH_IS_ON;
signed short ETH_DHCP_ON;
signed short ETH_IP_1;
signed short ETH_IP_2;
signed short ETH_IP_3;
signed short ETH_IP_4;
signed short ETH_NET_MASK_1;
signed short ETH_NET_MASK_2;
signed short ETH_NET_MASK_3;
signed short ETH_NET_MASK_4;
signed short ETH_DEF_GATW_1;
signed short ETH_DEF_GATW_2;
signed short ETH_DEF_GATW_3;
signed short ETH_DEF_GATW_4;

//
signed short ETH_SNMP_PORT_READ;
signed short ETH_SNMP_PORT_WRITE;
//


//***********************************************
//SNMP-настройки
signed short SNMP_READ_PORT;
signed short SNMP_WRITE_PORT;
signed short SNMP_TRAP1_IP_1;
signed short SNMP_TRAP1_IP_2;
signed short SNMP_TRAP1_IP_3;
signed short SNMP_TRAP1_IP_4;
signed short SNMP_TRAP2_IP_1;
signed short SNMP_TRAP2_IP_2;
signed short SNMP_TRAP2_IP_3;
signed short SNMP_TRAP2_IP_4;
signed short SNMP_TRAP3_IP_1;
signed short SNMP_TRAP3_IP_2;
signed short SNMP_TRAP3_IP_3;
signed short SNMP_TRAP3_IP_4;
signed short SNMP_TRAP4_IP_1;
signed short SNMP_TRAP4_IP_2;
signed short SNMP_TRAP4_IP_3;
signed short SNMP_TRAP4_IP_4;
signed short SNMP_TRAP5_IP_1;
signed short SNMP_TRAP5_IP_2;
signed short SNMP_TRAP5_IP_3;
signed short SNMP_TRAP5_IP_4;

//***********************************************
//Трап-настройки
signed short MAIN_POWER_TRAP_SEND_OF_AV;
signed short MAIN_POWER_TRAP_SEND_OF_NO_AV;
signed short INVERTER_TEMPERATURE_TRAP_SEND_OF_AV;
signed short INVERTER_TEMPERATURE_TRAP_SEND_OF_NO_AV;
signed short INVERTER_VOLTAGE_TRAP_SEND_OF_AV;
signed short INVERTER_VOLTAGE_TRAP_SEND_OF_NO_AV;
signed short INVERTER_CURRENT_TRAP_SEND_OF_AV;
signed short INVERTER_CURRENT_TRAP_SEND_OF_NO_AV;
signed short BATTERY_VOLTAGE_TRAP_SEND_OF_AV;
signed short BATTERY_VOLTAGE_TRAP_SEND_OF_NO_AV;


//***********************************************
//Структура ИБЭПа
char cnt_of_slave=8;
//***********************************************
//Состояние источников
BPS_STAT bps[12];
//***********************************************
//Межблоковая связь
char cnt_net_drv;
//***********************************************
//КАН 
extern char ptr_can1_tx_wr,ptr_can1_tx_rd;
extern char ptr_can2_tx_wr,ptr_can2_tx_rd;
extern unsigned short rotor_can[6];
extern char RXBUFF[40],TXBUFF[40];
//***********************************************
//Состояние первичной сети
char net_av=1;
signed short net_stat_cnt=0;



//-----------------------------------------------
//Кнопки
char speed,l_but,n_but;
char but;                            
unsigned long but_n,but_s;
char but0_cnt;
char but1_cnt;
char but_onL_temp;


signed short main_cnt;
char plazma_pal;
signed short rele_cnt;
char bRELE;
//-----------------------------------------------

//-----------------------------------------------
void delay_us(long del)
{
long temp;
temp=5*del;

while (--temp);
return;
}

//-----------------------------------------------
void Delay (unsigned long tick) 
{       
unsigned long syst;

syst = tick;
while (--syst);
}


#define butLRC_		120
#define butC_		125
#define butC		253
#define butR_		126
#define butR		254
#define butL_		123
#define butL		251
#define butLR		250
#define butE		247
#define butE_		247-128

//-----------------------------------------------


//Таймер

void rtc_init (void) 
{
LPC_RTC->CCR=0x11;
}

//-----------------------------------------------
void net_drv(void)
{ 
//char temp_;    

if(++cnt_net_drv>=24) cnt_net_drv=0; //всего 16 посылок

if(cnt_net_drv<=7) // с 1 по 12 посылки адресные		  /**/
	{    
	can1_out(cnt_net_drv,cnt_net_drv,GETTM,bps[cnt_net_drv]._flags_tu,*((char*)(&bps[cnt_net_drv]._vol_u)),*((char*)((&bps[cnt_net_drv]._vol_u))+1),*((char*)(&bps[cnt_net_drv]._vol_i)),*((char*)((&bps[cnt_net_drv]._vol_i))+1));
     
	if(cnt_net_drv<cnt_of_slave)
	     {
	     if(bps[cnt_net_drv]._cnt<CNT_SRC_MAX)
   	 		{    
   	 		bps[cnt_net_drv]._cnt++;
   	 		if( (bps[cnt_net_drv]._cnt>=CNT_SRC_MAX) /*&& (!net_av)*/ && (!(bps[cnt_net_drv]._av&0x08)) ) 
   	 			{
 	 			avar_bps_hndl(cnt_net_drv,3,1);
   	 			}
   	 		}
		else bps[cnt_net_drv]._cnt=CNT_SRC_MAX;
						
		if((bps[cnt_net_drv]._cnt>=3)&&(bps[cnt_net_drv]._cnt_old<3))bps[cnt_net_drv]._cnt_more2++;
		bps[cnt_net_drv]._cnt_old=bps[cnt_net_drv]._cnt;
	     }
	}

else if(cnt_net_drv==8)
	{
//     can1_out(cnt_net_drv,cnt_net_drv,*((char*)(&Uvv[0])),*((char*)((&Uvv[0]))+1),*((char*)(&Uvv[1])),*((char*)((&Uvv[1]))+1),0,bRESET_EXT);
     }

else if(cnt_net_drv==9)
	{
//     can1_out(cnt_net_drv,cnt_net_drv,(char)main_vent_pos,*((char*)(&POWER_CNT_ADRESS)),*((char*)((&POWER_CNT_ADRESS))+1),0,0,0);
     }

else if(cnt_net_drv==10)
	{
     can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     }

else if(cnt_net_drv==12)
	{
//     can1_out(0xff,0xff,MEM_KF,*((char*)(&UMAX)),*((char*)((&UMAX))+1),*((char*)(&DU)),*((char*)((&DU))+1),0);
     } 
     
else if(cnt_net_drv==13)
	{
//     can1_out(0xff,0xff,MEM_KF1,*((char*)(&TMAX)),*((char*)((&TMAX))+1),*((char*)(&TSIGN)),*((char*)((&TSIGN))+1),(char)TZAS);
     } 
else if(cnt_net_drv==14)
	{                 
//	can2_out(0xff,0xff,MEM_KF2,*((char*)(&U_INV_MAX)),*((char*)((&U_INV_MAX))+1),*((char*)(&U_INV_MIN)),*((char*)((&U_INV_MIN))+1),(char)T_INV_MAX);
     }
	
	
else if(cnt_net_drv==20)
	{
     can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     }
else if(cnt_net_drv==21)
	{
     can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     } 
else if(cnt_net_drv==22)
	{
     can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     } 
else if(cnt_net_drv==23)
	{                 
	can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     } 	 
}


//-----------------------------------------------
void init_ETH(void)
{

localm[NETIF_ETH].IpAdr[0]=lc640_read_int(EE_ETH_IP_1);
localm[NETIF_ETH].IpAdr[1]=lc640_read_int(EE_ETH_IP_2);
localm[NETIF_ETH].IpAdr[2]=lc640_read_int(EE_ETH_IP_3);
localm[NETIF_ETH].IpAdr[3]=lc640_read_int(EE_ETH_IP_4);

localm[NETIF_ETH].NetMask[0]=lc640_read_int(EE_ETH_NET_MASK_1);
localm[NETIF_ETH].NetMask[1]=lc640_read_int(EE_ETH_NET_MASK_2);
localm[NETIF_ETH].NetMask[2]=lc640_read_int(EE_ETH_NET_MASK_3);
localm[NETIF_ETH].NetMask[3]=lc640_read_int(EE_ETH_NET_MASK_4);

localm[NETIF_ETH].DefGW[0]=lc640_read_int(EE_ETH_DEF_GATW_1);
localm[NETIF_ETH].DefGW[1]=lc640_read_int(EE_ETH_DEF_GATW_2);
localm[NETIF_ETH].DefGW[2]=lc640_read_int(EE_ETH_DEF_GATW_3);
localm[NETIF_ETH].DefGW[3]=lc640_read_int(EE_ETH_DEF_GATW_4); 

}


//-----------------------------------------------
static void timer_poll () 
{
//if (SysTick->CTRL & 0x10000) 
     {
     timer_tick ();
     tick = __TRUE;
     }
}


//-----------------------------------------------
signed short abs_pal(signed short in)
{
if(in<0)return -in;
else return in;
}

//-----------------------------------------------
void ADC_IRQHandler(void) {
LPC_ADC->ADCR &=  ~(7<<24);



adc_self_ch_buff[adc_self_ch_cnt]=(LPC_ADC->ADGDR>>4) & 0xFFF;/* Read Conversion Result             */
adc_self_ch_cnt++;
if(adc_self_ch_cnt<3)
	{
	LPC_ADC->ADCR |=  (1<<24);
	}
}



void SysTick_Handler (void) 	 /* SysTick Interrupt Handler (1ms)    */
{
f1000Hz=1;

if (++t100==10)
	{
	f100Hz=1;
	t100=0;
	}

if (++t50==20)
	{
	f50Hz=1;
	t50=0;
	}

if (++t10==100)
	{
	f10Hz=1;
	t10=0;
	if(bDTS) LPC_GPIO1->FIOPIN^=(1<<20); 
	}

if (++t5==200)
	{
	f5Hz=1;
	t5=0;
	}

if (++t2==500)
	{
	f2Hz=1;
	t2=0;
	}

if (++t1==1000)
	{
	f1Hz=1;
	t1=0;
	}

}
//*****************   Заставка   *****************************
void glav_menu_hndl (void){
	if(par_glav_menu[0]){
		if(delay_glav_menu==0){
		   if(intelval_glav_menu==0){
		   		if(nomer_glav_menu==0){
					if(par_glav_menu[3]=='+') {
					 	nomer_glav_menu=1;
						poz_display_temp_gm=poz_display;
						poz_display=240;						
					}
					else if(par_glav_menu[4]=='+') {
						nomer_glav_menu=2;
						poz_display_temp_gm=poz_display;
						poz_display=241;
					}
					else if(par_glav_menu[5]=='+') {
					 	nomer_glav_menu=3;
						poz_display_temp_gm=poz_display;
						poz_display=242;
					}
					else if(par_glav_menu[6]=='+') {
						nomer_glav_menu=4;
						poz_display_temp_gm=poz_display;
						poz_display=243;
					}
					else if(par_glav_menu[7]=='+') {
						nomer_glav_menu=5;
						poz_display_temp_gm=poz_display;
						poz_display=244;
					}
					else if(par_glav_menu[8]=='+') {
					 	nomer_glav_menu=6;
						poz_display_temp_gm=poz_display;
						poz_display=245;
					}
					intelval_glav_menu=par_glav_menu[2];
				}
				else if(nomer_glav_menu==1){
					if(par_glav_menu[4]=='+') {
						nomer_glav_menu=2;
						poz_display=241;
					}
					else if(par_glav_menu[5]=='+') {
					 	nomer_glav_menu=3;
						poz_display=242;
					}
					else if(par_glav_menu[6]=='+') {
						nomer_glav_menu=4;
						poz_display=243;
					}
					else if(par_glav_menu[7]=='+') {
						nomer_glav_menu=5;
						poz_display=244;
					}
					else if(par_glav_menu[8]=='+') {
					 	nomer_glav_menu=6;
						poz_display=245;
					}
					intelval_glav_menu=par_glav_menu[2];
				}
				else if(nomer_glav_menu==2){
					if(par_glav_menu[5]=='+') {
					 	nomer_glav_menu=3;
						poz_display=242;
					}
					else if(par_glav_menu[6]=='+') {
						nomer_glav_menu=4;
						poz_display=243;
					}
					else if(par_glav_menu[7]=='+') {
						nomer_glav_menu=5;
						poz_display=244;
					}
					else if(par_glav_menu[8]=='+') {
					 	nomer_glav_menu=6;
						poz_display=245;
					}
					else if(par_glav_menu[3]=='+') {
					 	nomer_glav_menu=1;
						poz_display=240;
					}
					intelval_glav_menu=par_glav_menu[2];
				}
				else if(nomer_glav_menu==3){
					if(par_glav_menu[6]=='+') {
						nomer_glav_menu=4;
						poz_display=243;
					}
					else if(par_glav_menu[7]=='+') {
						nomer_glav_menu=5;
						poz_display=244;
					}
					else if(par_glav_menu[8]=='+') {
					 	nomer_glav_menu=6;
						poz_display=245;
					}
					else if(par_glav_menu[3]=='+') {
					 	nomer_glav_menu=1;
						poz_display=240;
					}
					else if(par_glav_menu[4]=='+') {
						nomer_glav_menu=2;
						poz_display=241;
					}
					intelval_glav_menu=par_glav_menu[2];
				}
				else if(nomer_glav_menu==4){
					if(par_glav_menu[7]=='+') {
						nomer_glav_menu=5;
						poz_display=244;
					}
					else if(par_glav_menu[8]=='+') {
					 	nomer_glav_menu=6;
						poz_display=245;
					}
					else if(par_glav_menu[3]=='+') {
					 	nomer_glav_menu=1;
						poz_display=240;
					}
					else if(par_glav_menu[4]=='+') {
						nomer_glav_menu=2;
						poz_display=241;
					}
					else if(par_glav_menu[5]=='+') {
					 	nomer_glav_menu=3;
						poz_display=242;
					}
					intelval_glav_menu=par_glav_menu[2];
				}
				else if(nomer_glav_menu==5){
					if(par_glav_menu[8]=='+') {
					 	nomer_glav_menu=6;
						poz_display=245;
					}
					else if(par_glav_menu[3]=='+') {
					 	nomer_glav_menu=1;
						poz_display=240;
					}
					else if(par_glav_menu[4]=='+') {
						nomer_glav_menu=2;
						poz_display=241;
					}
					else if(par_glav_menu[5]=='+') {
					 	nomer_glav_menu=3;
						poz_display=242;
					}
					else if(par_glav_menu[6]=='+') {
						nomer_glav_menu=4;
						poz_display=243;
					}
					intelval_glav_menu=par_glav_menu[2];
				}
				else if(nomer_glav_menu==6){
					if(par_glav_menu[3]=='+') {
					 	nomer_glav_menu=1;
						poz_display=240;
					}
					else if(par_glav_menu[4]=='+') {
						nomer_glav_menu=2;
						poz_display=241;
					}
					else if(par_glav_menu[5]=='+') {
					 	nomer_glav_menu=3;
						poz_display=242;
					}
					else if(par_glav_menu[6]=='+') {
						nomer_glav_menu=4;
						poz_display=243;
					}
					else if(par_glav_menu[7]=='+') {
						nomer_glav_menu=5;
						poz_display=244;
					}
					intelval_glav_menu=par_glav_menu[2];
				}
		   
		   		
		   }
		   else intelval_glav_menu-=1;
		
		}
		else delay_glav_menu-=1;	


	}

}
//===============================================
//===============================================
#include "oleg_keypad.h"
#include "lcd_f.c"
#include "key_f.c"
//===============================================
//===============================================
int main (void)
{
short iiii_;
char mac_adr[6] = { 0x00,0x73,0x05,50,60,70 };

bDTS=1;

SystemInit();

SysTick_Config(SystemFrequency/1000 - 1); /* Generate interrupt each 1 ms   */

LPC_GPIO1->FIODIR|=(1<<20);	  // для ресета


LPC_GPIO2->FIODIR&=~BUT_MASK;
LPC_PINCON->PINMODE4&=~(0x3ff);
LPC_PINCON->PINMODE4&=~(1<<(BUT0*2))&~(1<<((BUT0*2)+1));
LPC_PINCON->PINMODE4&=~(1<<(BUT1*2))&~(1<<((BUT1*2)+1));
LPC_PINCON->PINMODE4&=~(1<<(BUT2*2))&~(1<<((BUT2*2)+1));
LPC_PINCON->PINMODE4&=~(1<<(BUT3*2))&~(1<<((BUT3*2)+1));
LPC_PINCON->PINMODE4&=~(1<<(BUT4*2))&~(1<<((BUT4*2)+1));



//beep(0,0,0,0,0); //инициализация
INIT_BP;
BEEPER_OFF;
///blink(0,0,0,0);
LED_RED_OFF;
LED_GREEN_OFF;
INIT_LED_RED;
INIT_LED_GREEN;

RELE_I_OFF;
RELE1_OFF;
RELE2_OFF;
rele_init();


X16_OFF;
X17_OFF;
sk_init();

///rtc_init();
//LPC_GPIO0->FIODIR|=(1<<POWER_NET);
///LPC_GPIO0->FIOCLR|=(1<<POWER_NET);
///LPC_GPIO1->FIOPIN^=(1<<20);
Delay(10000000);
///LPC_GPIO1->FIOPIN^=(1<<20);
///LPC_GPIO0->FIOSET|=(1<<POWER_NET);

adc_init();
//lc640_write_int(EE_MAIN_POWER_TRAP_SEND_OF_AV,1);
//lc640_write_int(EEPROM_INIT,0xFFFF);	//сбросить на умолчания	EEPROM
if(lc640_read_int(EEPROM_INIT)==0xFFFF){ //инициализация EEPROM
	lc640_write_int(EE_KUBAT1,1800); 
	lc640_write_int(EE_KI0BAT1,0);
	lc640_write_int(EE_KI1BAT1,1000);
	ethernet_default();
	lc640_write_int(EE_PAR_GLAV_MENU,0);
	lc640_write_int(EE_PAR_GLAV_MENU+2,30);
	lc640_write_int(EE_PAR_GLAV_MENU+4,3);
	lc640_write_int(EE_PAR_GLAV_MENU+6,'+');
	lc640_write_int(EE_PAR_GLAV_MENU+8,'-');
	lc640_write_int(EE_PAR_GLAV_MENU+10,'-');
	lc640_write_int(EE_PAR_GLAV_MENU+12,'-');
	lc640_write_int(EE_PAR_GLAV_MENU+14,'-');
	lc640_write_int(EE_PAR_GLAV_MENU+16,'-');
	lc640_write_int(EE_PAR_GLAV_MENU+18,'-');
	lc640_write_int(EE_MAIN_POWER_TRAP_SEND_OF_AV,1);
	lc640_write_int(EE_MAIN_POWER_TRAP_SEND_OF_NO_AV,1);
	lc640_write_int(EE_INVERTER_TEMPERATURE_TRAP_SEND_OF_AV,1);
	lc640_write_int(EE_INVERTER_TEMPERATURE_TRAP_SEND_OF_NO_AV,1);
	lc640_write_int(EE_INVERTER_VOLTAGE_TRAP_SEND_OF_AV,1);
	lc640_write_int(EE_INVERTER_VOLTAGE_TRAP_SEND_OF_NO_AV,1);
	lc640_write_int(EE_INVERTER_CURRENT_TRAP_SEND_OF_AV,1);
	lc640_write_int(EE_INVERTER_CURRENT_TRAP_SEND_OF_NO_AV,1);
	lc640_write_int(EE_BATTERY_VOLTAGE_TRAP_SEND_OF_AV,1);
	lc640_write_int(EE_BATTERY_VOLTAGE_TRAP_SEND_OF_NO_AV,1);

	lc640_write_int(EEPROM_INIT,0);
}
memo_read();


can1_init(BITRATE62_5K6_25MHZ);
FullCAN_SetFilter(0,0x18e);


///LPC_GPIO1->FIOPIN^=(1<<20);
///avar_bps_hndl(NUMB,3,1);
//  init=1;	  // для тестов

SERIAL_NUMBER=lc640_read_long(EE_SERIAL_NUMBER);

i2c_init();
ssd1306_init(SSD1306_SWITCHCAPVCC); 

if(ETH_IS_ON){
	sprintf(lcd_buffer,"\n ИНИЦИАЛИЗАЦИЯ\n   ИНТЕРНЕТ\n");
	N_sim=16;
	filling_lcd_buffer(lcd_buffer, N_sim, 4);
	bitmap_hndl16x8();
	for(iiii_=0;iiii_<1024;iiii_++)	ssd1306_data(lcd_bitmap[iiii_]);

	mac_adr[5]=*((char*)&SERIAL_NUMBER);
	mac_adr[4]=*(((char*)&SERIAL_NUMBER)+1);
	mac_adr[3]=*(((char*)&SERIAL_NUMBER)+2);

	mem_copy (own_hw_adr, mac_adr, 6);

	// snmp_Community имеет 8 разрядов по описанию. Олег.  девятый 0
	snmp_Community[0]=(char)lc640_read(EE_SNMP_READ_COMMUNITY);
	if((snmp_Community[0]==0)||(snmp_Community[0]==' '))snmp_Community[0]=0;
	snmp_Community[1]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+1);
	if((snmp_Community[1]==0)||(snmp_Community[1]==' '))snmp_Community[1]=0;
	snmp_Community[2]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+2);
	if((snmp_Community[2]==0)||(snmp_Community[2]==' '))snmp_Community[2]=0;
	snmp_Community[3]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+3);
	if((snmp_Community[3]==0)||(snmp_Community[3]==' '))snmp_Community[3]=0;
	snmp_Community[4]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+4);
	if((snmp_Community[4]==0)||(snmp_Community[4]==' '))snmp_Community[4]=0;
	snmp_Community[5]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+5);
	LPC_GPIO1->FIOPIN^=(1<<20);
	if((snmp_Community[5]==0)||(snmp_Community[5]==' '))snmp_Community[5]=0;
	snmp_Community[6]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+6);
	if((snmp_Community[6]==0)||(snmp_Community[6]==' '))snmp_Community[6]=0;
	snmp_Community[7]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+7);
	if((snmp_Community[7]==0)||(snmp_Community[7]==' '))snmp_Community[7]=0;
	snmp_Community[8]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+8);
	if((snmp_Community[8]==0)||(snmp_Community[8]==' '))snmp_Community[8]=0;
	snmp_Community[9]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+9); 
	if((snmp_Community[9]==0)||(snmp_Community[9]==' '))snmp_Community[9]=0;
	
	/*
	snmp_Community[10]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+10); 
	if((snmp_Community[10]==0)||(snmp_Community[10]==' '))snmp_Community[10]=0;
	snmp_Community[11]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+11); 
	if((snmp_Community[11]==0)||(snmp_Community[11]==' '))snmp_Community[11]=0;
	snmp_Community[12]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+12); 
	if((snmp_Community[12]==0)||(snmp_Community[12]==' '))snmp_Community[12]=0;
	snmp_Community[13]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+13); 
	if((snmp_Community[13]==0)||(snmp_Community[13]==' '))snmp_Community[13]=0;
	snmp_Community[14]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+14); 
	if((snmp_Community[14]==0)||(snmp_Community[14]==' '))snmp_Community[14]=0;
	snmp_Community[15]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+15); 
	if((snmp_Community[15]==0)||(snmp_Community[15]==' '))snmp_Community[15]=0;
	*/
	snmp_Community[9]=0;
	snmp_PortNum  = lc640_read_int(EE_SNMP_READ_PORT);
	snmp_TrapPort = lc640_read_int(EE_SNMP_WRITE_PORT);
	init_TcpNet ();
	init_ETH();
}



//tcp_init_cnt=10;

//poz_display=36; 
//poz_kursor=1;
//rejim_led=1;
//rejim_avar_led=6;

delay_glav_menu=par_glav_menu[1];
bDTS=0;
while(1)
	{
	if(f1000Hz)
		{
		f1000Hz=0;
		adc_drv7();
		}
	if(f100Hz)
		{
		f100Hz=0;
		LPC_GPIO1->FIODIR^=(1<<20);	 // сброс супервизора
		//blinker();
		//beeper();
		//led_beep();
		count_rejim_led+=1;
		keypad_long  (K_R,&count_right,&flag_right);
		keypad_long  (K_L,&count_left,&flag_left);
		keypad_long  (K_U,&count_up,&flag_up);
		keypad_long  (K_D,&count_down,&flag_down);
		keypad_long  (K_F,&count_f,&flag_f);
		if(flag_right||flag_left||flag_down||flag_up||flag_f) {
			analiz_keypad();
			if(nomer_glav_menu) {poz_display=poz_display_temp_gm; nomer_glav_menu=0;}
			delay_glav_menu=par_glav_menu[1]; 
			//lcd_out(); 
		}

		
																						
		
		}
	if(f50Hz)
		{
		f50Hz=0;
		if (init) net_drv(); // задержка опросов иначе зависает кан

		}
	if(f10Hz)
		{
		f10Hz=0;
		LPC_GPIO1->FIOPIN^=(1<<20);

		unet_drv();			// следилка за сетью 220

		if(main_cnt>2)inv_drv(NUMB);

		timer_poll ();
     	main_TcpNet ();

		//ind_hndl();
		
		if(tcp_init_cnt)
			{
			tcp_init_cnt--;
			if(!tcp_init_cnt)
				{
				
	bDTS=1;
	snmp_Community[0]=(char)lc640_read(EE_SNMP_READ_COMMUNITY);
	if((snmp_Community[0]==0)||(snmp_Community[0]==' '))snmp_Community[0]=0;
	snmp_Community[1]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+1);
	if((snmp_Community[1]==0)||(snmp_Community[1]==' '))snmp_Community[1]=0;
	snmp_Community[2]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+2);
	if((snmp_Community[2]==0)||(snmp_Community[2]==' '))snmp_Community[2]=0;
	snmp_Community[3]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+3);
	if((snmp_Community[3]==0)||(snmp_Community[3]==' '))snmp_Community[3]=0;
	snmp_Community[4]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+4);
	if((snmp_Community[4]==0)||(snmp_Community[4]==' '))snmp_Community[4]=0;
	snmp_Community[5]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+5);
	if((snmp_Community[5]==0)||(snmp_Community[5]==' '))snmp_Community[5]=0;
	snmp_Community[6]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+6);
	if((snmp_Community[6]==0)||(snmp_Community[6]==' '))snmp_Community[6]=0;
	snmp_Community[7]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+7);
	if((snmp_Community[7]==0)||(snmp_Community[7]==' '))snmp_Community[7]=0;
	snmp_Community[8]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+8);
	if((snmp_Community[8]==0)||(snmp_Community[8]==' '))snmp_Community[8]=0;
	snmp_Community[9]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+9); 
	if((snmp_Community[9]==0)||(snmp_Community[9]==' '))snmp_Community[9]=0;

	/*
	snmp_Community[10]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+10); 
	if((snmp_Community[10]==0)||(snmp_Community[10]==' '))snmp_Community[10]=0;
	snmp_Community[11]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+11); 
	if((snmp_Community[11]==0)||(snmp_Community[11]==' '))snmp_Community[11]=0;
	snmp_Community[12]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+12); 
	if((snmp_Community[12]==0)||(snmp_Community[12]==' '))snmp_Community[12]=0;
	snmp_Community[13]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+13); 
	if((snmp_Community[13]==0)||(snmp_Community[13]==' '))snmp_Community[13]=0;
	snmp_Community[14]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+14); 
	if((snmp_Community[14]==0)||(snmp_Community[14]==' '))snmp_Community[14]=0;
	snmp_Community[15]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+15); 
	if((snmp_Community[15]==0)||(snmp_Community[15]==' '))snmp_Community[15]=0;
	*/
	snmp_Community[9]=0;
	snmp_PortNum  = lc640_read_int(EE_SNMP_READ_PORT);
	snmp_TrapPort = lc640_read_int(EE_SNMP_WRITE_PORT);
	init_TcpNet ();
	init_ETH();
	bDTS=0;
				}
			}
		}
	if(f5Hz)
		{
		f5Hz=0;
		avar_hndl();

		
		memo_read();

		if( (poz_display>19 && poz_display<24) || (poz_display>34 && poz_display<38) ) can1_out(27,27,0xFD,0,0,0,0,0);
		
		matemat();
		rele_hndl();
		snmp_data();
		}
	if(f2Hz)
		{
		f2Hz=0;
 		lcd_out();
		if(flash_1S) {
			flash_1S=0; 
			if(data_can_reset<5) data_can_reset+=1;
			
		}
		else {flash_1S=1;}
		if(data_can_reset==4){
			snmp_inverter_voltage=0;
			snmp_inverter_current=0;
			snmp_inverter_power=0;
			snmp_main_voltage=0;
			snmp_inverter_temperature=0;
		}

		}
	if(f1Hz)
		{
		f1Hz=0;
		if(poz_display<20 ) count_kalibr_i_bat+=1;
		else count_kalibr_i_bat=0;
		if(count_kalibr_i_bat==600) RELE_I_ON;
		if(count_kalibr_i_bat==605) {
			Kibat0[0]=adc_buff_[1];
			lc640_write_int(EE_KI0BAT1,Kibat0[0]);
		}
		if(count_kalibr_i_bat>605) {count_kalibr_i_bat=0; RELE_I_OFF; }
		
		
		if(main_cnt<1000)main_cnt++;

		if (poz_display<10 || (poz_display>239 && poz_display<246) ) glav_menu_hndl();



//snmp_trap_send("Main power alarm. Power source is ACB",1,1);
	 
		}
	}// end while
	
}
