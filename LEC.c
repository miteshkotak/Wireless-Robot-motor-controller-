#include <REGX51.H>

void msdelay(unsigned int );

void main()
{
	P2=0x00;  //all pin of PORT2 declared as output
//------------//infinite loop
	while(1)
	{
		P2=0xFF;   //all pin high
		msdelay(250);    //delay
		P2=0x00;   //all pin low
		msdelay(250); //delay
	}
}
//---------//delay function
void msdelay(unsigned int value)
{
	unsigned int x,y;
	for(x=0;x<value;x++)
	for(y=0;y<6457;y++);
}
//In C programs you cannot be sure of delay, cause  it depends on compiler how it optimize the loops as soon as you make changes in the options the delay changes.
//you will have to use Timers for making exact delays….. it does not matters whether u need delays of ms , us or even seconds…
//below is a function of 1 second using timers…..
// the idea is to make a 50ms delay and run it 20 times as 20x50ms= 1000ms= 1sec
delay_1s() // timer of 1 sec
{
	int d;
	for(d=0;d<=20;d++)
{
	TMOD=0x01;
	TL0=0xFD;
	TH0=0x04B;
	TR0=1; // start timer.
		while(TF0==0); // run until TF turns to 1
		TR0=0; // stop timer
		TF0=0; // reset the flag
}
}