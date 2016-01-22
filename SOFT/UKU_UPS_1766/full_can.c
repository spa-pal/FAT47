#include "main.h"
#include <LPC17xx.H>
#include "full_can.h"
#include "cmd.h"
//#include "mess.h"
#include "global_define.h"
#include "avar_hndl.h"
//#include "eeprom_map.h"
#include "control.h"
//#include "25lc640.h"

// Counts number of filters (CAN message objects) used so far
short volatile gCANFilter = 0;

char ptr_can1_tx_wr,ptr_can1_tx_rd;
long can1_info[8];
long can1_id[8];
long can1_data[8];
long can1_datb[8];
																							 
char ptr_can2_tx_wr,ptr_can2_tx_rd;

long can2_info[8];
long can2_id[8];
long can2_data[8];
long can2_datb[8];

unsigned short rotor_can[6];

extern signed short snmp_inverter_voltage;
extern signed short snmp_inverter_current;
extern signed short snmp_inverter_temperature;
extern signed short snmp_inverter_power;
extern signed short snmp_main_voltage;
extern unsigned char kontrol_seti, upravl_shim;

// FullCAN Message List
FULLCAN_MSG volatile gFullCANList[MAX_FILTERS];

char bR;
char RXBUFF[40],TXBUFF[40];
char bIN,bIN2;
char bd_dumm[25];
char bd[25];
char TX_len;
//char bOUT;
char RXBUFF2[40],TXBUFF2[40];
extern char can_tx_cnt;
extern char can_tx_cnt2;
char bOUT_FREE=1;
char bOUT_FREE2=1;
char rotor_rotor_rotor[2];
char can_tx_cnt;
char can_rotor[10];

const char Table87[]={
0x00, 0x0E, 0x1C, 0x12, 0x38, 0x36, 0x24, 0x2A, 0x70, 0x7E, 0x6C, 0x62, 0x48, 0x46, 0x54, 0x5A,
0xE0, 0xEE, 0xFC, 0xF2, 0xD8, 0xD6, 0xC4, 0xCA, 0x90, 0x9E, 0x8C, 0x82, 0xA8, 0xA6, 0xB4, 0xBA,
0xCE, 0xC0, 0xD2, 0xDC, 0xF6, 0xF8, 0xEA, 0xE4, 0xBE, 0xB0, 0xA2, 0xAC, 0x86, 0x88, 0x9A, 0x94,
0x2E, 0x20, 0x32, 0x3C, 0x16, 0x18, 0x0A, 0x04, 0x5E, 0x50, 0x42, 0x4C, 0x66, 0x68, 0x7A, 0x74,
0x92, 0x9C, 0x8E, 0x80, 0xAA, 0xA4, 0xB6, 0xB8, 0xE2, 0xEC, 0xFE, 0xF0, 0xDA, 0xD4, 0xC6, 0xC8,
0x72, 0x7C, 0x6E, 0x60, 0x4A, 0x44, 0x56, 0x58, 0x02, 0x0C, 0x1E, 0x10, 0x3A, 0x34, 0x26, 0x28,
0x5C, 0x52, 0x40, 0x4E, 0x64, 0x6A, 0x78, 0x76, 0x2C, 0x22, 0x30, 0x3E, 0x14, 0x1A, 0x08, 0x06,
0xBC, 0xB2, 0xA0, 0xAE, 0x84, 0x8A, 0x98, 0x96, 0xCC, 0xC2, 0xD0, 0xDE, 0xF4, 0xFA, 0xE8, 0xE6,
0x2A, 0x24, 0x36, 0x38, 0x12, 0x1C, 0x0E, 0x00, 0x5A, 0x54, 0x46, 0x48, 0x62, 0x6C, 0x7E, 0x70,
0xCA, 0xC4, 0xD6, 0xD8, 0xF2, 0xFC, 0xEE, 0xE0, 0xBA, 0xB4, 0xA6, 0xA8, 0x82, 0x8C, 0x9E, 0x90,
0xE4, 0xEA, 0xF8, 0xF6, 0xDC, 0xD2, 0xC0, 0xCE, 0x94, 0x9A, 0x88, 0x86, 0xAC, 0xA2, 0xB0, 0xBE,
0x04, 0x0A, 0x18, 0x16, 0x3C, 0x32, 0x20, 0x2E, 0x74, 0x7A, 0x68, 0x66, 0x4C, 0x42, 0x50, 0x5E,
0xB8, 0xB6, 0xA4, 0xAA, 0x80, 0x8E, 0x9C, 0x92, 0xC8, 0xC6, 0xD4, 0xDA, 0xF0, 0xFE, 0xEC, 0xE2,
0x58, 0x56, 0x44, 0x4A, 0x60, 0x6E, 0x7C, 0x72, 0x28, 0x26, 0x34, 0x3A, 0x10, 0x1E, 0x0C, 0x02,
0x76, 0x78, 0x6A, 0x64, 0x4E, 0x40, 0x52, 0x5C, 0x06, 0x08, 0x1A, 0x14, 0x3E, 0x30, 0x22, 0x2C,
0x96, 0x98, 0x8A, 0x84, 0xAE, 0xA0, 0xB2, 0xBC, 0xE6, 0xE8, 0xFA, 0xF4, 0xDE, 0xD0, 0xC2, 0xCC};



const char Table95[]={
0x00, 0x2A, 0x54, 0x7E, 0xA8, 0x82, 0xFC, 0xD6, 0x7A, 0x50, 0x2E, 0x04, 0xD2, 0xF8, 0x86, 0xAC,
0xF4, 0xDE, 0xA0, 0x8A, 0x5C, 0x76, 0x08, 0x22, 0x8E, 0xA4, 0xDA, 0xF0, 0x26, 0x0C, 0x72, 0x58,
0xC2, 0xE8, 0x96, 0xBC, 0x6A, 0x40, 0x3E, 0x14, 0xB8, 0x92, 0xEC, 0xC6, 0x10, 0x3A, 0x44, 0x6E,
0x36, 0x1C, 0x62, 0x48, 0x9E, 0xB4, 0xCA, 0xE0, 0x4C, 0x66, 0x18, 0x32, 0xE4, 0xCE, 0xB0, 0x9A,
0xAE, 0x84, 0xFA, 0xD0, 0x06, 0x2C, 0x52, 0x78, 0xD4, 0xFE, 0x80, 0xAA, 0x7C, 0x56, 0x28, 0x02,
0x5A, 0x70, 0x0E, 0x24, 0xF2, 0xD8, 0xA6, 0x8C, 0x20, 0x0A, 0x74, 0x5E, 0x88, 0xA2, 0xDC, 0xF6,
0x6C, 0x46, 0x38, 0x12, 0xC4, 0xEE, 0x90, 0xBA, 0x16, 0x3C, 0x42, 0x68, 0xBE, 0x94, 0xEA, 0xC0,
0x98, 0xB2, 0xCC, 0xE6, 0x30, 0x1A, 0x64, 0x4E, 0xE2, 0xC8, 0xB6, 0x9C, 0x4A, 0x60, 0x1E, 0x34,
0x76, 0x5C, 0x22, 0x08, 0xDE, 0xF4, 0x8A, 0xA0, 0x0C, 0x26, 0x58, 0x72, 0xA4, 0x8E, 0xF0, 0xDA,
0x82, 0xA8, 0xD6, 0xFC, 0x2A, 0x00, 0x7E, 0x54, 0xF8, 0xD2, 0xAC, 0x86, 0x50, 0x7A, 0x04, 0x2E,
0xB4, 0x9E, 0xE0, 0xCA, 0x1C, 0x36, 0x48, 0x62, 0xCE, 0xE4, 0x9A, 0xB0, 0x66, 0x4C, 0x32, 0x18,
0x40, 0x6A, 0x14, 0x3E, 0xE8, 0xC2, 0xBC, 0x96, 0x3A, 0x10, 0x6E, 0x44, 0x92, 0xB8, 0xC6, 0xEC, 
0xD8, 0xF2, 0x8C, 0xA6, 0x70, 0x5A, 0x24, 0x0E, 0xA2, 0x88, 0xF6, 0xDC, 0x0A, 0x20, 0x5E, 0x74, 
0x2C, 0x06, 0x78, 0x52, 0x84, 0xAE, 0xD0, 0xFA, 0x56, 0x7C, 0x02, 0x28, 0xFE, 0xD4, 0xAA, 0x80, 
0x1A, 0x30, 0x4E, 0x64, 0xB2, 0x98, 0xE6, 0xCC, 0x60, 0x4A, 0x34, 0x1E, 0xC8, 0xE2, 0x9C, 0xB6, 
0xEE, 0xC4, 0xBA, 0x90, 0x46, 0x6C, 0x12, 0x38, 0x94, 0xBE, 0xC0, 0xEA, 0x3C, 0x16, 0x68, 0x42};



char can_debug_plazma[2][10];
volatile uint32_t CANStatus;


//-----------------------------------------------
char CRC1_in(void)
{
char r,j,lb;
lb=(RXBUFF[1]&0x1f)+0x04;
r=RXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(RXBUFF[j]^Table87[r]);
	}
if(r==0)r=0xFF;
return r;	
} 

////-----------------------------------------------
char CRC1_out(void)
{
char r,j,lb;
lb=(TXBUFF[1]&0x1f)+0x04;
r=TXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(TXBUFF[j]^Table87[r]);
	}
if(r==0)r=0xFF;
return r;	
} 


//-----------------------------------------------
void can1_out(char dat0,char dat1,char dat2,char dat3,char dat4,char dat5,char dat6,char dat7)
{
//new_rotor[0]++;
can1_info[ptr_can1_tx_wr]=((8UL)<<16)&0x000f0000UL;
can1_id[ptr_can1_tx_wr]=0x0000009eUL;
*((char*)&can1_data[ptr_can1_tx_wr])=dat0;
*(((char*)&can1_data[ptr_can1_tx_wr])+1)=dat1;
*(((char*)&can1_data[ptr_can1_tx_wr])+2)=dat2;
*(((char*)&can1_data[ptr_can1_tx_wr])+3)=dat3;
*((char*)&can1_datb[ptr_can1_tx_wr])=dat4;
*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=dat5;
*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=dat6;
*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=dat7;	
ptr_can1_tx_wr++;
if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;


if(bOUT_FREE)
	{
	//rotor_rotor_rotor[1]++;
//	new_rotor[1]++;
	LPC_CAN1->TFI1=can1_info[ptr_can1_tx_rd];
     LPC_CAN1->TID1=can1_id[ptr_can1_tx_rd];
     LPC_CAN1->TDA1=can1_data[ptr_can1_tx_rd];
     LPC_CAN1->TDB1=can1_datb[ptr_can1_tx_rd];
     LPC_CAN1->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
     bOUT_FREE=0;	
	}
}	
	

////-----------------------------------------------
void can_adr_hndl(void)
{
	TXBUFF[2]=RXBUFF[3];
	TXBUFF[3]=RXBUFF[2];
	TXBUFF[4]=((RXBUFF[4]&0xF0)>>4)|((RXBUFF[4]&0x0f)<<4);
	TXBUFF[5]=((RXBUFF[5]&0xF0)>>4)|((RXBUFF[5]&0x0f)<<4);	
}	


//-----------------------------------------------
extern unsigned char data_can_reset;
extern signed short snmp_battery_voltage;
extern unsigned char delete_temp;
extern unsigned char sw_red, sw_green;
extern unsigned char avar_t70, avar_t80, avar_p1, avar_p2, avar_akb_umin;
#include "beeper_drv.h"
void can_in_an1(void)
{
//char i;
//signed short temp_SS;
//char slave_num;

//if(!bIN2) goto CAN_IN_AN1_end; 

//can_debug_plazma[1][2]++;
can_rotor[1]++;

//if((RXBUFF[0]==sub_ind1)&&(RXBUFF[1]==PUTID)&&(RXBUFF[2]==0xdd)&&(RXBUFF[3]==0xdd)&&(sub_ind==6))
//	{
//	mess_send(MESS2IND_HNDL,PARAM_U_AVT_GOOD,0,10);
//	}
data_can_reset=0;

if((RXBUFF[0]&0x1f)==27){

	if(RXBUFF[1]==0xDD)  /**/
     {
		snmp_inverter_current= (((unsigned short)RXBUFF[3])<<8)|RXBUFF[2];
		snmp_inverter_power=0;
		snmp_inverter_power= ( snmp_inverter_power | ((unsigned short)RXBUFF[5]<<8) ) |RXBUFF[4];
		snmp_inverter_voltage= (((unsigned short)RXBUFF[7])<<8)|RXBUFF[6];	// Uнагрузки
     }

	else if(RXBUFF[1]==0xDE)  /**/
     {
		snmp_inverter_temperature= RXBUFF[2];
		if(RXBUFF[3]&0x02) avar_t70=1;
		else avar_t70=0;
		if(RXBUFF[2]&0x02) avar_t80=1;
		else avar_t80=0;

		/*
		if(rejim_avar_led==0 && RXBUFF[3]&0x02)	rejim_avar_led=2;
		else if(rejim_avar_led==0 && RXBUFF[3]&0x04)	rejim_avar_led=1;
		else if( (rejim_avar_led==2 || rejim_avar_led==1) && RXBUFF[3]&0x06==0 ) rejim_avar_led=0;
		*/
		snmp_main_voltage= (((unsigned short)RXBUFF[5])<<8)|RXBUFF[4];
     }
	else if(RXBUFF[1]==0xDA)  /**/
     {
		snmp_battery_voltage= (((unsigned short)RXBUFF[3])<<8)|RXBUFF[2];

		
delete_temp=RXBUFF[4];

		/*
		if(rejim_avar_led==3 && RXBUFF[4]&0x02==0 )	rejim_avar_led=0;
		else if(rejim_avar_led==0 && RXBUFF[4]&0x02) rejim_avar_led=3;

		if(rejim_avar_led==4 && RXBUFF[4]&0x04==0)	rejim_avar_led=0;
		else if(rejim_avar_led==0 && RXBUFF[4]&0x04) rejim_avar_led=4;

		if(rejim_avar_led==5 && RXBUFF[4]&0x08==0)	rejim_avar_led=0;
		else if(rejim_avar_led==0 && RXBUFF[4]&0x08) rejim_avar_led=5;

		if(rejim_avar_led==6 && RXBUFF[4]&0x10==0)	rejim_avar_led=0;
		else if(rejim_avar_led==0 && RXBUFF[4]&0x10) rejim_avar_led=6;
		*/

		if(RXBUFF[4]&0x01==0) avar_akb_umin=1;
		else avar_akb_umin=0;

		if(RXBUFF[4]&0x02==0) avar_p1=1;
		else avar_p1=0;

		if(RXBUFF[4]&0x04==0) avar_p2=1;
		else avar_p2=0;


		if(RXBUFF[4]&0x40) sw_green=1;
		else sw_green=0;

		if(RXBUFF[4]&0x20) sw_red=1;
		else sw_red=0;

		if(RXBUFF[4]&0x80) BEEPER_ON;
		else BEEPER_OFF;
		
     }
	else if(RXBUFF[1]==0xDF)  /*пакет конфигурирования*/
     {
		kontrol_seti=RXBUFF[5];
		upravl_shim=RXBUFF[6];	
     }
	 else if(RXBUFF[1]==0xDB)  /*пакет конфигурирования*/
     {
		u_bat_off=RXBUFF[2];
		u_bat_on=RXBUFF[3];	
     }
}


//CAN_IN_AN1_end:
bIN2=0;
}





  
/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 
void CAN_ISR_Rx1( void )
{
unsigned int buf;
unsigned int *pDest;
char temp;
char *ptr,j;
//can_cnt++;

rotor_can[0]++;

  if (!(LPC_CAN1->RFS & 0xC0000400L))
  { // 11-bit ID, no RTR, matched a filter

rotor_can[1]++;
    // initialize destination pointer
    // filter number is in lower 10 bits of C1RFS
    pDest = (unsigned int *) &(gFullCANList[(LPC_CAN1->RFS & 0x000003FFL)].Dat1);
    
    // calculate contents for first entry into FullCAN list
    buf = LPC_CAN1->RFS & 0xC00F0000L; // mask FF, RTR and DLC
    buf |= 0x01002000L; // set semaphore to 01b and CAN port to 1
    buf |= LPC_CAN1->RID & 0x000007FFL; // get CAN message ID

    // now copy entire message to FullCAN list
    *pDest = buf; 
    pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatA
    *pDest = LPC_CAN1->RDA; 
    pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatB
    *pDest = LPC_CAN1->RDB; 

    // now set the sempahore to complete
    buf |= 0x03000000L; // set semaphore to 11b
    pDest -= 2; // set to gFullCANList[(C1RFS & 0x000003FFL)].Dat1
    *pDest = buf; 
    
	temp=(char)gFullCANList[0].DatA;
	if(temp==0x30) bR=0;
	else bR++;
	
	temp=(char)(((gFullCANList[0].Dat1)>>16)&0x0f); 
     
     ptr=(char*)(&gFullCANList[0].DatA);
	
	for(j=0;j<temp;j++)
		{
		RXBUFF[j]=*ptr;
		ptr++;
		}
	can_in_an1();
	    
   
  }

  LPC_CAN1->CMR = 0x04; // release receive buffer
}

/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 
//void CAN_ISR_Rx2( void ) 
//{
//
//unsigned int buf;
//unsigned int *pDest;
//char temp;
//char *ptr,j;
////can_cnt++;	
//can_rotor[0]++;
//if (!(LPC_CAN2->RFS & 0xC0000400L))
//  { // 11-bit ID, no RTR, matched a filter
//
//
//    // initialize destination pointer
//    // filter number is in lower 10 bits of C1RFS
//    pDest = (unsigned int *) &(gFullCANList[(LPC_CAN2->RFS & 0x000003FFL)].Dat1);
//    
//    // calculate contents for first entry into FullCAN list
//    buf = LPC_CAN2->RFS & 0xC00F0000L; // mask FF, RTR and DLC
//    buf |= 0x01002000L; // set semaphore to 01b and CAN port to 1
//    buf |= LPC_CAN2->RID & 0x000007FFL; // get CAN message ID
//
//    // now copy entire message to FullCAN list
//    *pDest = buf; 
//    pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatA
//    *pDest = LPC_CAN2->RDA; 
//    pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatB
//    *pDest = LPC_CAN2->RDB; 
//
//    // now set the sempahore to complete
//    buf |= 0x03000000L; // set semaphore to 11b
//    pDest -= 2; // set to gFullCANList[(C1RFS & 0x000003FFL)].Dat1
//    *pDest = buf; 
//    
//	temp=(char)gFullCANList[0].DatA;
//	if(temp==0x30) bR=0;
//	else bR++;
//	
//	temp=(char)(((gFullCANList[0].Dat1)>>16)&0x0f); 
//     
//     ptr=(char*)(&gFullCANList[0].DatA);
//	
//	for(j=0;j<temp;j++)
//		{
//		RXBUFF[j]=*ptr;
//		ptr++;
//		}
//		
//  	can_in_an2();
//   
//    
//  }
//
//LPC_CAN2->CMR = 0x04; // release receive buffer
//}

/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 

void can_isr_tx1 (void) 
{
//unsigned int buf;
//unsigned int *pDest;
//char temp;
//char *ptr,j;

//plazma_can2++;

can_tx_cnt++;

rotor_can[5]++;

if(ptr_can1_tx_wr!=ptr_can1_tx_rd)
	{
	LPC_CAN1->TFI1=can1_info[ptr_can1_tx_rd];
     LPC_CAN1->TID1=can1_id[ptr_can1_tx_rd];
     LPC_CAN1->TDA1=can1_data[ptr_can1_tx_rd];
     LPC_CAN1->TDB1=can1_datb[ptr_can1_tx_rd];
     LPC_CAN1->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
	}
else bOUT_FREE=1;
//temp=LPC_CAN1->ICR;

}

/***************************************************************************/
void can_isr_tx2 (void) 
{

}


/**************************************************************************
Initialization of a CAN interface
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short can1_init (unsigned int can_btr)
{
LPC_SC->PCONP |= (1<<13);  /* Enable CAN1 and CAN2 clock */

LPC_PINCON->PINSEL0 &= ~0x0000000F;  /* CAN1 is p0.0 and p0.1	*/
LPC_PINCON->PINSEL0 |= 0x00000005;

gCANFilter = 0; // Reset and disable all message filters

LPC_CANAF->AFMR = 0x00000001L; // Acceptance Filter Mode Register = off !

LPC_CAN1->MOD = 1; // Go into Reset mode

LPC_CAN1->IER = 0;// Disable All Interrupts

LPC_CAN1->GSR = 0; // Clear Status register

LPC_CAN1->BTR = can_btr; // Set bit timing

//LPC_CAN1->IER |=(1<<0)|(1<<1)|(1<<9)|(1<<10); // Enable Receive & Transmit Interrupt

LPC_CAN1->MOD = 0; // Enter Normal Operating Mode



NVIC_EnableIRQ(CAN_IRQn);
LPC_CAN1->IER =0x0003;
return 1;
}

/**************************************************************************
Initialization of a CAN interface
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short can2_init (unsigned short can_rx_vector, unsigned short can_tx_vector, unsigned int can_btr)
{
return 1;
}

/**************************************************************************
Setting a CAN receive filter
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short FullCAN_SetFilter  (
                         unsigned short can_port, // CAN interface number
                         unsigned int CANID // 11-bit CAN ID
                         )
{
unsigned int p, n;
unsigned int buf0, buf1;
unsigned int ID_lower, ID_upper;
unsigned int candata;
unsigned int *pAddr;


// Acceptance Filter Mode Register = off !
LPC_CANAF->AFMR = 0x00000001L;

if (gCANFilter == 0)
     {    
     // First call, init entry zero
     gFullCANList[0].Dat1 = 0x000037FFL; // CAN 1, disabled and unused
     }
if (gCANFilter >= MAX_FILTERS)
     {
     return 0;
     }

CANID &= 0x000007FFL; // Mask out 11-bit ID
CANID |= (can_port << 13); // Put can_port info in bits 13-15

// Filters must be sorted by interface, then by priority
// new filter is sorted into array
p = 0;
while (p < gCANFilter) // loop through all existing filters 
     {
     if ((gFullCANList[p].Dat1 & 0x0000FFFFL) > CANID)
          {
          break;
          }
     p++;
     }

// insert new filter here
buf0 = gFullCANList[p].Dat1; // save current entry
gFullCANList[p].Dat1 = CANID; // insert the new entry

// move all remaining entries one row up
gCANFilter++;
while (p < gCANFilter)
     {
     p++;
     buf1 = gFullCANList[p].Dat1;
     gFullCANList[p].Dat1 = buf0;
     buf0 = buf1;
     }

// Now work on Acceptance Filter Configuration     
// Set CAN filter for 11-bit standard identifiers
p = 0;

// Set pointer for Standard Frame Individual
// Standard Frame Explicit
LPC_CANAF->SFF_sa = p;

pAddr = (unsigned int *) LPC_CANAF_RAM_BASE;
for (n = 0; n < ((gCANFilter+1)/2); n++)
     {
     ID_lower = gFullCANList[n * 2].Dat1 & 0x0000FFFFL;
     ID_upper = gFullCANList[n * 2 + 1].Dat1 & 0x0000FFFFL;
     candata = (ID_lower << 16) + ID_upper;
     *pAddr = candata;
     p += 4;
     pAddr++;
     }

// p is still pointing to ENDofTable;
  
// Set pointer for Standard Frame Groups
// Standard Frame Group Start Address Register
LPC_CANAF->SFF_GRP_sa = p;

// Set pointer for Extended Frame Individual
// Extended Frame Start Address Register
LPC_CANAF->EFF_sa = p;

// Set pointer for Extended Frame Groups
// Extended Frame Group Start Address Register
LPC_CANAF->EFF_GRP_sa = p;

// Set ENDofTable 
// End of AF Tables Register
LPC_CANAF->ENDofTable = p;

// Acceptance Filter Mode Register, start using filter
LPC_CANAF->AFMR = 0;
  
return 1;
}

//-----------------------------------------------
void CAN_IRQHandler(void)  
{
//can_rotor[0]++;
CANStatus = LPC_CAN1->ICR;
//new_rotor[3]=CANStatus;
//new_rotor[4]=CANStatus>>16;
//plazma_can++;
//rotor_rotor_rotor[0]++;		
if ( CANStatus & (1 << 0) )
     {
	CAN_ISR_Rx1();
     }

if ( CANStatus & (1 << 1) )
     {
	can_isr_tx1();
	canzx_tmp=canzx_tmp+1;
     }

return;
}










