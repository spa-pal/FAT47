#ifndef  _oleg_keypad_INCLUDED_
#define _oleg_keypad_INCLUDED_

                     

#define COUNT_MAX 1


char R_OFF,R_ON;
void keypad_long (bool bit,unsigned char *count,unsigned short *flag);	 // определяет дл.нажатие
void keypad_short (bool bit,unsigned char *count,unsigned char *flag);
void keypad_srt (bool bit,unsigned char *count,unsigned char *flag);
void keypad_fixed (bool bit,unsigned char *count,unsigned char *flag); 


#include "oleg_keypad.c"

#endif

