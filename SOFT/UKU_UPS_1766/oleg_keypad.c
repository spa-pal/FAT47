

void keypad_long (bool bit,unsigned char *count,unsigned short *flag){  //опрашивает один бит в порту,
									// определяет дл.нажатие
if ( bit==0){
	if (*flag<0xffff) *flag=*flag+1;
	if(*count<0xff) *count=*count+1;
}
else {
	*flag=0;
	*count=0;
}

}
/*
void keypad_long (bool bit,unsigned char *count,unsigned short *flag){  //опрашивает один бит в порту,
									// определяет дл.нажатие
if ( bit==0){
	if ( *count>COUNT_MAX ) {if (*flag<0xffff) *flag=*flag+1; *count=0;}
	else *count=*count+1;
}
else {
	if (*count==0) *flag=0;
        else *count=*count-1;
}

}
*/
//**************************************************************
void keypad_srt (bool bit,unsigned char *count,unsigned char *flag)  //опрашивает один бит в порту,определяет
{                                                       //короткое нажатие, сброс при отжатии
if ( bit==0 ){
	if ( *count>=COUNT_MAX )*flag=0xff;//COUNT_MAX-10
	else *count=*count+1;
}                            
else {
	if (*count==0) *flag=0;
        else *count=*count-1;
}

}
//*************************************************************
void keypad_short (bool bit,unsigned char *count,unsigned char *flag)  //опрашивает один бит в порту,определяет
{                                                             //короткое нажатие, сброс флага внешний
if ((bit==0)&&*flag==0 ){
	if ( *count>=COUNT_MAX ) *flag=0xff;//COUNT_MAX-10
	else if(*count<COUNT_MAX) *count=*count+1;
}                            
else if (*count!=0) *count=*count-1;

}                                               
//*************************************************************
void keypad_fixed (bool bit,unsigned char *count,unsigned char *flag) //опрашивает один бит в порту,определяет
{                                                             //короткое нажатие, сброс повторным нажатием,
if ( ((bit==0)||R_ON==1) && *flag==0){                //или бит R_OFF=1, установка R_ON=1    
	if ( *count>=COUNT_MAX ){*flag=0x0F; R_ON=0;R_OFF=0;} //COUNT_MAX-10
	else *count=*count+1;
}                            

else if ( ((bit==0)||R_OFF==1)&& *flag==0x1F ){
	if ( *count>=COUNT_MAX ) {*flag=0x2F;R_OFF=0;R_ON=0;}//COUNT_MAX-10
	else *count=*count+1;
}    

else if (*count!=0 && bit!=0) {
	*count=*count-1;
	if(*flag==0x0F) *flag=0x1F;
	else if(*flag==0x2F) *flag=0;
}
                     
}  
