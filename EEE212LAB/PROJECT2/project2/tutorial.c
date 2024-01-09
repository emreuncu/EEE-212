#include <MKL25Z4.h>
#include <stdio.h>
#include "utils.h"
#define square 37
#define sawtooth 33
int squarewave[square];
int sawtoothwave[sawtooth];
void ADC0_init(void);
void DAC0_init(void);
void SysTick_Handler(void);
void PORTA_IRQHandler(void);
void init_sys(void);
volatile int m = 0;
static int n = 6;

int main (void) {	
	LCD_init();
	LCD_command(0x01);
	print_fnc("frequency: 840Hz");
	LCD_command(0xC0);
	print_fnc("amplitude: ");
	int x;
	float coef = 0;	
	const static int sinwawe[64] =		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0,39,345,600,910,1264,1648,2048,2447,2831,3185,
		3495,3750,3939,4056,4056,4056,3939,3750,3495,3185,
	  2831,2447,2048,1648,1264,910,600,345,39};

	
	init_sys();	
	DAC0_init();
	ADC0_init();
	uint32_t result = 0;
	
	while (1) {
			int i;
			ADC0->SC1[0] = 0; 
			while(!(ADC0->SC1[0] & 0x80)){}
				if (m == 0){
//				for (x = 0; x < 64; x++){
//					DAC0->DAT[0].DATL = ((int)(WavesPLS[x] * coef)) & 0xff; 
//					DAC0->DAT[0].DATH = (((int)(WavesPLS[x] * coef)) >> 8) & 0x0f;
//					Delay(n);}
				for(i=0; i<square/2; i++) {	
			    squarewave[i] = 5000;}
			  for(i=square/2; i<square; i++) {
			    squarewave[i]=0; }
			
			DAC0_init(); 
			while (1) {
				if (m == 0){
				for (i = 0; i < square; i++) {
					Delay(1);
					ADC0->SC1[0] = 0; 
					while(!(ADC0->SC1[0] & 0x80)) { } 
					result = ADC0->R[0];
					DAC0->DAT[0].DATL = result*squarewave[i]/5000 & 0xff; 
					DAC0->DAT[0].DATH = (result*squarewave[i]/5000 >> 8) & 0x0f;
					Delay(1); }}
					else {
						break; }}}
					
					if (m == 1){
						for (x = 0; x < 64; x++){
							DAC0->DAT[0].DATL = ((int)(sinwawe[x] * coef)) & 0xff; 
							DAC0->DAT[0].DATH = (((int)(sinwawe[x] * coef)) >> 8) & 0x0f;
							Delay(n); }}
					
					if (m == 2){
//					for (x = 0; x < 64; x++){
//						DAC0->DAT[0].DATL = ((int)(WavesSAW[x] * coef)) & 0xff; 
//						DAC0->DAT[0].DATH = (((int)(WavesSAW[x] * coef)) >> 8) & 0x0f;
//						Delay(n);}
				  for(i=0;i<sawtooth;i++)	{
						sawtoothwave[i]=i; }		
	
			DAC0_init(); 
			while (1) {
				if (m == 2){
				for (i = 0; i < sawtooth; i++) {
					Delay(1);
					ADC0->SC1[0] = 0; 
					while(!(ADC0->SC1[0] & 0x80)) { } 
					result = ADC0->R[0]; 
					DAC0->DAT[0].DATL = result*sawtoothwave[i]/(sawtooth) & 0xff; 
					DAC0->DAT[0].DATH = (result*sawtoothwave[i]/(sawtooth) >> 8) & 0x0f;
					Delay(1); }}
					else {
						break; }}}
				
			result = ADC0->R[0]; 
			coef = result / 4096.0; }}

void init_sys(void) {
	__disable_irq(); /* disable all IRQs */
	
	SIM->SCGC5 |= 0x400;  /*enable port B for output*/
	PORTB->PCR[1] = 0X100; /* make PTB1 GPIO*/
	PORTB->PCR[2] = 0X100; /* make PTB2 GPIO*/
	PORTB->PCR[3] = 0X100; /* make PTB3 GPIO*/
	PTB->PDDR |= 0x0E ;/*make PTB1,2,3 outputs*/

	
	SIM->SCGC5 |= 0x200; /* enable clock to Port A */
	/* configure PTA1 for interrupt */
	PORTA->PCR[1] |= 0x00100;  
	PORTA->PCR[1] |= 0x00003; /*resistance calistiriyor */
	PTA->PDDR &= ~0x0002; /* make pin input */
	PORTA->PCR[1] &= ~0xF0000; /* clear interrupt selection */
	PORTA->PCR[1] |= 0xA0000; /* enable falling edge interrupt */

	SysTick->LOAD = (41940000/16) - 1; /*to make 2 second delay*/
	SysTick->CTRL = 3;			/*clock is divided by 16 make such a long delay*/
	
	NVIC->ISER[0] |= 0x40000000; /* enable INT30 (bit 30 of ISER[0]) */
	__enable_irq(); /* global enable IRQs */
}

void DAC0_init(void) {
	SIM->SCGC6 |= 0x80000000; /* clock to DAC module */
	DAC0->C1 = 0; /* disable the use of buffer */
	DAC0->C0 = 0x80 | 0x20; /* enable DAC and use software trigger */
}

void SysTick_Handler(void) {

	uint32_t result = 0;
	char arry[4];
	ADC0->SC1[0] = 0; 
	result = ADC0->R[0]; 
	result = ((result + 1)*3.3)*1000/4096;
			result = (float) result;
			print_to_arr(arry, result, 1);
			LCD_command(0x01);
			print_fnc("frequency: 840Hz");
			LCD_command(0xC0);
			print_fnc("amplitude: ");
////      float resultasil = result
////			int r3 = result % 10; result = result / 10;
////	    int r2 = result % 10; result = result / 10;
////	    int r1 = result % 10; result = result / 10;
////	    int r0 = result % 10; result = result / 10;
	if (result > 1000){
			LCD_data(arry[0]);
			LCD_data('.');
			LCD_data(arry[1]);
			LCD_data(arry[2]);
			LCD_data('V');}
////		if (resultasil > 1000){
////			LCD_data(r0 + '0');
////			LCD_data('.');
////			LCD_data(r1 + '0');
////			LCD_data(r2 + '0');
////			LCD_data('V');}
	else{
		  LCD_data('0');
			LCD_data('.');
			LCD_data(arry[0]);
			LCD_data(arry[1]);
			LCD_data('V');}
////		else{
////		  LCD_data('0');
////			LCD_data('.');
////			LCD_data(r1 + '0');
////			LCD_data(r2 + '0');
////			LCD_data('V');}
}

void ADC0_init(void) {
	SIM->SCGC5 |= 0x2000; /* clock to PORTE */
	PORTE->PCR[20] = 0; /* PTE20 analog input */
	SIM->SCGC6 |= 0x8000000; /* clock to ADC0 */
	ADC0->SC2 &= ~0x40; /* software trigger */
	ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00; /* clock div by 4, long sample time, single ended 12 bit, bus clock */
}


void PORTA_IRQHandler(void) {	
	Delay(300000);
	m = (m + 1) % 3;  
	PORTA->ISFR = 0x00000002; /* clear interrupt flag  001 sended */
}
