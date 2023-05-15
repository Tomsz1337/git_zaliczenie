#include <LPC21xx.H>

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19

#define BUTTON0_bm 1<<4
#define BUTTON1_bm 1<<5
#define BUTTON2_bm 1<<6
#define BUTTON3_bm 1<<7

enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum Step {LEFT, RIGHT};


void Delay(int iCzasMs)
{
	int iCounter;
	int iCounter1MS;
	
	for(iCounter=0; iCounter<iCzasMs; iCounter++)
	{
	  for(iCounter1MS=0; iCounter1MS<122e1; iCounter1MS++){}
	}	
}

void LedInit (void)
{
	IO1DIR = IO1DIR | (LED3_bm | LED2_bm | LED1_bm | LED0_bm);
	
	IO1SET = LED0_bm;	
}

void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR = LED1_bm | LED2_bm | LED0_bm | LED3_bm;
	switch(ucLedIndeks)
	{
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
		default:
			break;
	}
}

enum KeyboardState eKeyboardRead (void)
{
	if ((IO0PIN&BUTTON0_bm) == 0)
		{
			return (BUTTON_0);
		}
	else if ((IO0PIN&BUTTON1_bm) == 0)
		{
			return (BUTTON_1);
		}
	else if ((IO0PIN&BUTTON2_bm) == 0)
		{
			return (BUTTON_2);
		}
	else if ((IO0PIN&BUTTON3_bm) == 0)
		{
			return (BUTTON_3);
		}
	else
		{
			return (RELASED);
		}
}

void KeyboardInit (void)
{
	IO0DIR = IO0DIR & (~(BUTTON1_bm | BUTTON2_bm | BUTTON3_bm | BUTTON0_bm));
}

void LedStep (enum Step Direction)
{
	static unsigned int uiLedNR;
	
	switch (Direction)
	{
		case LEFT:
			
			uiLedNR++;
			break;
		
		case RIGHT:
			
			uiLedNR--;
			break;
	}
	
	LedOn(uiLedNR%4);
}

void LedStepLeft(void)
{
		LedStep(LEFT);
}

void LedStepRight(void)
{
		LedStep(RIGHT);
}

int main()
{
	LedInit();
	KeyboardInit();
	
	while(1)
		{
			Delay(100);
			
			switch (eKeyboardRead())
			{
				case BUTTON_1:
					
					LedStepRight();
					break;
				
				case BUTTON_2:
					
					LedStepLeft();
					break;
				
				default:	
					break;
			}
		}
			
}

