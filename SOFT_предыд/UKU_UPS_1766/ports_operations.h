#ifndef _PORTS_OPERATIONS_	 //������, ���� ���� ����� �� ������

#define _PORTS_OPERATIONS_	  //����������, ��� ���� ��������

//-------- Por0
void dir_out_p0(int a,int p);
void dir_in_p0(int a,int p);
void set_p0(int a,int p);
void clr_p0(int a,int p);
int in_p0(int a,int p);	   // �� �������� ������-��
//-------- Port1
void dir_out_p1(int a,int p);
void dir_in_p1(int a,int p);
void set_p1(int a,int p);
void clr_p1(int a,int p);
int in_p1(int a,int p);		  // �� �������� ������-��
//-------- Port2
void dir_out_p2(int a,int p);
void dir_in_p2(int a,int p);
void set_p2(int a,int p);
void clr_p2(int a,int p);
//-------- Port3
void dir_out_p3(int a,int p);
void dir_in_p3(int a,int p);
void set_p3(int a,int p);
void clr_p3(int a,int p);
//-------- Port4
void dir_out_p4(int a,int p);
void dir_in_p4(int a,int p);
void set_p4(int a,int p);
void clr_p4(int a,int p);

 #endif
