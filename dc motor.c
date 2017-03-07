												  *
//* DCMotorControl.c
*
//* Created: 4/1/2011 12:08:10 AM
//*  Author: sfg
#include <REGX51.h>
int main(void)
{
P1=0xFF; //PORTD declared as output
P1=0×00;
P2=0×00; //PORTB as input
while(1)
{
//Pin 0 of PORTB high,then Moves Clockwise
//A–1–PD0
//B–0–PD1
//Enable–1–PD2
if(P2==0×01)
{
P1=0×05;
//_delay_ms(5000);
}
//Pin 0 of PORTB Low,then Moves AntiClockwise
//A–0–PD0
//B–1–PD1
//Enable–1–PD2
else
{
P1=0×06;
//_delay_ms(5000);
}
}
}


