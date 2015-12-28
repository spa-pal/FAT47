#ifndef _MENU_NAVI_	 //������, ���� ���� ����� �� ������

#define _MENU_NAVI_	  //����������, ��� ���� ��������


#define MAX_MAIN_MENU 19			  //���-�� ����� � ������ ����
//---���� �5---
#define MAX_P5_MENU MAX_MAIN_MENU+7
//---���� �6---
#define MAX_P6_MENU MAX_P5_MENU+7
//---���� �7---
#define MAX_P7_MENU MAX_P6_MENU+7
//---���� �8---
#define MAX_P8_MENU MAX_P7_MENU+4
//---���� �9---
#define MAX_P9_MENU MAX_P8_MENU+4
//---���� �10---
#define MAX_P10_MENU MAX_P9_MENU+10
//---���� �11---
#define MAX_P11_MENU MAX_P10_MENU+4
//---���� �12---
#define MAX_P12_MENU MAX_P11_MENU+6
//---���� �13---
#define MAX_P13_MENU MAX_P12_MENU+6
//---���� �14---
#define MAX_P14_MENU MAX_P13_MENU+37
//---���� �15---
#define MAX_P15_MENU MAX_P14_MENU+6
//---���� �16---
#define MAX_P16_MENU MAX_P15_MENU+0
//---���� �17---
#define MAX_P17_MENU MAX_P16_MENU+8
//---���� �18---
#define MAX_P18_MENU MAX_P17_MENU+8
//---���� �19---
#define MAX_P19_MENU MAX_P18_MENU+22
//-----------------------------------
//---���� �13-�2---	126
#define MAX_P13_P2_MENU MAX_P19_MENU+4
//---���� �13-�3---
#define MAX_P13_P3_MENU MAX_P13_P2_MENU+7
//---���� �13-�4---	 125
#define MAX_P13_P4_MENU MAX_P13_P3_MENU+4
//---���� �13-�5---  125
#define MAX_P13_P5_MENU MAX_P13_P4_MENU+4
//-----------------------------------
//---���� �14-�2---
#define MAX_P14_P2_MENU MAX_P13_P5_MENU+4
//---���� �14-�3---
#define MAX_P14_P3_MENU MAX_P14_P2_MENU+4
//---���� �14-�4---
#define MAX_P14_P4_MENU MAX_P14_P3_MENU+4
//---���� �14-�5---
#define MAX_P14_P5_MENU MAX_P14_P4_MENU+9
//---���� �14-�11---
#define MAX_P14_P11_MENU MAX_P14_P5_MENU+5
//---���� �14-�32--- 
#define MAX_P14_P32_MENU MAX_P14_P11_MENU+5
//---���� �14-�38---  873
#define MAX_P14_P38_MENU MAX_P14_P32_MENU+5
//-----------------------------------
//---���� �19-�17---
#define MAX_P19_P17_MENU MAX_P14_P38_MENU+5
//---���� �19-�18---  
#define MAX_P19_P18_MENU MAX_P19_P17_MENU+5
//---���� �19-�19---  
#define MAX_P19_P19_MENU MAX_P19_P18_MENU+5


//--------------------------------

extern char lcdPointer, capt;

extern char* mainMenu[];
//--------������ �������� ���� ���������������� � ��������� ��������� �� ���� 
typedef enum {mainMnu,P4menu,P5menu,P6menu,P7menu,P8menu,P9menu,P10menu,P11menu,P12menu,P13menu,P14menu,P15menu,P14P3menu,} menu_enum;
extern menu_enum menu;

extern char startString,endString;
extern int 	menuPointer;
extern void menuNavi(void);

void writeLCD_buffer (void);

#endif

