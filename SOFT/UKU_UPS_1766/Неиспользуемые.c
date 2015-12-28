//-----------------------------------------------
void but_an(void)
{
if(!n_but)goto but_an_end;

snmp_trap_send("Main power alarm. Power source is ACB",1,1);


if(ind==iMn)
	{
	if((but==butLRC_)||(but==butE_))
		{
		ind=iDef_net_set;
		}
	if(but==butC_)
		{
		ind=iK;
		sub_ind=0;
		}
	if(but==butE)
		{
		snmp_trap_send("Main power alarm. Power source is ACB",1,1);
		}

	}

else if(ind==iDef_net_set)
	{
	if((but==butLRC_)||(but==butE_))
		{
		char i;

		ind=iMn;

			ETH_IP_1=192;
			ETH_IP_2=168;
			ETH_IP_3=1;
			ETH_IP_4=1;
			lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
			lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
			lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
			lc640_write_int(EE_ETH_IP_4,ETH_IP_4); 

			ETH_NET_MASK_1=255;
			ETH_NET_MASK_2=255;
			ETH_NET_MASK_3=255;
			ETH_NET_MASK_4=0;
			lc640_write_int(EE_ETH_NET_MASK_1,ETH_NET_MASK_1);
			lc640_write_int(EE_ETH_NET_MASK_2,ETH_NET_MASK_2);
			lc640_write_int(EE_ETH_NET_MASK_3,ETH_NET_MASK_3);
			lc640_write_int(EE_ETH_NET_MASK_4,ETH_NET_MASK_4);

			ETH_DEF_GATW_1=192;
			ETH_DEF_GATW_2=168;
			ETH_DEF_GATW_3=1;
			ETH_DEF_GATW_4=254;
			lc640_write_int(EE_ETH_DEF_GATW_1,ETH_DEF_GATW_1);
			lc640_write_int(EE_ETH_DEF_GATW_2,ETH_DEF_GATW_2);
			lc640_write_int(EE_ETH_DEF_GATW_3,ETH_DEF_GATW_3);
			lc640_write_int(EE_ETH_DEF_GATW_4,ETH_DEF_GATW_4);

			snmp_snmp_settings_read_community[0]='p';
			snmp_snmp_settings_read_community[1]='u';
			snmp_snmp_settings_read_community[2]='b';
			snmp_snmp_settings_read_community[3]='l';
			snmp_snmp_settings_read_community[4]='i';
			snmp_snmp_settings_read_community[5]='c';
			snmp_snmp_settings_read_community[6]=0;
			snmp_snmp_settings_read_community[7]=0;
			snmp_snmp_settings_read_community[8]=0;
			snmp_snmp_settings_read_community[9]=0;
			snmp_snmp_settings_read_community[10]=0;
			snmp_snmp_settings_read_community[11]=0;
			snmp_snmp_settings_read_community[12]=0;
			snmp_snmp_settings_read_community[13]=0;
			snmp_snmp_settings_read_community[14]=0;
			snmp_snmp_settings_read_community[15]=0;

			for(i=0;i<16;i++)
				{
				lc640_write(EE_SNMP_READ_COMMUNITY+i,snmp_snmp_settings_read_community[i]);
				}

			SNMP_READ_PORT=161;
			lc640_write_int(EE_SNMP_READ_PORT,SNMP_READ_PORT);
			SNMP_WRITE_PORT=162;
			lc640_write_int(EE_SNMP_WRITE_PORT,SNMP_WRITE_PORT); /**/

		}
	}

else if(ind==iK)
	{
	if(but==butC_)
		{
		ind=iMn;
		}
	if(but==butC)
		{
		sub_ind++;
		if(sub_ind>=6)sub_ind=0;
		}
	else if(sub_ind==0)
		{
		if(but==butR)
			{
			can1_out(NUMB,NUMB,KLBR,(0*16)+2,(0*16)+2,0,0,0);
			}
		else if(but==butR_)
			{
			can1_out(NUMB,NUMB,KLBR,(0*16)+3,(0*16)+3,0,0,0);
			}
		else if(but==butL)
			{
			can1_out(NUMB,NUMB,KLBR,(0*16)+4,(0*16)+4,0,0,0);
			}
		else if(but==butL_)
			{
			can1_out(NUMB,NUMB,KLBR,(0*16)+5,(0*16)+5,0,0,0);
			}

		}
	else if(sub_ind==1)
		{
		if(but==butR)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+2,(2*16)+2,0,0,0);
			}
		else if(but==butR_)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+3,(2*16)+3,0,0,0);
			}
		else if(but==butL)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+4,(2*16)+4,0,0,0);
			}
		else if(but==butL_)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+5,(2*16)+5,0,0,0);
			}
		else if(but==butLR)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+1,(2*16)+1,0,0,0);
			}
		}

	else if(sub_ind==2)
		{
		if(but==butR)
			{
			can1_out(NUMB,NUMB,KLBR,(3*16)+2,(3*16)+2,0,0,0);
			}
		else if(but==butR_)
			{
			can1_out(NUMB,NUMB,KLBR,(3*16)+3,(3*16)+3,0,0,0);
			}
		else if(but==butL)
			{
			can1_out(NUMB,NUMB,KLBR,(3*16)+4,(3*16)+4,0,0,0);
			}
		else if(but==butL_)
			{
			can1_out(NUMB,NUMB,KLBR,(3*16)+5,(3*16)+5,0,0,0);
			}

		}
#define UAKB_L 1500
#define UAKB_H 2100
	else if(sub_ind==3)
		{
		if(but==butR)
			{
			Kubat[0]+=2;
			gran(&Kubat[0],UAKB_L,UAKB_H);
			lc640_write_int(EE_KUBAT1,Kubat[0]);
			}
		else if(but==butR_)
			{
			Kubat[0]+=5;
			gran(&Kubat[0],UAKB_L,UAKB_H);
			lc640_write_int(EE_KUBAT1,Kubat[0]);
			}
		else if(but==butL)
			{
			Kubat[0]-=2;
			gran(&Kubat[0],UAKB_L,UAKB_H);
			lc640_write_int(EE_KUBAT1,Kubat[0]);
			}
		else if(but==butL_)
			{
			Kubat[0]-=5;
			gran(&Kubat[0],UAKB_L,UAKB_H);
			lc640_write_int(EE_KUBAT1,Kubat[0]);
			}

		}

#define IAKB_L 500
#define IAKB_H 1500
	else if(sub_ind==4)
		{
		if(but==butR)
			{
			Kibat1[0]+=5;
			gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
			}
		else if(but==butR_)
			{
			Kibat1[0]+=20;
			gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
			}
		else if(but==butL)
			{
			Kibat1[0]-=5;
			gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
			}
		else if(but==butL_)
			{
			Kibat1[0]-=20;
			gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
			}
		else if(but==butLR)
			{
			Kibat0[0]=adc_buff_[1];
			//gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI0BAT1,Kibat0[0]);			}


		}

	else if(sub_ind==5)
		{
		if(but==butR)
			{
			Kunet++;
			gran(&Kunet,900,1300);
			lc640_write_int(EE_KUNET,Kunet);
			}
		else if(but==butR_)
			{
			Kunet+=5;
			gran(&Kunet,900,1300);
			lc640_write_int(EE_KUNET,Kunet);
			}
		else if(but==butL)
			{
			Kunet--;
			gran(&Kunet,900,1300);
			lc640_write_int(EE_KUNET,Kunet);
			}
		else if(but==butL_)
			{
			Kunet-=5;
			gran(&Kunet,900,1300);
			lc640_write_int(EE_KUNET,Kunet);
			}
		}

	}

	   
but_an_end:
n_but=0;

}	



//-----------------------------------------------
void but_drv(void)
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

LPC_GPIO1->FIODIR&=~(1<<30);
LPC_PINCON->PINMODE3&=~(1<<((30-16)*2))&~(1<<(((30-16)*2)+1));


//but=LPC_GPIO1->FIOPIN&(7<<BUT0);	  // читаем 3 бита с порта
//but=LPC_GPIO1->FIOPIN|(~(1UL<<BUT0))&(~(1UL<<BUT1))&(~(1UL<<BUT2))&(~(1UL<<BUT3))&(~(1UL<<BUT4));

//but>>=BUT0;		// преобразуем в удобный вид






but_n=LPC_GPIO1->FIOPIN|(0xFFFFFFFFUL&(~(1UL<<BUT0))&(~(1UL<<BUT1))&(~(1UL<<BUT2)));
but_n>>=BUT0;
if(LPC_GPIO1->FIOPIN&(1<<30))but_n|=(1<<3);
else but_n&=~(1<<3);
if((but_n==0xffUL)||(but_n!=but_s))
 	{
 	speed=0;
 
   	if (((but0_cnt>=BUT_ON)||(but1_cnt!=0))&&(!l_but))
  		{
   	     n_but=1;
          but=but_s;

          }
   	if (but1_cnt>=but_onL_temp)
  		{
   	     n_but=1;
 
          but=but_s&0x7f;
          }
    	l_but=0;
   	but_onL_temp=BUT_ONL;
    	but0_cnt=0;
  	but1_cnt=0;          
     goto but_drv_out;
  	}
else if(but_n==but_s)
 	{
  	but0_cnt++;
  	if(but0_cnt>=BUT_ON)
  		{

   		but0_cnt=0;
   		but1_cnt++;
   		if(but1_cnt>=but_onL_temp)
   			{              
    			but=but_s&0x7f;
    			but1_cnt=0;
    			n_but=1;
    			     
    			l_but=1;
			if(speed)
				{
    				but_onL_temp=but_onL_temp>>1;
        			if(but_onL_temp<=2) but_onL_temp=2;
				}    
   			}
  		}
 	}
but_drv_out: 
but_s=but_n;
LPC_GPIO1->FIODIR&=~(1UL<<BUT0)&~(1UL<<BUT1)&~(1UL<<BUT2);
	   
}




