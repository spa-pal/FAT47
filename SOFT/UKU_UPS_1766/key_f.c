void kurs_up(){
	if(poz_kursor) poz_kursor--;
	else poz_display--;
}
//*********************************
void kurs_down(){
	if(poz_kursor==3) poz_display++;
	else poz_kursor++;
}
//*********************************
void kurs_up1(){
	if(poz_kursor>1) poz_kursor--;
	else poz_display--;
}
//********************************
//****  интернет по умолчанию
void ethernet_default (void){
unsigned char i;	  
		lc640_write_int(EE_ETH_IS_ON,0);
		lc640_write_int(EE_ETH_DHCP_ON,0);
		lc640_write_int(EE_ETH_IP_1,192);
		lc640_write_int(EE_ETH_IP_2,168);
		lc640_write_int(EE_ETH_IP_3,1);
		lc640_write_int(EE_ETH_IP_4,249);
		lc640_write_int(EE_ETH_NET_MASK_1,255);
		lc640_write_int(EE_ETH_NET_MASK_2,255);
		lc640_write_int(EE_ETH_NET_MASK_3,255);
		lc640_write_int(EE_ETH_NET_MASK_4,0);
		lc640_write_int(EE_ETH_DEF_GATW_1,192);
		lc640_write_int(EE_ETH_DEF_GATW_2,168);
		lc640_write_int(EE_ETH_DEF_GATW_3,1);
		lc640_write_int(EE_ETH_DEF_GATW_4,254);
		//lc640_write_int(EE_ETH_SNMP_PORT_READ,161);
		//lc640_write_int(EE_ETH_SNMP_PORT_WRITE,162);
		lc640_write_int(EE_SNMP_READ_PORT,161);
		lc640_write_int(EE_SNMP_WRITE_PORT,162);
		lc640_write(EE_SNMP_READ_COMMUNITY,'p');
		lc640_write(EE_SNMP_READ_COMMUNITY+1,'u');
		lc640_write(EE_SNMP_READ_COMMUNITY+2,'b');
		lc640_write(EE_SNMP_READ_COMMUNITY+3,'l');
		lc640_write(EE_SNMP_READ_COMMUNITY+4,'i');
		lc640_write(EE_SNMP_READ_COMMUNITY+5,'c');
		lc640_write(EE_SNMP_READ_COMMUNITY+6,0);
		lc640_write_int(EE_SNMP_TRAP1_IP_1,192);
		lc640_write_int(EE_SNMP_TRAP1_IP_2,168);
		lc640_write_int(EE_SNMP_TRAP1_IP_3,1);
		lc640_write_int(EE_SNMP_TRAP1_IP_4,2);
		lc640_write_int(EE_SNMP_TRAP2_IP_1,192);
		lc640_write_int(EE_SNMP_TRAP2_IP_2,168);
		lc640_write_int(EE_SNMP_TRAP2_IP_3,1);
		lc640_write_int(EE_SNMP_TRAP2_IP_4,4);
		lc640_write_int(EE_SNMP_TRAP3_IP_1,192);
		lc640_write_int(EE_SNMP_TRAP3_IP_2,168);
		lc640_write_int(EE_SNMP_TRAP3_IP_3,1);
		lc640_write_int(EE_SNMP_TRAP3_IP_4,6);
		lc640_write_int(EE_SNMP_TRAP4_IP_1,192);
		lc640_write_int(EE_SNMP_TRAP4_IP_2,168);
		lc640_write_int(EE_SNMP_TRAP4_IP_3,1);
		lc640_write_int(EE_SNMP_TRAP4_IP_4,8);
		lc640_write_int(EE_SNMP_TRAP5_IP_1,192);
		lc640_write_int(EE_SNMP_TRAP5_IP_2,168);
		lc640_write_int(EE_SNMP_TRAP5_IP_3,1);
		lc640_write_int(EE_SNMP_TRAP5_IP_4,9);
		lc640_write_int(EE_PAR_GLAV_MENU,0);// меню отключено
		lc640_write_int(EE_PAR_GLAV_MENU+2,30);//запуск через 30 секунд
		lc640_write_int(EE_PAR_GLAV_MENU+4,3);//время индикации 3 секунды

		for(i=3;i<11;i++) lc640_write_int(EE_PAR_GLAV_MENU+i*2,'-');

}
//*********************************
void analiz_keypad(void){

	switch(poz_display+poz_kursor){
	case 0:{
		if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 1:{
		if(flag_up==2) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 2:{
		if(flag_up==2) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 3:{
		if(flag_up==2) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 4:{
		if(flag_up==2) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 5:{
		if(flag_up==2) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 6:{
		if(flag_up==2) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 7:{ // УСТАНОВКИ
		if(flag_up==2) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_f==2) {flag_f++; poz_display_bf=poz_display; poz_kursor_bf=poz_kursor; 
			poz_display=252; poz_kursor=0; password_obr=184;}
	break;}
	case 8:{ // ВЫХОД
		if(flag_up==2) {flag_up++; kurs_up();}
		if(flag_f==2) {flag_f++; poz_display=0; poz_kursor=0;}
	break;}
		//*********  меню установки *********************
	case 21:{  // выбор главного меню 
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_f==2) { flag_f++; poz_display_bf2=poz_display; poz_kursor_bf2=poz_kursor;
						poz_kursor=0;
						poz_display=70; 
		}
	break;}
	case 22:{ 	//меню интернет
		if(flag_up==2 ) {flag_up++; 
			if(poz_display==21) poz_display=20; 
			else kurs_up1();
		}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_f==2) {flag_f++; poz_display_bf2=poz_display; poz_kursor_bf2=poz_kursor;
						poz_kursor=1;
						if(ETH_IS_ON) poz_display=40; 
						else poz_display=66; 
						}
	break;}
	case 23:{ // Uбат мах
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==30) {
			flag_left=3;
			can1_out(27,27,0xEE,0x94,0x94,0,0,0);
		}
		if(flag_right==2 || flag_right==30) {
			flag_right=3;
			can1_out(27,27,0xEE,0x92,0x92,0,0,0);
		}		
	break;}
	case 24:{ // Uбат мин
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==30) {
			flag_left=3;
			can1_out(27,27,0xEE,0x84,0x84,0,0,0);
		}
		if(flag_right==2 || flag_right==30) {
			flag_right=3;
			can1_out(27,27,0xEE,0x82,0x82,0,0,0);
		}
	break;}
	case 25:{ // вход в меню калибровка через пароль
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_f==2) {flag_f++; poz_display_bf2=poz_display; poz_kursor_bf2=poz_kursor;
			poz_display=252; poz_kursor=0; password_obr=873;}
	break;}
	case 26:{  // выход из меню установки
		if(flag_up==2 ) {flag_up++; kurs_up1(); }
		if(flag_f==2) {flag_f++; poz_display=poz_display_bf; poz_kursor=poz_kursor_bf;}
	break;}
	//*********  меню калибровка *********************
	case 31:{ // напряжение на нагрузке 
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==5) {
			flag_left=3;
			if(count_left==0xFF) can1_out(27,27,0xEE,0x05,0x05,0,0,0);
			else can1_out(27,27,0xEE,0x04,0x04,0,0,0);
		}
		if(flag_right==2 || flag_right==5) {
			flag_right=3;
			if(count_right==0xFF) can1_out(27,27,0xEE,0x03,0x03,0,0,0);
			else can1_out(27,27,0xEE,0x02,0x02,0,0,0);
		}
	break;}
	case 32:{ 	// ток инвертора
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==5) {
			flag_left=3;
			if(count_left==0xFF) can1_out(27,27,0xEE,0x25,0x25,0,0,0);
			else can1_out(27,27,0xEE,0x24,0x24,0,0,0);
		}
		if(flag_right==2 || flag_right==5) {
			flag_right=3;
			if(count_right==0xFF) can1_out(27,27,0xEE,0x23,0x23,0,0,0);
			else can1_out(27,27,0xEE,0x22,0x22,0,0,0);
		}
		if(flag_f==2) {flag_f++; can1_out(27,27,0xEE,0x21,0x21,0,0,0);}
	break;}
	case 33:{   // мощность инвертора 
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==5) {
			flag_left=3;
			if(count_left==0xFF) can1_out(27,27,0xEE,0x65,0x65,0,0,0);
			else can1_out(27,27,0xEE,0x64,0x64,0,0,0);
		}
		if(flag_right==2 || flag_right==5) {
			flag_right=3;
			if(count_right==0xFF) can1_out(27,27,0xEE,0x63,0x63,0,0,0);
			else can1_out(27,27,0xEE,0x62,0x62,0,0,0);
		}
	break;}
	case 34:{  //  сеть
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==5) {
			flag_left=3;
			if(count_left==0xFF) can1_out(27,27,0xEE,0x55,0x55,0,0,0);
			else can1_out(27,27,0xEE,0x54,0x54,0,0,0);
		}
		if(flag_right==2 || flag_right==5) {
			flag_right=3;
			if(count_right==0xFF) can1_out(27,27,0xEE,0x53,0x53,0,0,0);
			else can1_out(27,27,0xEE,0x52,0x52,0,0,0);
		}
	break;}
	case 35:{ // температура
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==5) {
			flag_left=3;
			if(count_left==0xFF) can1_out(27,27,0xEE,0x35,0x35,0,0,0);
			else can1_out(27,27,0xEE,0x34,0x34,0,0,0);
		}
		if(flag_right==2 || flag_right==5) {
			flag_right=3;
			if(count_right==0xFF) can1_out(27,27,0xEE,0x33,0x33,0,0,0);
			else can1_out(27,27,0xEE,0x32,0x32,0,0,0);
		}
	break;}
	case 36:{ // Uбат
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==5) {
			flag_left=3;
			//if(Kubat[0]>1 && count_left<50) Kubat[0]-=1;
			//else if(Kubat[0]>1+count_left/10) Kubat[0]-=1+count_left/10;
			//lc640_write_int(EE_KUBAT1,Kubat[0]);
			if(count_left==0xFF) can1_out(27,27,0xEE,0x75,0x75,0,0,0);
			else can1_out(27,27,0xEE,0x74,0x74,0,0,0);
		}
		if(flag_right==2 || flag_right==5) {flag_right=3;
			//if( count_right<50 && Kubat[0]<10000L) Kubat[0]+=1; 
			//else if(Kubat[0]<10000L) Kubat[0]+=1+count_right/10;
			//lc640_write_int(EE_KUBAT1,Kubat[0]);
			if(count_right==0xFF) can1_out(27,27,0xEE,0x73,0x73,0,0,0);
			else can1_out(27,27,0xEE,0x72,0x72,0,0,0);
		}
		
	break;}
	case 37:{ // Iбат
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==15) {flag_left=5; 
			if(Kibat1[0]>1+count_left/10) Kibat1[0]-=1+count_left/10;
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
		}
		if(flag_right==2 || flag_right==15) {flag_right=5; 
			if(Kibat1[0]<20000) Kibat1[0]+=1+count_right/10;
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
		}
		if(flag_f==2) {flag_f++; 
			Kibat0[0]=adc_buff_[1];
			lc640_write_int(EE_KI0BAT1,Kibat0[0]);
		}
	break;}
	case 38:{  // контроль сети	 kontrol_seti  0,1,3
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left=5;
			if(kontrol_seti>0) can1_out(27,27,0xEE,0xD4,0xD4,0,0,0);
		}
		if(flag_right==2 ) {flag_right=5;
			if(kontrol_seti<3) can1_out(27,27,0xEE,0xD2,0xD2,0,0,0);
		}		
	break;}
	case 39:{  // управление ШИМ upravl_shim   0,1
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left=5;
			 if(upravl_shim==0) can1_out(27,27,0xEE,0xE2,0xE2,0,0,0);
			 else can1_out(27,27,0xEE,0xE4,0xE4,0,0,0);
		}
		if(flag_right==2 ) {flag_right=5;
			 if(upravl_shim==0) can1_out(27,27,0xEE,0xE2,0xE2,0,0,0);
			 else can1_out(27,27,0xEE,0xE4,0xE4,0,0,0);
		}
	break;}
	case 40:{  // выход из меню калибровка
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		if(flag_f==2) {flag_f++; poz_display=poz_display_bf2; poz_kursor=poz_kursor_bf2;}
	break;}


	//********** меню интернет **********************
	case 41:{
		if(flag_left>30 && flag_right>30 && !flag_l_r) {ethernet_default(); flag_l_r=1;}  
		else if(flag_f==2) { flag_f++;
			if(ETH_IS_ON) {ETH_IS_ON=0; lc640_write_int(EE_ETH_IS_ON,0);  poz_display=66;}
			}
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 42:{
		if(flag_left>30 && flag_right>30 && !flag_l_r) {ethernet_default(); flag_l_r=1;}  
		else if(flag_f==2) {
			if(ETH_DHCP_ON) ETH_DHCP_ON=0;
			else ETH_DHCP_ON=1;
			lc640_write_int(EE_ETH_DHCP_ON,ETH_DHCP_ON);
			}
		else if(flag_up==2 ) {flag_up++; kurs_up1();}
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 43:{
		if(flag_left>30 && flag_right>30 && !flag_l_r) {ethernet_default(); flag_l_r=1;}  
		else if(flag_up==2 ) {flag_up++; kurs_up1();}
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 44:{ // установка ip адреса
		if(flag_up==2 ) {flag_up++; kurs_up1();poz_flash=0;}
		else if(flag_down==2) {flag_down++; kurs_down();poz_flash=0;}
		else if (flag_f==10) {
			poz_flash=poz_flash+1;
			if(poz_flash>3) poz_flash=0;
		}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (poz_flash==0){
				if (ETH_IP_1==0) ETH_IP_1=255;
				else ETH_IP_1-=1;
				lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
			}
			else if (poz_flash==1){
				if (ETH_IP_2==0) ETH_IP_2=255;
				else ETH_IP_2-=1;
				lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
			}
			else if (poz_flash==2){
				if (ETH_IP_3==0) ETH_IP_3=255;
				else ETH_IP_3-=1;
				lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
			}
			else if (poz_flash==3){
				if (ETH_IP_4==0) ETH_IP_4=255;
				else ETH_IP_4-=1;
				lc640_write_int(EE_ETH_IP_4,ETH_IP_4);
			}
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (poz_flash==0){
				if (ETH_IP_1==255) ETH_IP_1=0;
				else ETH_IP_1+=1;
				lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
			}
			else if (poz_flash==1){
				if (ETH_IP_2==255) ETH_IP_2=0;
				else ETH_IP_2+=1;
				lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
			}
			else if (poz_flash==2){
				if (ETH_IP_3==255) ETH_IP_3=0;
				else ETH_IP_3+=1;
				lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
			}
			else if (poz_flash==3){
				if (ETH_IP_4==255) ETH_IP_4=0;
				else ETH_IP_4+=1;
				lc640_write_int(EE_ETH_IP_4,ETH_IP_4);
			}
		}
	break;}
	case 45:{
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 46:{
		if(flag_up==2 ) {flag_up++; kurs_up1();poz_flash=0;}
		else if(flag_down==2) {flag_down++; kurs_down();poz_flash=0;}
		else if (flag_f==10) {
			poz_flash=poz_flash+1;
			if(poz_flash>3) poz_flash=0;
		}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (poz_flash==0){
				if (ETH_NET_MASK_1==0) ETH_NET_MASK_1=255;
				else ETH_NET_MASK_1-=1;
				lc640_write_int(EE_ETH_NET_MASK_1,ETH_NET_MASK_1);
			}
			else if (poz_flash==1){
				if (ETH_NET_MASK_2==0) ETH_NET_MASK_2=255;
				else ETH_NET_MASK_2-=1;
				lc640_write_int(EE_ETH_NET_MASK_2,ETH_NET_MASK_2);
			}
			else if (poz_flash==2){
				if (ETH_NET_MASK_3==0) ETH_NET_MASK_3=255;
				else ETH_NET_MASK_3-=1;
				lc640_write_int(EE_ETH_NET_MASK_3,ETH_NET_MASK_3);
			}
			else if (poz_flash==3){
				if (ETH_NET_MASK_4==0) ETH_NET_MASK_4=255;
				else ETH_NET_MASK_4-=1;
				lc640_write_int(EE_ETH_NET_MASK_4,ETH_NET_MASK_4);
			}
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (poz_flash==0){
				if (ETH_NET_MASK_1==255) ETH_NET_MASK_1=0;
				else ETH_NET_MASK_1+=1;
				lc640_write_int(EE_ETH_NET_MASK_1,ETH_NET_MASK_1);
			}
			else if (poz_flash==1){
				if (ETH_NET_MASK_2==255) ETH_NET_MASK_2=0;
				else ETH_NET_MASK_2+=1;
				lc640_write_int(EE_ETH_NET_MASK_2,ETH_NET_MASK_2);
			}
			else if (poz_flash==2){
				if (ETH_NET_MASK_3==255) ETH_NET_MASK_3=0;
				else ETH_NET_MASK_3+=1;
				lc640_write_int(EE_ETH_NET_MASK_3,ETH_NET_MASK_3);
			}
			else if (poz_flash==3){
				if (ETH_NET_MASK_4==255) ETH_NET_MASK_4=0;
				else ETH_NET_MASK_4+=1;
				lc640_write_int(EE_ETH_NET_MASK_4,ETH_NET_MASK_4);
			}
		}
	break;}
	case 47:{
		if(flag_up==2 ) {flag_up++; kurs_up1();}
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 48:{
		if(flag_up==2 ) {flag_up++; kurs_up1();poz_flash=0;} 
		else if(flag_down==2) {flag_down++; kurs_down();poz_flash=0;}
		else if (flag_f==10) {
			poz_flash=poz_flash+1;
			if(poz_flash>3) poz_flash=0;
		}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (poz_flash==0){
				if (ETH_DEF_GATW_1==0) ETH_DEF_GATW_1=255;
				else ETH_DEF_GATW_1-=1;
				lc640_write_int(EE_ETH_DEF_GATW_1,ETH_DEF_GATW_1);
			}
			else if (poz_flash==1){
				if (ETH_DEF_GATW_2==0) ETH_DEF_GATW_2=255;
				else ETH_DEF_GATW_2-=1;
				lc640_write_int(EE_ETH_DEF_GATW_2,ETH_DEF_GATW_2);
			}
			else if (poz_flash==2){
				if (ETH_DEF_GATW_3==0) ETH_DEF_GATW_3=255;
				else ETH_DEF_GATW_3-=1;
				lc640_write_int(EE_ETH_DEF_GATW_3,ETH_DEF_GATW_3);
			}
			else if (poz_flash==3){
				if (ETH_DEF_GATW_4==0) ETH_DEF_GATW_4=255;
				else ETH_DEF_GATW_4-=1;
				lc640_write_int(EE_ETH_DEF_GATW_4,ETH_DEF_GATW_4);
			}
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (poz_flash==0){
				if (ETH_DEF_GATW_1==255) ETH_DEF_GATW_1=0;
				else ETH_DEF_GATW_1+=1;
				lc640_write_int(EE_ETH_DEF_GATW_1,ETH_DEF_GATW_1);
			}
			else if (poz_flash==1){
				if (ETH_DEF_GATW_2==255) ETH_DEF_GATW_2=0;
				else ETH_DEF_GATW_2+=1;
				lc640_write_int(EE_ETH_DEF_GATW_2,ETH_DEF_GATW_2);
			}
			else if (poz_flash==2){
				if (ETH_DEF_GATW_3==255) ETH_DEF_GATW_3=0;
				else ETH_DEF_GATW_3+=1;
				lc640_write_int(EE_ETH_DEF_GATW_3,ETH_DEF_GATW_3);
			}
			else if (poz_flash==3){
				if (ETH_DEF_GATW_4==255) ETH_DEF_GATW_4=0;
				else ETH_DEF_GATW_4+=1;
				lc640_write_int(EE_ETH_DEF_GATW_4,ETH_DEF_GATW_4);
			}
		}
	break;}
	case 49:{
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_down==2) {flag_down++; kurs_down();}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (SNMP_READ_PORT==0) SNMP_READ_PORT=255;
			else SNMP_READ_PORT-=1;
			lc640_write_int(EE_SNMP_READ_PORT,SNMP_READ_PORT);
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (SNMP_READ_PORT==255) SNMP_READ_PORT=0;
			else SNMP_READ_PORT+=1;
			lc640_write_int(EE_SNMP_READ_PORT,SNMP_READ_PORT);
		}		
	break;}
	case 50:{
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_down==2) {flag_down++; kurs_down();}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (SNMP_WRITE_PORT==0) SNMP_WRITE_PORT=255;
			else SNMP_WRITE_PORT-=1;
			lc640_write_int(EE_SNMP_WRITE_PORT,SNMP_WRITE_PORT);
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (SNMP_WRITE_PORT==255) SNMP_WRITE_PORT=0;
			else SNMP_WRITE_PORT+=1;
			lc640_write_int(EE_SNMP_WRITE_PORT,SNMP_WRITE_PORT);
		}
	break;}
	case 51:{
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 52:{ // community
		if(flag_up==2 ) {flag_up++; kurs_up1();poz_flash=0;} 
		else if(flag_down==2) {flag_down++; kurs_down();poz_flash=0;}
		else if (flag_f==10) {
			poz_flash=poz_flash+1;
			if(snmp_Community[poz_flash] ==0) {
				snmp_Community[poz_flash+1] =0;
				lc640_write(EE_SNMP_READ_COMMUNITY+(poz_flash+1),0);
			}
			if(snmp_Community[poz_flash-1]==0 || poz_flash>7) poz_flash=0;

		}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if(snmp_Community[poz_flash] == 0)	snmp_Community[poz_flash]=122;
			else if(snmp_Community[poz_flash] == 48){
				if(poz_flash){
					snmp_Community[poz_flash]=0;
					snmp_Community[poz_flash+1]=0;
					lc640_write(EE_SNMP_READ_COMMUNITY+(poz_flash+1),0);
				}
				else snmp_Community[poz_flash]=122;
			}
			else if(snmp_Community[poz_flash] == 65)	snmp_Community[poz_flash]=57;
			else if(snmp_Community[poz_flash] == 97)	snmp_Community[poz_flash]=90;
			else snmp_Community[poz_flash]-=1;
			lc640_write(EE_SNMP_READ_COMMUNITY+poz_flash,snmp_Community[poz_flash]);
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if(snmp_Community[poz_flash] == 0)	snmp_Community[poz_flash]=48;			
			else if(snmp_Community[poz_flash] == 57)	snmp_Community[poz_flash]=65;
			else if(snmp_Community[poz_flash] == 90)	snmp_Community[poz_flash]=97;
			else if(snmp_Community[poz_flash] == 122){
				if(poz_flash){
					snmp_Community[poz_flash]=0;
					snmp_Community[poz_flash+1]=0;
					lc640_write(EE_SNMP_READ_COMMUNITY+(poz_flash+1),0);
				}
				else snmp_Community[poz_flash]=48;
			}
			else snmp_Community[poz_flash]+=1;
			lc640_write(EE_SNMP_READ_COMMUNITY+poz_flash,snmp_Community[poz_flash]);
		}
	break;}
	case 53:{
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 54:{
		if(flag_up==2 ) {flag_up++; kurs_up1();poz_flash=0;} 
		else if(flag_down==2) {flag_down++; kurs_down();poz_flash=0;}
		else if (flag_f==10) {
			poz_flash=poz_flash+1;
			if(poz_flash>3) poz_flash=0;
		}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (poz_flash==0){
				if (SNMP_TRAP1_IP_1==0) SNMP_TRAP1_IP_1=255;
				else SNMP_TRAP1_IP_1-=1;
				lc640_write_int(EE_SNMP_TRAP1_IP_1,SNMP_TRAP1_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP1_IP_2==0) SNMP_TRAP1_IP_2=255;
				else SNMP_TRAP1_IP_2-=1;
				lc640_write_int(EE_SNMP_TRAP1_IP_2,SNMP_TRAP1_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP1_IP_3==0) SNMP_TRAP1_IP_3=255;
				else SNMP_TRAP1_IP_3-=1;
				lc640_write_int(EE_SNMP_TRAP1_IP_3,SNMP_TRAP1_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP1_IP_4==0) SNMP_TRAP1_IP_4=255;
				else SNMP_TRAP1_IP_4-=1;
				lc640_write_int(EE_SNMP_TRAP1_IP_4,SNMP_TRAP1_IP_4);
			}
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (poz_flash==0){
				if (SNMP_TRAP1_IP_1==255) SNMP_TRAP1_IP_1=0;
				else SNMP_TRAP1_IP_1+=1;
				lc640_write_int(EE_SNMP_TRAP1_IP_1,SNMP_TRAP1_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP1_IP_2==255) SNMP_TRAP1_IP_2=0;
				else SNMP_TRAP1_IP_2+=1;
				lc640_write_int(EE_SNMP_TRAP1_IP_2,SNMP_TRAP1_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP1_IP_3==255) SNMP_TRAP1_IP_3=0;
				else SNMP_TRAP1_IP_3+=1;
				lc640_write_int(EE_SNMP_TRAP1_IP_3,SNMP_TRAP1_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP1_IP_4==255) SNMP_TRAP1_IP_4=0;
				else SNMP_TRAP1_IP_4+=1;
				lc640_write_int(EE_SNMP_TRAP1_IP_4,SNMP_TRAP1_IP_4);
			}
		}
	break;}
	case 55:{
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 56:{
		if(flag_up==2 ) {flag_up++; kurs_up1();poz_flash=0;} 
		else if(flag_down==2) {flag_down++; kurs_down();poz_flash=0;}
		else if (flag_f==10) {
			poz_flash=poz_flash+1;
			if(poz_flash>3) poz_flash=0;
		}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (poz_flash==0){
				if (SNMP_TRAP2_IP_1==0) SNMP_TRAP2_IP_1=255;
				else SNMP_TRAP2_IP_1-=1;
				lc640_write_int(EE_SNMP_TRAP2_IP_1,SNMP_TRAP2_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP2_IP_2==0) SNMP_TRAP2_IP_2=255;
				else SNMP_TRAP2_IP_2-=1;
				lc640_write_int(EE_SNMP_TRAP2_IP_2,SNMP_TRAP2_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP2_IP_3==0) SNMP_TRAP2_IP_3=255;
				else SNMP_TRAP2_IP_3-=1;
				lc640_write_int(EE_SNMP_TRAP2_IP_3,SNMP_TRAP2_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP2_IP_4==0) SNMP_TRAP2_IP_4=255;
				else SNMP_TRAP2_IP_4-=1;
				lc640_write_int(EE_SNMP_TRAP2_IP_4,SNMP_TRAP2_IP_4);
			}
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (poz_flash==0){
				if (SNMP_TRAP2_IP_1==255) SNMP_TRAP2_IP_1=0;
				else SNMP_TRAP2_IP_1+=1;
				lc640_write_int(EE_SNMP_TRAP2_IP_1,SNMP_TRAP2_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP2_IP_2==255) SNMP_TRAP2_IP_2=0;
				else SNMP_TRAP2_IP_2+=1;
				lc640_write_int(EE_SNMP_TRAP2_IP_2,SNMP_TRAP2_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP2_IP_3==255) SNMP_TRAP2_IP_3=0;
				else SNMP_TRAP2_IP_3+=1;
				lc640_write_int(EE_SNMP_TRAP2_IP_3,SNMP_TRAP2_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP2_IP_4==255) SNMP_TRAP2_IP_4=0;
				else SNMP_TRAP2_IP_4+=1;
				lc640_write_int(EE_SNMP_TRAP2_IP_4,SNMP_TRAP2_IP_4);
			}
		}
	break;}
	case 57:{
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 58:{
		if(flag_up==2 ) {flag_up++; kurs_up1();poz_flash=0;} 
		else if(flag_down==2) {flag_down++; kurs_down();poz_flash=0;}
		else if (flag_f==10) {
			poz_flash=poz_flash+1;
			if(poz_flash>3) poz_flash=0;
		}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (poz_flash==0){
				if (SNMP_TRAP3_IP_1==0) SNMP_TRAP3_IP_1=255;
				else SNMP_TRAP3_IP_1-=1;
				lc640_write_int(EE_SNMP_TRAP3_IP_1,SNMP_TRAP3_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP3_IP_2==0) SNMP_TRAP3_IP_2=255;
				else SNMP_TRAP3_IP_2-=1;
				lc640_write_int(EE_SNMP_TRAP3_IP_2,SNMP_TRAP3_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP3_IP_3==0) SNMP_TRAP3_IP_3=255;
				else SNMP_TRAP3_IP_3-=1;
				lc640_write_int(EE_SNMP_TRAP3_IP_3,SNMP_TRAP3_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP3_IP_4==0) SNMP_TRAP3_IP_4=255;
				else SNMP_TRAP3_IP_4-=1;
				lc640_write_int(EE_SNMP_TRAP3_IP_4,SNMP_TRAP3_IP_4);
			}
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (poz_flash==0){
				if (SNMP_TRAP3_IP_1==255) SNMP_TRAP3_IP_1=0;
				else SNMP_TRAP3_IP_1+=1;
				lc640_write_int(EE_SNMP_TRAP3_IP_1,SNMP_TRAP3_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP3_IP_2==255) SNMP_TRAP3_IP_2=0;
				else SNMP_TRAP3_IP_2+=1;
				lc640_write_int(EE_SNMP_TRAP3_IP_2,SNMP_TRAP3_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP3_IP_3==255) SNMP_TRAP3_IP_3=0;
				else SNMP_TRAP3_IP_3+=1;
				lc640_write_int(EE_SNMP_TRAP3_IP_3,SNMP_TRAP3_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP3_IP_4==255) SNMP_TRAP3_IP_4=0;
				else SNMP_TRAP3_IP_4+=1;
				lc640_write_int(EE_SNMP_TRAP3_IP_4,SNMP_TRAP3_IP_4);
			}
		}
	break;}
	case 59:{
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 60:{
		if(flag_up==2 ) {flag_up++; kurs_up1();poz_flash=0;} 
		else if(flag_down==2) {flag_down++; kurs_down();poz_flash=0;}
		else if (flag_f==10) {
			poz_flash=poz_flash+1;
			if(poz_flash>3) poz_flash=0;
		}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (poz_flash==0){
				if (SNMP_TRAP4_IP_1==0) SNMP_TRAP4_IP_1=255;
				else SNMP_TRAP4_IP_1-=1;
				lc640_write_int(EE_SNMP_TRAP4_IP_1,SNMP_TRAP4_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP4_IP_2==0) SNMP_TRAP4_IP_2=255;
				else SNMP_TRAP4_IP_2-=1;
				lc640_write_int(EE_SNMP_TRAP4_IP_2,SNMP_TRAP4_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP4_IP_3==0) SNMP_TRAP4_IP_3=255;
				else SNMP_TRAP4_IP_3-=1;
				lc640_write_int(EE_SNMP_TRAP4_IP_3,SNMP_TRAP4_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP4_IP_4==0) SNMP_TRAP4_IP_4=255;
				else SNMP_TRAP4_IP_4-=1;
				lc640_write_int(EE_SNMP_TRAP4_IP_4,SNMP_TRAP4_IP_4);
			}
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (poz_flash==0){
				if (SNMP_TRAP4_IP_1==255) SNMP_TRAP4_IP_1=0;
				else SNMP_TRAP4_IP_1+=1;
				lc640_write_int(EE_SNMP_TRAP4_IP_1,SNMP_TRAP4_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP4_IP_2==255) SNMP_TRAP4_IP_2=0;
				else SNMP_TRAP4_IP_2+=1;
				lc640_write_int(EE_SNMP_TRAP4_IP_2,SNMP_TRAP4_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP4_IP_3==255) SNMP_TRAP4_IP_3=0;
				else SNMP_TRAP4_IP_3+=1;
				lc640_write_int(EE_SNMP_TRAP4_IP_3,SNMP_TRAP4_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP4_IP_4==255) SNMP_TRAP4_IP_4=0;
				else SNMP_TRAP4_IP_4+=1;
				lc640_write_int(EE_SNMP_TRAP4_IP_4,SNMP_TRAP4_IP_4);
			}
		}
	break;}
	case 61:{
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_down==2) {flag_down++; kurs_down();}
	break;}
	case 62:{
		if(flag_up==2 ) {flag_up++; kurs_up1();poz_flash=0;} 
		else if(flag_down==2) {flag_down++; kurs_down();poz_flash=0;}
		else if (flag_f==10) {
			poz_flash=poz_flash+1;
			if(poz_flash>3) poz_flash=0;
		}
		else if(flag_left==2 || flag_left==50) {flag_left=30;
			if (poz_flash==0){
				if (SNMP_TRAP5_IP_1==0) SNMP_TRAP5_IP_1=255;
				else SNMP_TRAP5_IP_1-=1;
				lc640_write_int(EE_SNMP_TRAP5_IP_1,SNMP_TRAP5_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP5_IP_2==0) SNMP_TRAP5_IP_2=255;
				else SNMP_TRAP5_IP_2-=1;
				lc640_write_int(EE_SNMP_TRAP5_IP_2,SNMP_TRAP5_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP5_IP_3==0) SNMP_TRAP5_IP_3=255;
				else SNMP_TRAP5_IP_3-=1;
				lc640_write_int(EE_SNMP_TRAP5_IP_3,SNMP_TRAP5_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP5_IP_4==0) SNMP_TRAP5_IP_4=255;
				else SNMP_TRAP5_IP_4-=1;
				lc640_write_int(EE_SNMP_TRAP5_IP_4,SNMP_TRAP5_IP_4);
			}
		}
		else if(flag_right==2 || flag_right==50) {flag_right=30;
			if (poz_flash==0){
				if (SNMP_TRAP5_IP_1==255) SNMP_TRAP5_IP_1=0;
				else SNMP_TRAP5_IP_1+=1;
				lc640_write_int(EE_SNMP_TRAP5_IP_1,SNMP_TRAP5_IP_1);
			}
			else if (poz_flash==1){
				if (SNMP_TRAP5_IP_2==255) SNMP_TRAP5_IP_2=0;
				else SNMP_TRAP5_IP_2+=1;
				lc640_write_int(EE_SNMP_TRAP5_IP_2,SNMP_TRAP5_IP_2);
			}
			else if (poz_flash==2){
				if (SNMP_TRAP5_IP_3==255) SNMP_TRAP5_IP_3=0;
				else SNMP_TRAP5_IP_3+=1;
				lc640_write_int(EE_SNMP_TRAP5_IP_3,SNMP_TRAP5_IP_3);
			}
			else if (poz_flash==3){
				if (SNMP_TRAP5_IP_4==255) SNMP_TRAP5_IP_4=0;
				else SNMP_TRAP5_IP_4+=1;
				lc640_write_int(EE_SNMP_TRAP5_IP_4,SNMP_TRAP5_IP_4);
			}
		}
	break;}
	case 63:{ // выход 
		if(flag_up==2 ) {flag_up++; kurs_up1();} 
		else if(flag_f==2) {flag_f++; poz_display=poz_display_bf2; poz_kursor=poz_kursor_bf2; tcp_init_cnt=2;}
	break;}
	case 67:{
		if(flag_down==2) {flag_down++; poz_kursor=2;}
		else if(flag_f==2) {	flag_f++;
			if(!ETH_IS_ON) {ETH_IS_ON=1; lc640_write_int(EE_ETH_IS_ON,1); poz_display=40; }
		}
	break;}
	case 68:{
		if(flag_up==2 ) {flag_up++; poz_kursor=1;}
		else if(flag_f==2) {	
			flag_f++;
			poz_display=poz_display_bf2; 
			poz_kursor=poz_kursor_bf2;
			tcp_init_cnt=2;
		}
	break;}
	// ********* меню выбор глав меню ***************
	case 70:{
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left++; par_glav_menu[0]=0; lc640_write_int(EE_PAR_GLAV_MENU,par_glav_menu[0]);}
		if(flag_right==2) {flag_right++; par_glav_menu[0]=1;lc640_write_int(EE_PAR_GLAV_MENU,par_glav_menu[0]);}
	break;}
	case 71:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==50) {flag_left=30; 
			if(par_glav_menu[1]>=40) {
				par_glav_menu[1]-=10;
				lc640_write_int(EE_PAR_GLAV_MENU+2,par_glav_menu[1]);
			}
		}
		if(flag_right==2 || flag_right==50) {flag_right=30; 
			if(par_glav_menu[1]<250) {
				par_glav_menu[1]+=10;
				lc640_write_int(EE_PAR_GLAV_MENU+2,par_glav_menu[1]);
			}
		}
	break;}
	case 72:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2 || flag_left==50) {flag_left=30; 
			if(par_glav_menu[2]>3) {
				par_glav_menu[2]-=1;
				lc640_write_int(EE_PAR_GLAV_MENU+4,par_glav_menu[2]);
			}
		}
		if(flag_right==2 || flag_right==50) {flag_right=30; 
			if(par_glav_menu[2]<60) {
				par_glav_menu[2]+=1;
				lc640_write_int(EE_PAR_GLAV_MENU+4,par_glav_menu[2]);
			}
		}
	break;}
	case 73:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left++; par_glav_menu[3]='-'; lc640_write_int(EE_PAR_GLAV_MENU+6,par_glav_menu[3]);}
		if(flag_right==2) {flag_right++; par_glav_menu[3]='+'; lc640_write_int(EE_PAR_GLAV_MENU+6,par_glav_menu[3]);}
	break;}
	case 74:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left++; par_glav_menu[4]='-'; lc640_write_int(EE_PAR_GLAV_MENU+8,par_glav_menu[4]);}
		if(flag_right==2) {flag_right++; par_glav_menu[4]='+'; lc640_write_int(EE_PAR_GLAV_MENU+8,par_glav_menu[4]);}
	break;}
	case 75:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left++; par_glav_menu[5]='-'; lc640_write_int(EE_PAR_GLAV_MENU+10,par_glav_menu[5]);}
		if(flag_right==2) {flag_right++; par_glav_menu[5]='+'; lc640_write_int(EE_PAR_GLAV_MENU+10,par_glav_menu[5]);}
	break;}
	case 76:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left++; par_glav_menu[6]='-'; lc640_write_int(EE_PAR_GLAV_MENU+12,par_glav_menu[6]);}
		if(flag_right==2) {flag_right++; par_glav_menu[6]='+'; lc640_write_int(EE_PAR_GLAV_MENU+12,par_glav_menu[6]);}
	break;}
	case 77:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left++; par_glav_menu[7]='-'; lc640_write_int(EE_PAR_GLAV_MENU+14,par_glav_menu[7]);}
		if(flag_right==2) {flag_right++; par_glav_menu[7]='+'; lc640_write_int(EE_PAR_GLAV_MENU+14,par_glav_menu[7]);}
	break;}
	case 78:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left++; par_glav_menu[8]='-'; lc640_write_int(EE_PAR_GLAV_MENU+16,par_glav_menu[8]);}
		if(flag_right==2) {flag_right++; par_glav_menu[8]='+'; lc640_write_int(EE_PAR_GLAV_MENU+16,par_glav_menu[8]);}
	break;}
	case 79:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		if(flag_down==2) {flag_down++; kurs_down();}
		if(flag_left==2) {flag_left++; par_glav_menu[9]='-'; lc640_write_int(EE_PAR_GLAV_MENU+18,par_glav_menu[9]);}
		if(flag_right==2) {flag_right++; par_glav_menu[9]='+'; lc640_write_int(EE_PAR_GLAV_MENU+18,par_glav_menu[9]);}
	break;}
	case 80:{
		if(flag_up==2 ) {flag_up++; kurs_up();}
		else if(flag_f==2) {	flag_f++;
			poz_display=poz_display_bf2; poz_kursor=poz_kursor_bf2;
		}
	break;}



	// ********* меню пароль  ***********************
	case 250:{ 
		if(flag_left==2) {flag_left++; poz_display++;}
		if(flag_up==2) {flag_up++;
			if(password%10==9) password-=9;      
			else password++;
		}
		if(flag_down==2) {flag_down++;
			if(password%10==0) password+=9;      
			else password--;		
		}
		if(flag_f==2) {flag_f++;
			if(password_obr==password && password==184) {poz_display=20;poz_kursor=1;}			
			else if(password_obr==password && password==873) {poz_display=30;poz_kursor=1;}			
			else {poz_display=255; pass_error=4;}
			password=0;
		}
	break;}
	case 251:{ 
		if(flag_left==2) {flag_left++; poz_display++;}
		if(flag_right==2) {flag_right++; poz_display--;}
		if(flag_up==2) {flag_up++;
		  	if(password%100>=90) password=password-90;      
			else password+=10;		
		}
		if(flag_down==2) {flag_down++;
			if(password%100<10) password=password+90;      
			else password-=10;
		}
		if(flag_f==2) {flag_f++;
			if(password_obr==password && password==184) {poz_display=20;poz_kursor=1;}			
			else if(password_obr==password && password==873) {poz_display=30;poz_kursor=1;}			
			else {poz_display=255; pass_error=4;}
			password=0;
		}
	break;}
	case 252:{ 
		if(flag_right==2) {flag_right++; poz_display--;}
		if(flag_up==2) { flag_up++;
			if(password%1000>=900) password=password-900;      
			else password+=100;
		}
		if(flag_down==2) { flag_down++;
		  	if(password%1000<100) password=password+900;      
			else password-=100;
		}
		if(flag_f==2) {	 flag_f++;
			if(password_obr==password && password==184) {poz_display=20;poz_kursor=1;}
			else if(password_obr==password && password==873) {poz_display=30;poz_kursor=1;}			
			else {poz_display=255; pass_error=4;}
			password=0;
		}
	break;}
	
	
	}// end switch(poz_display+poz_kursor){	

	if( flag_l_r && !flag_left && !flag_right ) flag_l_r=0;



}























