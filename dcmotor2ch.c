sbit ENA1 = P3^0;
sbit ENB1 = P3^1;
sbit PWM1 = P3^2;

sbit ENA2 = P3^4;
sbit ENB2 = P3^5;
sbit PWM2 = P3^6;


void dcmotorOnCW1( void )
{
	ENA1 = 1;
	ENB1 = 0;
}
void dcmotorOnCCW1( void )
{
	ENA1 = 0;
	ENB1 = 1;
}
void dcmotorOff1( void )
{
	ENA1 = 0;
	ENB1 = 0;
}

void dcmotorOnCW2( void )
{
	ENA2 = 1;
	ENB2 = 0;
}
void dcmotorOnCCW2( void )
{
	ENA2 = 0;
	ENB2 = 1;
}
void dcmotorOff2( void )
{
	ENA1 = 0;
	ENB1 = 0;
}
