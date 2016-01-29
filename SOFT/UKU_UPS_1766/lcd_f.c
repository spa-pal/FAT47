
void ssd1306_data(char data);
unsigned char  N_sim;// 16 // ����� �������� � ������ ���	//10
unsigned char  N_toh;// 8 // ������ ������� � ������	//12
unsigned char N_ss; //  ������ ������� � �����
//���������� ����� ������ �� 
//���������������� �������
void filling_lcd_buffer (char *str, unsigned char N_sim, unsigned char n_strok)
{
unsigned char i,j,k,_lcd_buffer[(16+1)*4];	// 16- ��� N_sim
i=0;
j=0;

for (k=1;k<=n_strok;k++)
{
for (i=(N_sim)*k-N_sim;i<((N_sim)*k);i++)
{
	if (*(str+j)!=0x0a && *(str+j)!=0)
	{
		_lcd_buffer[i]=*(str+j);
		j=j+1;
	}
    else 
    {
        for (i=i;i<( (N_sim)*k);i++) _lcd_buffer[i]=0x20;
		j=j+1;

    }
}
if(*(str+j)==0x0a) j=j+1;
}
for (i=0;i<N_sim*4;i++)  *(str+i)=_lcd_buffer[i];

}


//*****************************************************************************************
void bitmap_hndl21x16(void)// ���������� ������� ����� lcd_bitmap ��������� �� lcd_buffer 
{

char s;
short x,i;
unsigned int ptr_bitmap, z;
N_ss=21;  //  ������ ������� � �����
N_sim=6;  // ����� �������� � ������ ���
N_toh=21; // ������ ������� � ������
for(i=0;i<1023;i++)
	{
	lcd_bitmap[i]=0;
	}
for(i=0;i<2;i++) {
	for(x=0;x<N_sim;x++)
	 	{
		s=lcd_buffer[x+N_sim*i];
			if(s>191) z=((s-97)*N_ss*4);//���� 192 �� ���� 95
			else if(s>31) z=(s-32)*N_ss*4;
			else z=0;

			ptr_bitmap=(512*(unsigned)i)+(N_toh*x);
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+4];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+8];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+12];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+16];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+20];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+24];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+28];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+32];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+36];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+40];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+44];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+48];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+52];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+56];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+60];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+64];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+68];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+72];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+76];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+80];

			ptr_bitmap=(512*(unsigned)i)+(N_toh*x)+128;
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+1];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+5];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+9];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+13];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+17];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+21];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+25];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+29];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+33];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+37];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+41];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+45];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+49];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+53];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+57];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+61];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+65];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+69];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+73];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+77];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+81];

			ptr_bitmap=(512*(unsigned)i)+(N_toh*x)+256;
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+2];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+6];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+10];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+14];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+18];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+22];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+26];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+30];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+34];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+38];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+42];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+46];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+50];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+54];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+58];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+62];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+66];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+70];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+74];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+78];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+82];

			ptr_bitmap=(512*(unsigned)i)+(N_toh*x)+384;
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+3];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+7];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+11];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+15];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+19];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+23];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+27];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+31];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+35];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+39];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+43];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+47];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+51];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+55];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+59];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+63];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+67];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+71];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+75];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+79];
			lcd_bitmap[ptr_bitmap++]=caracter21x16[z+83];


			}

	

	 
	}

}    
//***************************************

//***************************************

void bitmap_hndl16x8(void)// ���������� ������� ����� lcd_bitmap ��������� �� lcd_buffer 
{
char s;
short x,i;
unsigned int ptr_bitmap, z;
N_ss=9;
N_sim=16;
N_toh=8;
for(i=0;i<1023;i++)
	{
	lcd_bitmap[i]=0;
	}
for(i=0;i<4;i++) {
	for(x=0;x<N_sim;x++)
	 	{
		s=lcd_buffer[x+N_sim*i];
			if(s>191) z=((s-97)*N_ss*2);//���� 192 �� ���� 95
			else if(s>31) z=(s-32)*N_ss*2;
			else z=0;

			ptr_bitmap=(256*(unsigned)i)+(N_toh*x);
			//lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+2];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+4];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+6];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+8];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+10];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+12];
			//lcd_bitmap[ptr_bitmap++]=0x00;
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+14];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+16];
			//lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+18];
			//lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+20];
			//lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+22];
			ptr_bitmap=(256*(unsigned)i)+(N_toh*x)+128;
			//lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+1];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+3];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+5];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+7];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+9];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+11];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+13];
			//lcd_bitmap[ptr_bitmap++]=0x00;
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+15];
			lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+17];
			//lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+19];
			//lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+21];
			//lcd_bitmap[ptr_bitmap++]=p27CircleCyr_10ptBitmaps[z+23];
			}

	

	 
	}

}    
//***************************************

void bitmap_hndl16x9(void)// ���������� ������� ����� lcd_bitmap ��������� �� lcd_buffer 
{
char s;
short x,i;
unsigned int ptr_bitmap, z;
N_ss=12;
N_sim=16;
N_toh=8;
for(i=0;i<1023;i++)
	{
	lcd_bitmap[i]=0;
	}


for(i=0;i<4;i++) {
	for(x=0;x<N_sim;x++)
	 	{
		s=lcd_buffer[x+N_sim*i];
			if(s>191) z=((s-97)*N_ss*2);//���� 192 �� ���� 95
			else if(s>31) z=(s-32)*N_ss*2;
			else z=0;

			ptr_bitmap=(256*(unsigned)i)+(N_toh*x);
			//lcd_bitmap[ptr_bitmap++]=caracter16x9[z];
			//lcd_bitmap[ptr_bitmap++]=caracter16x9[z+2];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+4];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+6];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+8];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+10];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+12];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+14];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+16];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+18];
			//lcd_bitmap[ptr_bitmap++]=caracter16x9[z+20];
			//lcd_bitmap[ptr_bitmap++]=caracter16x9[z+22];
			ptr_bitmap=(256*(unsigned)i)+(N_toh*x)+128;
			//lcd_bitmap[ptr_bitmap++]=caracter16x9[z+1];
			//lcd_bitmap[ptr_bitmap++]=caracter16x9[z+3];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+5];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+7];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+9];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+11];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+13];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+15];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+17];
			lcd_bitmap[ptr_bitmap++]=caracter16x9[z+19];
			//lcd_bitmap[ptr_bitmap++]=caracter16x9[z+21];
			//lcd_bitmap[ptr_bitmap++]=caracter16x9[z+23];
			}

	

	 
	}

}
//*****************************************************************************
void ind_hndl(void)
{
//char* ptrs[40];
const char* sub_ptrs[30];
char snmp_Community_temp[10], i;
//static char sub_cnt,sub_cnt1;
//char i,sub_cnt_max;
//char r1[12], r2[12], r3[12], r4[12];


switch (poz_display) {
	case 0:{
		sprintf(lcd_buffer," U���=%-u�\n I���=%.1f�\n P���=%-d��\n U����=%-u�",
							snmp_inverter_voltage/10,
							(float)snmp_inverter_current/10,
							snmp_inverter_power,
							snmp_main_voltage/10
							);
	break;}
	case 1:{
		sprintf(lcd_buffer," I���=%.1f�\n P���=%-d��\n U����=%-u�\n t=%d'C",
							(float)snmp_inverter_current/10,
							snmp_inverter_power,
							snmp_main_voltage/10,
							snmp_inverter_temperature
							);
	break;}
	case 2:{
		sprintf(lcd_buffer," P���=%-d��\n U����=%-u�\n t=%-d'C\n U���=%-u.%-uB",
							snmp_inverter_power,
							snmp_main_voltage/10,
							snmp_inverter_temperature,
							snmp_battery_voltage/10,snmp_battery_voltage%10
							);
	break;}
	case 3:{
		if(count_kalibr_i_bat>599){
			sprintf(lcd_buffer," U����=%-u�\n t=%-d'C\n U���=%-u.%-uB\n I���=������.",
							snmp_main_voltage/10,
							snmp_inverter_temperature,
							snmp_battery_voltage/10,snmp_battery_voltage%10
							);
		}
		else{
			sprintf(lcd_buffer," U����=%-u�\n t=%-d'C\n U���=%-u.%-uB\n I���=%.2fA",
							snmp_main_voltage/10,
							snmp_inverter_temperature,
							snmp_battery_voltage/10,snmp_battery_voltage%10,
							(float)snmp_battery_current/100
							);
		}
	break;}
	case 4:{
		if(count_kalibr_i_bat>599){
			sprintf(lcd_buffer," t=%-d'C\n U���=%-u.%-uB\n I���=������.\n ���������",
							snmp_inverter_temperature,
							snmp_battery_voltage/10,snmp_battery_voltage%10
							);
		}
		else{
			sprintf(lcd_buffer," t=%-d'C\n U���=%-u.%-uB\n I���=%.2fA\n ���������",
							snmp_inverter_temperature,
							snmp_battery_voltage/10,snmp_battery_voltage%10,
							(float)snmp_battery_current/100
							);
		}
	break;}
	case 5:{
		if(count_kalibr_i_bat>599){
			sprintf(lcd_buffer," U���=%-u.%-uB\n I���=������.\n ���������\n ������",
							snmp_battery_voltage/10,snmp_battery_voltage%10
							); 	
		}
		else{
			sprintf(lcd_buffer," U���=%-u.%-uB\n I���=%.2fA\n ���������\n ������",
							snmp_battery_voltage/10,snmp_battery_voltage%10,
							(float)snmp_battery_current/100
							);
		}
	break;}

	//  *********** ���� ��������� **************
	case 20:{
		sprintf(lcd_buffer,"    ���������\n ����� ��.����\n ��������\n U���.���=%-uB", u_bat_on);
	break;}
	case 21:{
		sprintf(lcd_buffer,"    ���������\n ��������\n U���.���=%-uB\n U���.����=%-uB", u_bat_on, u_bat_off );
	break;}
	case 22:{
		sprintf(lcd_buffer,"    ���������\n U���.���=%-uB\n U���.����=%-uB\n ���� 1", u_bat_on, u_bat_off);
	break;}
	case 23:{
		sprintf(lcd_buffer,"    ���������\n U���.����=%-uB\n ���� 1\n ���� 2", u_bat_off);
	break;}
	case 24:{
		sprintf(lcd_buffer,"    ���������\n ���� 1\n ���� 2\n ����������");
	break;}
	case 25:{
		sprintf(lcd_buffer,"    ���������\n ���� 2\n ����������\n �����");
	break;}

	//  *********** ���� ���������� **************
	case 30:{
		sprintf(lcd_buffer,"   ����������\n U���=%-u.%01u�\n I���=%.1f�\n P���=%-d��",
							snmp_inverter_voltage/10, snmp_inverter_voltage%10,
							(float)snmp_inverter_current/10,
							snmp_inverter_power
							);
	break;}
	case 31:{
		sprintf(lcd_buffer,"   ����������\n I���=%.1f�\n P���=%-d��\n U����=%-u.%01u�",
							(float)snmp_inverter_current/10,
							snmp_inverter_power,
							snmp_main_voltage/10, snmp_main_voltage%10);
	break;}
	case 32:{
		sprintf(lcd_buffer,"   ����������\n P���=%-d��\n U����=%-u.%01u�\n t=%d'C",
							snmp_inverter_power,
							snmp_main_voltage/10, snmp_main_voltage%10,
							snmp_inverter_temperature);
	break;}
	case 33:{
		sprintf(lcd_buffer,"   ����������\n U����=%-u.%01u�\n t=%d'C\n U���=%-u.%-uB",
							snmp_main_voltage/10, snmp_main_voltage%10,
							snmp_inverter_temperature,
							snmp_battery_voltage/10,snmp_battery_voltage%10);
	break;}
	case 34:{
		sprintf(lcd_buffer,"   ����������\n t=%d'C\n U���=%-u.%-uB\n I���=%.2fA",
							snmp_inverter_temperature,
							snmp_battery_voltage/10,snmp_battery_voltage%10,
							(float)snmp_battery_current/100);
	break;}
	case 35:{
		if(kontrol_seti==0) sub_ptrs[0]="����";
		else if(kontrol_seti==1) sub_ptrs[0]="����";
		else sub_ptrs[0]="���";
		sprintf(lcd_buffer,"   ����������\n U���=%-u.%-uB\n I���=%.2fA\n �����.���� %s",
							snmp_battery_voltage/10,snmp_battery_voltage%10,
							(float)snmp_battery_current/100,
							sub_ptrs[0]
							);
	break;}
	case 36:{
		if(kontrol_seti==0) sub_ptrs[0]="����";
		else if(kontrol_seti==1) sub_ptrs[0]="����";
		else sub_ptrs[0]="���";
		if(upravl_shim==0) sub_ptrs[1]="����";
		else sub_ptrs[1]="���";
		sprintf(lcd_buffer,"   ����������\n I���=%.2fA\n �����.���� %s\n ���.��� %s",
							(float)snmp_battery_current/100,
							sub_ptrs[0],
							sub_ptrs[1]
							);
	break;}
	case 37:{
		if(kontrol_seti==0) sub_ptrs[0]="����";
		else if(kontrol_seti==1) sub_ptrs[0]="����";
		else sub_ptrs[0]="���";
		if(upravl_shim==0) sub_ptrs[1]="����";
		else sub_ptrs[1]="���";
		sprintf(lcd_buffer,"   ����������\n �����.���� %s\n ���.��� %s\n �����",
							sub_ptrs[0],
							sub_ptrs[1]
							);
	break;}


   	//********** ���� �������� **********************
	/*
	ptrs[0]=	" Ethernet         ! ";
	ptrs[1]=	" DHCP������       @ ";
	ptrs[2]=	" IP�����            ";
	ptrs[3]=	"  000.000.000.00#   ";	// ETH_IP_1   ETH_IP_4
	ptrs[4]=	" ����� �������      ";
	ptrs[5]=	"  000.000.000.00$   ";	// ETH_MASK_1  ETH_MASK_4
	ptrs[6]=	" ����               ";
	ptrs[7]=	"  000.000.000.00)   ";	// ETH_GW_1  ETH_GW_4
	ptrs[8]=	" ����.������       [";	// SNMP_READ_PORT
	ptrs[9]=	" ����.������       ]"; // SNMP_WRITE_PORT
	ptrs[10]=	" Community <        ";	// snmp_Community[10]
	ptrs[11]=	" ������� ��� TRAP N1";
	ptrs[12]=	"  000.000.000.00%   ";	// SNMP_TRAP1_IP_1   SNMP_TRAP1_IP_4
	ptrs[13]=	" ������� ��� TRAP N2";
	ptrs[14]=	"  000.000.000.00^   ";
	ptrs[15]=	" ������� ��� TRAP N3";
	ptrs[16]=	"  000.000.000.00&   ";
	ptrs[17]=	" ������� ��� TRAP N4";
	ptrs[18]=	"  000.000.000.00*   ";
	ptrs[19]=	" ������� ��� TRAP N5";
	ptrs[20]=	"  000.000.000.00(   ";	// SNMP_TRAP5_IP_1   SNMP_TRAP5_IP_4
	ptrs[21]=	" �����              ";
	*/
	
	case 40:{
		if(ETH_IS_ON) sub_ptrs[0]="���";
		else sub_ptrs[0]="����";
		if(ETH_DHCP_ON) sub_ptrs[1]="���";
		else sub_ptrs[1]="����"; 
		sprintf(lcd_buffer,"   ETHERNET:\n Ethernet %s\n DHCP������ %s\n IP�����:",
					sub_ptrs[0],sub_ptrs[1]);
	break;}
	case 41:{
		if(ETH_IS_ON) sub_ptrs[0]="��� ";
		else sub_ptrs[0]="����";
		if(ETH_DHCP_ON) sub_ptrs[1]="��� ";
		else sub_ptrs[1]="����"; 
		sprintf(lcd_buffer,"   ETHERNET:\n DHCP������ %s\n IP�����:\n %03u.%03u.%03u.%03u",
					sub_ptrs[1], 
					ETH_IP_1, ETH_IP_2, ETH_IP_3, ETH_IP_4
					);
		if(flash_1S && poz_kursor==3){
			lcd_buffer[41+poz_flash*4]=0x20; lcd_buffer[42+poz_flash*4]=0x20; lcd_buffer[43+poz_flash*4]=0x20;
		}
	break;}
	case 42:{
		sprintf(lcd_buffer,"   ETHERNET:\n IP�����:\n %03u.%03u.%03u.%03u\n ����� �������:",
					 ETH_IP_1, ETH_IP_2, ETH_IP_3, ETH_IP_4 );
		if(flash_1S && poz_kursor==2){
			lcd_buffer[24+poz_flash*4]=0x20; lcd_buffer[25+poz_flash*4]=0x20; lcd_buffer[26+poz_flash*4]=0x20;
		}
	break;}
	case 43:{
		sprintf(lcd_buffer,"   ETHERNET:\n %03u.%03u.%03u.%03u\n ����� �������:\n %03u.%03u.%03u.%03u",
					ETH_IP_1, ETH_IP_2, ETH_IP_3, ETH_IP_4,
					 ETH_NET_MASK_1, ETH_NET_MASK_2, ETH_NET_MASK_3, ETH_NET_MASK_4 );
		if(flash_1S && poz_kursor==3 ){
			lcd_buffer[47+poz_flash*4]=0x20; lcd_buffer[48+poz_flash*4]=0x20; lcd_buffer[49+poz_flash*4]=0x20;
		}
		if(flash_1S && poz_kursor==1){
			lcd_buffer[14+poz_flash*4]=0x20; lcd_buffer[15+poz_flash*4]=0x20; lcd_buffer[16+poz_flash*4]=0x20;
		}
	break;}
	case 44:{
		sprintf(lcd_buffer,"   ETHERNET:\n ����� �������:\n %03u.%03u.%03u.%03u\n ����:",
					 ETH_NET_MASK_1, ETH_NET_MASK_2, ETH_NET_MASK_3, ETH_NET_MASK_4 );
		if(flash_1S && poz_kursor==2){
			lcd_buffer[30+poz_flash*4]=0x20; lcd_buffer[31+poz_flash*4]=0x20; lcd_buffer[32+poz_flash*4]=0x20;
		}
	break;}
	case 45:{
		sprintf(lcd_buffer,"   ETHERNET:\n %03u.%03u.%03u.%03u\n ����:\n %03u.%03u.%03u.%03u",
					 ETH_NET_MASK_1, ETH_NET_MASK_2, ETH_NET_MASK_3, ETH_NET_MASK_4, 
					 ETH_DEF_GATW_1, ETH_DEF_GATW_2, ETH_DEF_GATW_3, ETH_DEF_GATW_4 );
		if(flash_1S && poz_kursor==1){
			lcd_buffer[14+poz_flash*4]=0x20; lcd_buffer[15+poz_flash*4]=0x20; lcd_buffer[16+poz_flash*4]=0x20;
		}
		if(flash_1S && poz_kursor==3 ){
			lcd_buffer[38+poz_flash*4]=0x20; lcd_buffer[39+poz_flash*4]=0x20; lcd_buffer[40+poz_flash*4]=0x20;
		}
	break;}
	case 46:{
		sprintf(lcd_buffer,"   ETHERNET:\n ����:\n %03u.%03u.%03u.%03u\n ����.������ %-u",
					 ETH_DEF_GATW_1, ETH_DEF_GATW_2, ETH_DEF_GATW_3, ETH_DEF_GATW_4, SNMP_READ_PORT );
		if(flash_1S && poz_kursor==2){
			lcd_buffer[21+poz_flash*4]=0x20; lcd_buffer[22+poz_flash*4]=0x20; lcd_buffer[23+poz_flash*4]=0x20;
		}
	break;}
	case 47:{
		sprintf(lcd_buffer,"   ETHERNET:\n %03u.%03u.%03u.%03u\n ���� ������ %-u\n ���� ������ %-u",
					 ETH_DEF_GATW_1, ETH_DEF_GATW_2, ETH_DEF_GATW_3, ETH_DEF_GATW_4, SNMP_READ_PORT, SNMP_WRITE_PORT );
		if(flash_1S && poz_kursor==1){
			lcd_buffer[14+poz_flash*4]=0x20; lcd_buffer[15+poz_flash*4]=0x20; lcd_buffer[16+poz_flash*4]=0x20;
		}
	break;}
	case 48:{
		sprintf(lcd_buffer,"   ETHERNET:\n ���� ������ %-u\n ���� ������ %-u\n Community:",
					 SNMP_READ_PORT, SNMP_WRITE_PORT );
	break;}
	case 49:{
		for(i=0;i<10;i++) {snmp_Community_temp[i]=snmp_Community[i];}
		if(flash_1S && poz_kursor==3 )	{
			snmp_Community_temp[poz_flash]='_'; 
			if(poz_flash==strlen(snmp_Community))snmp_Community_temp[(strlen(snmp_Community_temp))+1]='\n';
			}
		sprintf(lcd_buffer,"   ETHERNET:\n ���� ������ %-u\n Community:\n %s",
					 SNMP_WRITE_PORT, snmp_Community_temp );
		
	break;}
	case 50:{
		for(i=0;i<10;i++) {snmp_Community_temp[i]=snmp_Community[i];}
		if(flash_1S && poz_kursor==2 )	{
			snmp_Community_temp[poz_flash]='_'; 
			if(poz_flash==strlen(snmp_Community))snmp_Community_temp[(strlen(snmp_Community_temp))+1]='\n';
			}
		sprintf(lcd_buffer,"   ETHERNET:\n Community:\n %s\n ������� TRAP N1",
					 snmp_Community_temp );
	break;}	
	case 51:{
		for(i=0;i<10;i++) {snmp_Community_temp[i]=snmp_Community[i];}
		if(flash_1S && poz_kursor==1 )	{
			snmp_Community_temp[poz_flash]='_'; 
			if(poz_flash==strlen(snmp_Community))snmp_Community_temp[(strlen(snmp_Community_temp))+1]='\n';
			}
		sprintf(lcd_buffer,"   ETHERNET:\n %s\n ������� TRAP N1\n %03u.%03u.%03u.%03u",
					 snmp_Community_temp, SNMP_TRAP1_IP_1, SNMP_TRAP1_IP_2, SNMP_TRAP1_IP_3, SNMP_TRAP1_IP_4 );
		if(flash_1S && poz_kursor==3 ){
			lcd_buffer[33+(strlen(snmp_Community_temp))+poz_flash*4]=0x20; 
			lcd_buffer[34+(strlen(snmp_Community_temp))+poz_flash*4]=0x20; 
			lcd_buffer[35+(strlen(snmp_Community_temp))+poz_flash*4]=0x20;
		}
	break;}	
	case 52:{
		sprintf(lcd_buffer,"   ETHERNET:\n ������� TRAP N1\n %03u.%03u.%03u.%03u\n ������� TRAP N2",
					 SNMP_TRAP1_IP_1, SNMP_TRAP1_IP_2, SNMP_TRAP1_IP_3, SNMP_TRAP1_IP_4 );
		if(flash_1S && poz_kursor==2){
			lcd_buffer[31+poz_flash*4]=0x20; lcd_buffer[32+poz_flash*4]=0x20; lcd_buffer[33+poz_flash*4]=0x20;
		}
	break;}
	case 53:{
		sprintf(lcd_buffer,"   ETHERNET:\n %03u.%03u.%03u.%03u\n ������� TRAP N2\n %03u.%03u.%03u.%03u",
					 SNMP_TRAP1_IP_1, SNMP_TRAP1_IP_2, SNMP_TRAP1_IP_3, SNMP_TRAP1_IP_4,
					 SNMP_TRAP2_IP_1, SNMP_TRAP2_IP_2, SNMP_TRAP2_IP_3, SNMP_TRAP2_IP_4  );
	   	if(flash_1S && poz_kursor==1){
			lcd_buffer[14+poz_flash*4]=0x20; lcd_buffer[15+poz_flash*4]=0x20; lcd_buffer[16+poz_flash*4]=0x20;
		}
		if(flash_1S && poz_kursor==3 ){
			lcd_buffer[48+poz_flash*4]=0x20; lcd_buffer[49+poz_flash*4]=0x20; lcd_buffer[50+poz_flash*4]=0x20;
		}
	break;}
	case 54:{
		sprintf(lcd_buffer,"   ETHERNET:\n ������� TRAP N2\n %03u.%03u.%03u.%03u\n ������� TRAP N3",
					 SNMP_TRAP2_IP_1, SNMP_TRAP2_IP_2, SNMP_TRAP2_IP_3, SNMP_TRAP2_IP_4  );
		if(flash_1S && poz_kursor==2){
			lcd_buffer[31+poz_flash*4]=0x20; lcd_buffer[32+poz_flash*4]=0x20; lcd_buffer[33+poz_flash*4]=0x20;
		}
	break;}

	case 55:{
		sprintf(lcd_buffer,"   ETHERNET:\n %03u.%03u.%03u.%03u\n ������� TRAP N3\n %03u.%03u.%03u.%03u",
					 SNMP_TRAP2_IP_1, SNMP_TRAP2_IP_2, SNMP_TRAP2_IP_3, SNMP_TRAP2_IP_4,
					 SNMP_TRAP3_IP_1, SNMP_TRAP3_IP_2, SNMP_TRAP3_IP_3, SNMP_TRAP3_IP_4  );
		if(flash_1S && poz_kursor==1){
			lcd_buffer[14+poz_flash*4]=0x20; lcd_buffer[15+poz_flash*4]=0x20; lcd_buffer[16+poz_flash*4]=0x20;
		}
		if(flash_1S && poz_kursor==3 ){
			lcd_buffer[48+poz_flash*4]=0x20; lcd_buffer[49+poz_flash*4]=0x20; lcd_buffer[50+poz_flash*4]=0x20;
		}
	break;}
	case 56:{
		sprintf(lcd_buffer,"   ETHERNET:\n ������� TRAP N3\n %03u.%03u.%03u.%03u\n ������� TRAP N4",
					 SNMP_TRAP3_IP_1, SNMP_TRAP3_IP_2, SNMP_TRAP3_IP_3, SNMP_TRAP3_IP_4  );
		if(flash_1S && poz_kursor==2){
			lcd_buffer[31+poz_flash*4]=0x20; lcd_buffer[32+poz_flash*4]=0x20; lcd_buffer[33+poz_flash*4]=0x20;
		}
	break;}
	case 57:{
		sprintf(lcd_buffer,"   ETHERNET:\n %03u.%03u.%03u.%03u\n ������� TRAP N4\n %03u.%03u.%03u.%03u",
					 SNMP_TRAP3_IP_1, SNMP_TRAP3_IP_2, SNMP_TRAP3_IP_3, SNMP_TRAP3_IP_4,
					 SNMP_TRAP4_IP_1, SNMP_TRAP4_IP_2, SNMP_TRAP4_IP_3, SNMP_TRAP4_IP_4  );
		if(flash_1S && poz_kursor==1){
			lcd_buffer[14+poz_flash*4]=0x20; lcd_buffer[15+poz_flash*4]=0x20; lcd_buffer[16+poz_flash*4]=0x20;
		}
		if(flash_1S && poz_kursor==3 ){
			lcd_buffer[48+poz_flash*4]=0x20; lcd_buffer[49+poz_flash*4]=0x20; lcd_buffer[50+poz_flash*4]=0x20;
		}
	break;}
	case 58:{
		sprintf(lcd_buffer,"   ETHERNET:\n ������� TRAP N4\n %03u.%03u.%03u.%03u\n ������� TRAP N5",
					 SNMP_TRAP4_IP_1, SNMP_TRAP4_IP_2, SNMP_TRAP4_IP_3, SNMP_TRAP4_IP_4  );
		if(flash_1S && poz_kursor==2){
			lcd_buffer[31+poz_flash*4]=0x20; lcd_buffer[32+poz_flash*4]=0x20; lcd_buffer[33+poz_flash*4]=0x20;
		}
	break;}
	case 59:{
		sprintf(lcd_buffer,"   ETHERNET:\n %03u.%03u.%03u.%03u\n ������� TRAP N5\n %03u.%03u.%03u.%03u",
					 SNMP_TRAP4_IP_1, SNMP_TRAP4_IP_2, SNMP_TRAP4_IP_3, SNMP_TRAP4_IP_4,
					 SNMP_TRAP5_IP_1, SNMP_TRAP5_IP_2, SNMP_TRAP5_IP_3, SNMP_TRAP5_IP_4  );
		if(flash_1S && poz_kursor==1){
			lcd_buffer[14+poz_flash*4]=0x20; lcd_buffer[15+poz_flash*4]=0x20; lcd_buffer[16+poz_flash*4]=0x20;
		}
		if(flash_1S && poz_kursor==3 ){
			lcd_buffer[48+poz_flash*4]=0x20; lcd_buffer[49+poz_flash*4]=0x20; lcd_buffer[50+poz_flash*4]=0x20;
		}
	break;}
	case 60:{
		sprintf(lcd_buffer,"   ETHERNET:\n ������� TRAP N5\n %03u.%03u.%03u.%03u\n �����",
					 SNMP_TRAP5_IP_1, SNMP_TRAP5_IP_2, SNMP_TRAP5_IP_3, SNMP_TRAP5_IP_4  );
		if(flash_1S && poz_kursor==2){
			lcd_buffer[31+poz_flash*4]=0x20; lcd_buffer[32+poz_flash*4]=0x20; lcd_buffer[33+poz_flash*4]=0x20;
		}
	break;}
	case 66:{
		sprintf(lcd_buffer,"   ETHERNET:\n Ethernet ����\n �����\n");
	break;}

	// ********** ��������� �������� ���� *************
	case 70:{
		if(par_glav_menu[0]) sub_ptrs[0]="���";
		else sub_ptrs[0]="����";
		sprintf(lcd_buffer," ��.���� %s\n ����� %-u���\n �������� %-u���\n  %c U���",
			sub_ptrs[0],par_glav_menu[1],par_glav_menu[2],par_glav_menu[3]);
	break;}
	case 71:{
		sprintf(lcd_buffer," ����� %-u���\n �������� %-u���\n  %c U���\n  %c I���",
			par_glav_menu[1],par_glav_menu[2],par_glav_menu[3],par_glav_menu[4]);
	break;}
	case 72:{
		sprintf(lcd_buffer," �������� %-u���\n  %c U���\n  %c I���\n  %c ����",
			par_glav_menu[2],par_glav_menu[3],par_glav_menu[4],par_glav_menu[5]);
	break;}
	case 73:{
		sprintf(lcd_buffer,"  %c U���\n  %c I���\n  %c ����\n  %c U����",
			par_glav_menu[3],par_glav_menu[4],par_glav_menu[5],par_glav_menu[6]
			);
	break;}
	case 74:{
		sprintf(lcd_buffer,"  %c I���\n  %c ����\n  %c U����\n  %c U���",
			par_glav_menu[4],par_glav_menu[5],par_glav_menu[6],par_glav_menu[7]
			);
	break;}
	case 75:{
		sprintf(lcd_buffer,"  %c ����\n  %c U����\n  %c U���\n  %c I���",
			par_glav_menu[5],par_glav_menu[6],par_glav_menu[7],par_glav_menu[8]
			);
	break;}
	case 76:{
		sprintf(lcd_buffer,"  %c U����\n  %c U���\n  %c I���\n  %c t`",
			par_glav_menu[6],par_glav_menu[7],par_glav_menu[8],par_glav_menu[9]
			);
	break;}
	case 77:{
		sprintf(lcd_buffer,"  %c U���\n  %c I���\n  %c t`\n �����",
			par_glav_menu[7],par_glav_menu[8],par_glav_menu[9]
			);
	break;}
	//  *********** ���� ���� 1   **************
	case 80:{		
		if(flash_1S){
			if(id_rele1==0) sprintf(lcd_buffer,"   ���� 1:\n  \n ������ ���� ��\n ������ U��� ��");
			else if(id_rele1==1) sprintf(lcd_buffer,"   ���� 1:\n ������ ���� ��\n \n ������ U��� ��");
			else if(id_rele1==2) sprintf(lcd_buffer,"   ���� 1:\n ������ ���� ��\n ������ ���� ��\n ");
		}
		else sprintf(lcd_buffer,"   ���� 1:\n ������ ���� ��\n ������ ���� ��\n ������ U��� ��"); 
	break;}
	case 81:{
		if(flash_1S){
			if(id_rele1==1) sprintf(lcd_buffer,"   ���� 1:\n \n ������ U��� ��\n ������ U��� HP");
			else if(id_rele1==2) sprintf(lcd_buffer,"   ���� 1:\n ������ ���� ��\n \n ������ U��� HP");
			else if(id_rele1==3) sprintf(lcd_buffer,"   ���� 1:\n ������ ���� ��\n ������ U��� ��\n ");
		}
		else sprintf(lcd_buffer,"   ���� 1:\n ������ ���� ��\n ������ U��� ��\n ������ U��� HP");
	break;}
	case 82:{
		if(flash_1S){
			if(id_rele1==2) sprintf(lcd_buffer,"   ���� 1:\n \n ������ U��� HP\n ��� ������. ��");
			else if(id_rele1==3) sprintf(lcd_buffer,"   ���� 1:\n ������ U��� ��\n \n ��� ������. ��");
			else if(id_rele1==4) sprintf(lcd_buffer,"   ���� 1:\n ������ U��� ��\n ������ U��� HP\n ");
		}
		else sprintf(lcd_buffer,"   ���� 1:\n ������ U��� ��\n ������ U��� HP\n ��� ������. ��");
	break;}
	case 83:{
		if(flash_1S){
			if(id_rele1==3) sprintf(lcd_buffer,"   ���� 1:\n \n ��� ������. ��\n ��� ������. ��");
			else if(id_rele1==4) sprintf(lcd_buffer,"   ���� 1:\n ������ U��� HP\n \n ��� ������. ��");
			else if(id_rele1==5) sprintf(lcd_buffer,"   ���� 1:\n ������ U��� HP\n ��� ������. ��\n ");
		}
		else sprintf(lcd_buffer,"   ���� 1:\n ������ U��� HP\n ��� ������. ��\n ��� ������. ��");
	break;}
	case 84:{
		if(flash_1S){
			if(id_rele1==4) sprintf(lcd_buffer,"   ���� 1:\n \n ��� ������. ��\n �����");
			else if(id_rele1==5) sprintf(lcd_buffer,"   ���� 1:\n ��� ������. ��\n \n �����");
		}
		else sprintf(lcd_buffer,"   ���� 1:\n ��� ������. ��\n ��� ������. ��\n �����");
	break;}
	//  *********** ���� ���� 2   **************
	case 90:{		
		if(flash_1S){
			if(id_rele2==0) sprintf(lcd_buffer,"   ���� 2:\n  \n ������ ���� ��\n ������ U��� ��");
			else if(id_rele2==1) sprintf(lcd_buffer,"   ���� 2:\n ������ ���� ��\n \n ������ U��� ��");
			else if(id_rele2==2) sprintf(lcd_buffer,"   ���� 2:\n ������ ���� ��\n ������ ���� ��\n ");
		}
		else sprintf(lcd_buffer,"   ���� 2:\n ������ ���� ��\n ������ ���� ��\n ������ U��� ��"); 
	break;}
	case 91:{
		if(flash_1S){
			if(id_rele2==1) sprintf(lcd_buffer,"   ���� 2:\n \n ������ U��� ��\n ������ U��� HP");
			else if(id_rele2==2) sprintf(lcd_buffer,"   ���� 2:\n ������ ���� ��\n \n ������ U��� HP");
			else if(id_rele2==3) sprintf(lcd_buffer,"   ���� 2:\n ������ ���� ��\n ������ U��� ��\n ");
		}
		else sprintf(lcd_buffer,"   ���� 2:\n ������ ���� ��\n ������ U��� ��\n ������ U��� HP");
	break;}
	case 92:{
		if(flash_1S){
			if(id_rele2==2) sprintf(lcd_buffer,"   ���� 2:\n \n ������ U��� HP\n ��� ������. ��");
			else if(id_rele2==3) sprintf(lcd_buffer,"   ���� 2:\n ������ U��� ��\n \n ��� ������. ��");
			else if(id_rele2==4) sprintf(lcd_buffer,"   ���� 2:\n ������ U��� ��\n ������ U��� HP\n ");
		}
		else sprintf(lcd_buffer,"   ���� 2:\n ������ U��� ��\n ������ U��� HP\n ��� ������. ��");
	break;}
	case 93:{
		if(flash_1S){
			if(id_rele2==3) sprintf(lcd_buffer,"   ���� 2:\n \n ��� ������. ��\n ��� ������. ��");
			else if(id_rele2==4) sprintf(lcd_buffer,"   ���� 2:\n ������ U��� HP\n \n ��� ������. ��");
			else if(id_rele2==5) sprintf(lcd_buffer,"   ���� 2:\n ������ U��� HP\n ��� ������. ��\n ");
		}
		else sprintf(lcd_buffer,"   ���� 2:\n ������ U��� HP\n ��� ������. ��\n ��� ������. ��");
	break;}
	case 94:{
		if(flash_1S){
			if(id_rele2==4) sprintf(lcd_buffer,"   ���� 2:\n \n ��� ������. ��\n �����");
			else if(id_rele2==5) sprintf(lcd_buffer,"   ���� 2:\n ��� ������. ��\n \n �����");
		}
		else sprintf(lcd_buffer,"   ���� 2:\n ��� ������. ��\n ��� ������. ��\n �����");
	break;}
	//*********** ��������  **********************
	case 240:{
		sprintf(lcd_buffer," U���\n %-uB",
			snmp_inverter_voltage/10
			);
	break;}
	case 241:{
		sprintf(lcd_buffer," I���\n%.1f�",
			(float)snmp_inverter_current/10
			);
	break;}
	case 242:{
		sprintf(lcd_buffer," P���\n%-dB�",
			snmp_inverter_power
			);
	break;}
	case 243:{
		sprintf(lcd_buffer,"U����\n%-uB",
			snmp_main_voltage/10
			);
	break;}
	case 244:{
		sprintf(lcd_buffer," U���\n%-u.%-uB",
			snmp_battery_voltage/10,snmp_battery_voltage%10
			);
	break;}
	case 245:{
		if(snmp_battery_current>500 || snmp_battery_current<-500){
			snmp_battery_current=snmp_battery_current/10;
			sprintf(lcd_buffer," I���\n%.1fA",(float)(snmp_battery_current) /10	);
		}
		else{ 
			sprintf(lcd_buffer," I���\n%.2fA",(float)(snmp_battery_current) /100	);
		}
	break;}
	case 246:{
		sprintf(lcd_buffer,"  t%c\n %-d%cC",
			34,
			snmp_inverter_temperature, 34
			);
	break;}


	// ********** ���� ������  ******************
	case 250:{
		sprintf(lcd_buffer,"������� ������:\n      %03u \n        *\n", password);
	break;}
	case 251:{
		sprintf(lcd_buffer,"������� ������:\n      %03u \n       *\n", password);
	break;}
	case 252:{
		sprintf(lcd_buffer,"������� ������:\n      %03u \n      *\n", password);
	break;}

	case 255:{
		sprintf(lcd_buffer,"\n     ������\n    �� �����!\n");
		if(!pass_error--) {
			if(password_obr==184){poz_display=poz_display_bf; poz_kursor=poz_kursor_bf;}
			if(password_obr==873){poz_display=poz_display_bf2; poz_kursor=poz_kursor_bf2;}
			password_obr=0;
		} 
	break;}

}






}
//********************************************

 void lcd_out (void){
 	short iiii_;

	ind_hndl();

	if(poz_display>239 && poz_display<247){
		N_sim=6;
		filling_lcd_buffer(lcd_buffer, N_sim, 2);
		bitmap_hndl21x16();
	}
	else{	
		N_sim=16;
		filling_lcd_buffer(lcd_buffer, N_sim, 4);
		if(poz_display<250) lcd_buffer[poz_kursor*16]='>'; // ��������� ������
 		bitmap_hndl16x8();
	}	
 	for(iiii_=0;iiii_<1024;iiii_++)	ssd1306_data(lcd_bitmap[iiii_]);



 }






















