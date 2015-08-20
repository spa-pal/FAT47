extern char snmp_community[10];

//���������� �� ����������
extern signed short snmp_device_code;
extern signed 	   snmp_sernum;
extern signed short snmp_sernum_lsb;
extern signed short snmp_sernum_msb;
extern char 	   snmp_location[100];
extern signed short snmp_numofbat;
extern signed short snmp_numofbps;
extern signed short snmp_numofevents;

//��������� ��������� ����
extern signed short snmp_main_voltage;
extern signed short snmp_main_power_on_off;

//��������� ��������
extern signed short snmp_load_voltage;
extern signed short snmp_load_current;

//��������� �����
extern signed short snmp_bps_number[2];
extern signed short snmp_bps_voltage[2];
extern signed short snmp_bps_current[2];
extern signed short snmp_bps_temperature[2];
extern signed short snmp_bps_stat[2];

//��������� �������
extern signed short snmp_battery_voltage;
extern signed short snmp_battery_current;

//��������� ���������
extern signed short snmp_inverter_voltage;
extern signed short snmp_inverter_current;
extern signed short snmp_inverter_temperature;

//�����������
extern signed short snmp_spc_stat;
extern char snmp_spc_trap_message[100];
extern signed short snmp_spc_trap_value;

//�������
extern signed short snmp_command;
extern signed short snmp_command_parametr;

//������ ������
extern char snmp_log[64][128];

//������������ ���������
//SNMP-���������
extern signed short snmp_snmp_settings_read_port;
extern signed short snmp_snmp_settings_write_port;
extern char 		snmp_snmp_settings_read_community[16];
extern char 		snmp_snmp_settings_write_community[16];
extern long 		snmp_snmp_settings_trap_server_1;
extern long 		snmp_snmp_settings_trap_server_2;
extern long 		snmp_snmp_settings_trap_server_3;
extern long 		snmp_snmp_settings_trap_server_4;
extern long 		snmp_snmp_settings_trap_server_5;
//ETH-���������
extern long 		snmp_eth_settings_ip;
extern long 		snmp_eth_settings_net_mask;
extern long 		snmp_eth_settings_def_gatw;
//����-���������
extern signed short snmp_trap_settings_main_power_trap_send_of_av;
extern signed short snmp_trap_settings_main_power_trap_send_of_no_av;
extern signed short snmp_trap_settings_inverter_temperature_trap_send_of_av;
extern signed short snmp_trap_settings_inverter_temperature_trap_send_of_no_av;
extern signed short snmp_trap_settings_inverter_voltage_trap_send_of_av;
extern signed short snmp_trap_settings_inverter_voltage_trap_send_of_no_av;
extern signed short snmp_trap_settings_inverter_current_trap_send_of_av;
extern signed short snmp_trap_settings_inverter_current_trap_send_of_no_av;
extern signed short snmp_trap_settings_battery_voltage_trap_send_of_av;
extern signed short snmp_trap_settings_battery_voltage_trap_send_of_no_av;

extern char snmp_spc_trap_message[100];
extern signed short snmp_spc_trap_value_0,snmp_spc_trap_value_1,snmp_spc_trap_value_2;


extern signed short snmp_main_bps;
extern signed short snmp_zv_en;
extern signed short snmp_alarm_auto_disable;
extern signed short snmp_bat_test_time;
extern signed short snmp_u_max;
extern signed short snmp_u_0_grad;
extern signed short snmp_u_20_grad;
extern signed short snmp_u_sign;
extern signed short snmp_u_min_power;
extern signed short snmp_u_withouth_bat;
extern signed short snmp_control_current;
extern signed short snmp_max_charge_current;
extern signed short snmp_max_current;
extern signed short snmp_max_current_koef;
extern signed short snmp_max_current_koef;
extern signed short snmp_up_charge_koef;
extern signed short snmp_powerup_psu_timeout;
extern signed short snmp_max_temperature;

extern signed short snmp_alarm_status;
  
//-----------------------------------------------
void snmp_snmp_settings_read_port_write (int mode);
void snmp_snmp_settings_write_port_write (int mode);
void snmp_snmp_settings_read_community_write (int mode);
void snmp_snmp_settings_write_community_write (int mode);
void snmp_snmp_settings_trap_server_1_write (int mode);
void snmp_snmp_settings_trap_server_2_write (int mode);
void snmp_snmp_settings_trap_server_3_write (int mode);
void snmp_snmp_settings_trap_server_4_write (int mode);
void snmp_snmp_settings_trap_server_5_write (int mode);
void snmp_eth_settings_ip_write (int mode);
void snmp_eth_settings_net_mask_write (int mode);
void snmp_eth_settings_def_gatw_write (int mode);
void snmp_trap_settings_main_power_trap_send_of_av_write (int mode);
void snmp_trap_settings_main_power_trap_send_of_no_av_write (int mode);
void snmp_trap_settings_inverter_temperature_trap_send_of_av_write (int mode);
void snmp_trap_settings_inverter_temperature_trap_send_of_no_av_write (int mode);
void snmp_trap_settings_inverter_voltage_trap_send_of_av_write (int mode) ;
void snmp_trap_settings_inverter_voltage_trap_send_of_no_av_write (int mode);
void snmp_trap_settings_inverter_current_trap_send_of_av_write (int mode) ;
void snmp_trap_settings_inverter_current_trap_send_of_no_av_write (int mode);
void snmp_trap_settings_battery_voltage_trap_send_of_av_write (int mode);
void snmp_trap_settings_battery_voltage_trap_send_of_no_av_write (int mode);


void snmp_data (void);
void snmp_sernum_write (int mode); 
void snmp_location_write (int mode);
void snmp_command_execute (int mode);
void event2snmp(char num);
void snmp_main_bps_write (int mode);
void snmp_zv_on_write (int mode);
void snmp_alarm_auto_disable_write (int mode);
void snmp_bat_test_time_write (int mode);
void snmp_u_max_write (int mode);
void snmp_u_0_grad_write (int mode);
void snmp_u_20_grad_write (int mode);
void snmp_u_sign_write (int mode);
void snmp_u_min_power_write (int mode);
void snmp_u_withouth_bat_write (int mode);
void snmp_control_current_write (int mode);
void snmp_max_charge_current_write (int mode);
void snmp_max_current_write (int mode);
void snmp_max_current_koef_write (int mode);
void snmp_up_charge_koef_write (int mode);
void snmp_powerup_psu_timeout_write (int mode);
void snmp_max_temperature_write (int mode);
void event2snmp(char num);
void snmp_trap_send(char* str, unsigned short in, unsigned short in1);

 
