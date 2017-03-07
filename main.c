#include <REGX51.H>
#include <stdio.h>

//**   Standard 8051 Port definition   **//
//#define P0   0x80
//#define P1   0x90
//#define P2   0xA0
//#define P3   0xB0

#include "lcd.h"
#include "adc.h"
#include "serialio.h"
#include "utils.h"
#include "dcmotor2ch.c"

sbit BUZZER=P1^6;
unsigned char adc1, adc2, adc3;
char buf[16];

unsigned char automode;

void UARTInit(void)
{
       /* Set up Timer 0 for the serial port */

        SCON = 0x50;        /* mode 1, 8-bit uart, enable receiver */
        TMOD = 0x20;        /* timer 1, mode 2, 8-bit reload */
        TH1  = 0xfd;        /* reload value for 9600 baud */
        ET0  = 0;                /* we don't want this timer to make interrupts */
        TR1  = 1;                /* start the timer */
        TI   = 1;                /* clear the buffer */

        /*
         * The compiler automatically installs the interrupt handler, so
         * all that needs to be done to use it is enable interrupts.  First,
         * speficially enable the serial interrupt, then enable interrupts.
         */
        
        ES   = 1;                /* allow serial interrupts */
        EA   = 1;                /* enable interrupts */
}
void serial_int (void) interrupt 4
{
        static char        chr = '\0';        /* character buffer */

        /* 
         * The interrupt was generated, but it is still unknown why.  	
         * First,check the RI flag to see if it was because a new character 	 was received.
         */

        if (RI == 1)        /* it was a receive interrupt */
        {
                chr = SBUF;        /* read the character into our local buffer */
                RI = 0;        /* clear the received interrupt flag */
                TI = 1;        /* signal that there's a new character to send */

			// TODO
			if(chr=='A')
				automode = 1;
			if(chr=='S')
			{
				automode  = 0;
				// stop
				dcmotorOff1();
				dcmotorOff2();
			}

			if(chr=='F')
			{
		// forward
		dcmotorOnCW1();
		dcmotorOnCW2();				
			}

			if(chr=='B')
			{
		// Back
		dcmotorOnCCW1();
		dcmotorOnCCW2();				
			}

			if(chr=='L')
			{
		// left
		dcmotorOnCW1();
		dcmotorOnCCW2();				
			}

			if(chr=='R')
			{
		// right
		dcmotorOnCCW1();
		dcmotorOnCW2();				
			}

        }
}
void main()
{

	BUZZER = 0; //off
	automode  = 0;
	// stop
	dcmotorOff1();
	dcmotorOff2();

	lcdInit();
// -=-=- Welcome LCD Message -=-=-=
	lcdClear();
	lcdGotoXY(0,0);	 // 1st Line of LCD
	//       "xxxxxxxxxxxxxxxx"
	lcdPrint("Millitary Survl.");
	lcdGotoXY(0,1);	 // 2nd Line of LCD
	//       "xxxxxxxxxxxxxxxx"
	lcdPrint("Robot controller");
	delayms(5000); // 5 sec 
		lcdClear();
	lcdGotoXY(0,0);	 // 1st Line of LCD
	//       "xxxxxxxxxxxxxxxx"
	lcdPrint("S.A.K.P");
	lcdGotoXY(0,1);	 // 2nd Line of LCD
	//       "xxxxxxxxxxxxxxxx"
	lcdPrint("C.O.E.");
	delayms(5000); // 5 sec 

	initADC();
	UARTInit();

	lcdClear();

	while(1)
	{
		//LED = 1;
		//delayms(100);		
		adc1 = (getADC(1)*1.960); // Temp LM35
		//LED = 0;
		//delayms(100);
		adc2 = getADC(2); // Gas						
		//LED = 1;
		//delayms(250);
		//adc3 = (getADC(3)*0.39); // Hum						
		
		//delayms(100);
		adc3 = getADC(3); // IR						

		lcdClear();
		sprintf (buf, "T:%2bu.C G:%bu", adc1, adc2);
		lcdPrint(buf);
		lcdGotoXY(0,1);	 // 2nd Line of LCD
		sprintf (buf, "IR:%bu", adc3);
		lcdPrint(buf);

		// printf("test");
	    printf("T:%03bu G:%03bu IR:%03bu", adc1, adc2, adc3);
		putchar(13); // new line char

		delayms(100);
		if(automode==1)
		{
			if(adc3<240)
			{
			dcmotorOnCCW1(); // TURN RIGHT				
			dcmotorOnCW2();	
			delayms(500);
			}

		// forward
		dcmotorOnCW1();
		dcmotorOnCW2();

		}
	}
 }	