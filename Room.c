#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
void SystemInit(){};
void init()
  {   
	  SYSCTL_RCGCGPIO_R |= 0x20;  //Connect Clock to portF
    while((SYSCTL_RCGCGPIO_R&0x20)!=0x20){} //wait til portF is Enabled
    GPIO_PORTF_LOCK_R = 0x4C4F434B; //Lock register to unLock portF
    GPIO_PORTF_CR_R |=0x1F;  //Comment Register allow change of data   11111
    GPIO_PORTF_AFSEL_R=0;   //NO Alternative Function 
	  GPIO_PORTF_PCTL_R=0;    //Not using Alternative Functions
    GPIO_PORTF_AMSEL_R=0;   //Disable Analog
    GPIO_PORTF_DIR_R |=0x2E;  //input 0 /0utput 1//0011110 switch o,4 leds 1 2 3
    GPIO_PORTF_DEN_R|=0x2E;   //1110
		GPIO_PORTF_DATA_R=0x00;    
  }

	void Relay_init()
{
SYSCTL_RCGCGPIO_R |= 0x10;  //Connect Clock to portE   10000
    while((SYSCTL_RCGCGPIO_R&0x10)!=0x10){} 
			 GPIO_PORTE_LOCK_R = 0x4C4F434B; //Lock register to unLock portE
    GPIO_PORTE_CR_R |=0x3F;  //Comment Register allow change of data   11111
    GPIO_PORTE_AFSEL_R=0;   //NO Alternative Function 
	  GPIO_PORTE_PCTL_R=0;    //Not using Alternative Functions
    GPIO_PORTE_AMSEL_R=0;   //Disable Analog
    GPIO_PORTE_DIR_R |=0x01;  //i1 bit for relay
    GPIO_PORTE_DEN_R|=0x01;   //1110
		GPIO_PORTE_DATA_R=0x00;    
			
}
void uartInit()
{
SYSCTL_RCGCGPIO_R |= 0x01;  //Connect Clock to portA
    while((SYSCTL_RCGCGPIO_R&0x01)!=0x01){} 
			SYSCTL_RCGCUART_R |= 0x01;
			 while((SYSCTL_RCGCUART_R&0x01)!=0x01){} 
    GPIO_PORTA_LOCK_R = 0x4C4F434B; //Lock register to unLock portA
    GPIO_PORTA_CR_R |=0x03;  //Comment Register allow change of data
    GPIO_PORTA_AFSEL_R|=0x03;   // Alternative Function 
	  GPIO_PORTA_PCTL_R=0x11;    // using Alternative Functions
    GPIO_PORTA_AMSEL_R=0;   //Disable Analog
  //  GPIO_PORTA_DIR_R |=0x02;  //input 0 /0utput 1//0001110 sitch o,4 leds 1 2 3
    GPIO_PORTA_DEN_R|=0x03;   //1110
		GPIO_PORTA_DATA_R=0x00; 
		UART0_CTL_R&=0xfff0;
    UART0_IBRD_R=104;
    UART0_FBRD_R=21;
		UART0_LCRH_R=0x0070; //01110000	
    UART0_CTL_R=0x0301;				 
}

void writeChar (char c)
   {
    while (  (UART0_FR_R&0x20)!=0){}
		UART0_DR_R=c;
		
			
   }
char ReadChar ()
   {
		 char c;
    while (  (UART0_FR_R&0x10)!=0){}		
		 c=UART0_DR_R;
   return c;
   
   }
	 void	delayUs(char C)
	 {
	 int i,j;
	for(i=0;i<C;i++){
		for(j=0;j<16;j++){}
	}
	 }
	 void LCD_command(char command)
	 {		 
	  GPIO_PORTA_DATA_R &=0x1f; //00011111
	  GPIO_PORTB_DATA_R =command;
		GPIO_PORTA_DATA_R |=0x80;   
	 	delayUs(2);
  	GPIO_PORTA_DATA_R &=0x1f;   
	 
	 }
	 void LCD_DATA(char data)
	 {
	  GPIO_PORTA_DATA_R &=0x3f; // 00111111
	  GPIO_PORTB_DATA_R =data;
		GPIO_PORTA_DATA_R |=0x80;   
	 	delayUs(2);
  	GPIO_PORTA_DATA_R &=0x1f;   
	 }
void Lcd_init(void)
 {
	  SYSCTL_RCGCGPIO_R |= 0x02;  //Connect Clock to portB
    while((SYSCTL_RCGCGPIO_R&0x02)!=0x02){} //wait til portBd
		SYSCTL_RCGCGPIO_R |= 0x01;  //Connect Clock to portA 
    while((SYSCTL_RCGCGPIO_R&0x01)!=0x01){} //wait til portA is Enabled
	  GPIO_PORTA_LOCK_R = 0x4C4F434B; //Lock register to unLock portA
	  GPIO_PORTB_LOCK_R = 0x4C4F434B; //Lock register to unLock portB
		GPIO_PORTA_DIR_R |=0x70;  //
    GPIO_PORTA_DEN_R|=0x70;   // 
    GPIO_PORTB_DIR_R |=0xff;  //
    GPIO_PORTB_DEN_R|=0xff;   //		
	  LCD_command(0x30); //WAKE UP 
	  LCD_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x06); /* move cursor right */
    LCD_command(0x01); /* clear screen, move cursor to home */
    LCD_command(0x0F);		
 }
	  void keypad_init(void)
	{
    SYSCTL_RCGCGPIO_R |= 0x04;  //Connect Clock to portc 0100
    while((SYSCTL_RCGCGPIO_R&0x04)!=0x04){} //wait til portc is Enabled
	  SYSCTL_RCGCGPIO_R |= 0x08;  //Connect Clock to portD 1000
    while((SYSCTL_RCGCGPIO_R&0x08)!=0x08){} //wait til portD is Enabled
    GPIO_PORTC_LOCK_R = 0x4C4F434B; //Lock register to unLock portB		
		GPIO_PORTD_LOCK_R = 0x4C4F434B; //Lock register to unLock portD
    GPIO_PORTC_CR_R |=0xF0;  //Comment Register allow change of data   11111
	  GPIO_PORTD_CR_R |=0x0F;  //Comment Register allow change of data   11111
    GPIO_PORTC_AFSEL_R=0;   //NO Alternative Function 
		GPIO_PORTD_AFSEL_R=0;   //NO Alternative Function 
	  GPIO_PORTC_PCTL_R=0;    //Not using Alternative Functions
		GPIO_PORTD_PCTL_R=0;    //Not using Alternative Functions
    GPIO_PORTC_AMSEL_R=0;   //Disable Analog
		GPIO_PORTD_AMSEL_R=0;   //Disable Analog		
    GPIO_PORTC_DIR_R |=0x0f;  //COL input
	  GPIO_PORTC_DEN_R |=0xf0;  //COL enable
		GPIO_PORTC_PUR_R |=0xf0;  //COL pullup Reesitance		
		GPIO_PORTD_DIR_R |=0x0f;  //ROW OUTPUT
    GPIO_PORTD_DEN_R |=0x0f; // ROW enable
 	  GPIO_PORTD_ODR_R |=0x0f; // ROW OPEN DRAIN
			
   }
  char get_keypad(void){
	 
	int row ,col;
	const char k_map[4][4]=
		{
  
    {'1','2','3','A'},
		{'4','5','6','B'},	
   	{'7','8','9','C'},
		{'*','0','#','D'}
		
		};
	
	Lcd_init();
	keypad_init();
	while (1)
	{	
		row =0;
	  GPIO_PORTD_DATA_R= 0x0E;
   	delayUs(2);
		col =  GPIO_PORTC_DATA_R&0xF0;
		if(col!=0xF0)break;
		row =1;
	  GPIO_PORTD_DATA_R = 0x0D;
	  delayUs(2);
		col =  GPIO_PORTC_DATA_R&0xF0;
		if(col!=0xF0)break;
		row =2;
	  GPIO_PORTD_DATA_R = 0x0B;
		delayUs(2);
		col = GPIO_PORTC_DATA_R&0xF0;
		if(col!=0xF0)break;
		row =3;
	  GPIO_PORTD_DATA_R= 0x07;
	  delayUs(2);
		col = GPIO_PORTC_DATA_R&0xF0;
		if(col!=0xF0)break;				
		if(( GPIO_PORTC_DATA_R&0xF0)==0xF0)return 'h';	
		return 'h';
	}	
	if(col==0xE0){LCD_DATA(k_map[row][0]);return k_map[row][0];}
	if(col==0xD0){LCD_DATA(k_map[row][1]);return k_map[row][1];}
	if(col==0xB0){LCD_DATA(k_map[row][2]);return k_map[row][2];}
	if(col==0x70){LCD_DATA(k_map[row][3]);return k_map[row][3];}
	return 0;
}
void guestRoom(char r ,char roomPassword[10][4])
{ int i;
	char z;
	char enteredPassword[4];//={'1','2','3','4'}; for simulation
	int correct=1; 
	keypad_init();
	 Lcd_init();	
	while(1)
	{
		z=get_keypad();
		if(z!='h'){enteredPassword[i]=z;i=i+1;}
		if (i==4)break;
	}
  // checking entered keypad password by pc password
 for (i=0;i<4;i++)
 {
  if (enteredPassword[i]!=roomPassword[r][i]){correct=0;break;}
 }
 if (correct)
	 {
	 GPIO_PORTF_DATA_R=0x06;//correct password pink lamp
	 GPIO_PORTE_DATA_R=0x01;// correct password open door
	 }
 else
	 {
	 GPIO_PORTF_DATA_R=0x0E;//white lamp
	 
   }
}
int main()
{  
	char roomPassword[10][4];		//room number is index of passwords (password is the map of 10*5)
   char s,r;//s is room status r is room number;
	  //int  ocRoom=0;
  int i;
	char state[10];
	 char x='1';
  init();
  Relay_init();
	uartInit();
  while(1)
  { 	
		if ( (UART0_FR_R&0x10)==0)
	{
	s=ReadChar();
	writeChar(s);
	switch (s)
	{
	case 'F':
	r=ReadChar();//read room no.
	writeChar(r);
	state[r]=s;
	if (r=='1')//to change only the lock of room 1
	{GPIO_PORTF_DATA_R=0x02;//in case of empty room red lamp will light
	GPIO_PORTE_DATA_R=0x00;// "lock room "(relay off)
	}break;
	case 'c':
	r=ReadChar();//read room no.
	writeChar(r);
	state[r]=s;
	if(r=='1')//to change only the lock of room 1
	{
	GPIO_PORTF_DATA_R=0x04;//in case of empty room blue lamp will light
	GPIO_PORTE_DATA_R=0x01;// "unlock room " (relay on) 
	}
	break;
	case 'o':
	r=ReadChar();//read room no.   1 1 1 1 1  
	writeChar(r);
	state[r]=s;
	
	for (i=0;i<4;i++){roomPassword[r][i]=ReadChar();writeChar(roomPassword[r][i]);}
	break;
  default:GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R;
	        GPIO_PORTE_DATA_R=GPIO_PORTE_DATA_R;
	}
}
	else
		{
  
	if ((GPIO_PORTF_DATA_R&0x10)==0x00&&state[x]=='o')  //if switch2 is pressed means guest wants to enter password
	
	{ 
	   GPIO_PORTF_DATA_R=0x08;// green lamp will turn on;
 	   guestRoom('1',roomPassword);
	
	}
}
  }
	
  }


