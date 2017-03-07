#include<AT89X51.H>
#define L293D_A P2_0 //positive of motor
#define L293D_B P2_1 //negative of motor
#define L293D_E P2_2 //enable L293D
//funtion prototype
void rotate_f(void);
void rotate_b(void);
void breaks(void);
void delay(void);
void main()
{
	while(1)
	{
		rotate_f();
		delay();
		breaks();
		delay();
		rotate_b();
		delay();
		breaks();
		delay();
	 }				//do this infinitely

}
 void rotate_f()
 {
  L293D_A=1; //positive of motor 1
  L293D_B=0; //negative of motor 0
  L293D_E=1; //enable L293D
 }

 void rotate_b()
 {
  L293D_A=0; //positive of motor 0
  L293D_B=1; //negative of motor 1
  L293D_E=1; //enable L293D
 }
 void breaks()
 {
  L293D_A=0; //positive of motor 1
  L293D_B=0; //negative of motor 0
  L293D_E=0; //disable L293D
 }
 void delay()				//delay
 {
  unsigned char i,j,k;
  for(i=0;i<255;i++)
  	for(j=0;j<255;j++)
  		for(k=0;k<255;k++);
  }