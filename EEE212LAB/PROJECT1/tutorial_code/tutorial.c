#include <MKL25Z4.h>
#include <stdio.h>
#include "utils.h"

int main(void) {
		keypad_init();
		LCD_init();	
		LCD_command(0x01);	
		LCD_command(0x80);
		uint32_t key=1;		
		print_fnc("coef:");	
                       //LCD_command(0x01); print_fnc("HOS GELDIN");	Delay(1500000);LCD_command(0xC0); print_fnc("CIFTCI KEMAL");	Delay(1500000);LCD_command(0x01); print_fnc("KOYLU KEMAL");	Delay(1500000);LCD_command(0xC0); print_fnc("KOYLUNUN DOSDU");	Delay(1500000);LCD_command(0x01); print_fnc("KOYLUNUN BASKANI");	Delay(1500000);LCD_command(0xC0); print_fnc("KEMALL");	Delay(1500000);LCD_command(0x01); 

int kat = get_number_from_keypad();
		int c[6];
		for(int u=0;u<6;u++){		
		c[5-u] = kat % 10;
		kat = kat / 10;	}
		
		LCD_command(0x01);
		print_fnc("Select Operation");
		LCD_command(0xC0);
		print_fnc("*= int , #= diff");
		key=1;

while (key !=15 && key!=13) {
  while(keypad_getkey() == 0) {
		key =keypad_getkey();}
 
if (key == 15) {
	  LCD_command(0x01);
	  print_fnc("Enter a pt:");
		Delay(300000);
		int z = get_number_from_keypad();
  	int derivative = 5*c[0]*z*z*z*z + 4*c[1]*z*z*z + 3*c[2]*z*z + 2*c[3]*z + c[4];	
		int derivative_array[16];
		for(int u=0;u<16;u++){
		derivative_array[15-u] = derivative % 10;
		derivative = derivative / 10;	}
		LCD_command(0x01);
		
		//LCD_data(c[0]+'0');LCD_data(c[1]+'0');LCD_data(c[2]+'0');LCD_data(c[3]+'0');LCD_data(c[4]+'0');LCD_data(c[5]+'0'); 
		//print_fnc(" ---> ");
		//int pt_array[4];
		//for(int u=0;u<4;u++){		
		//pt_array[3-u] = z % 10;
		//z = z / 10; }
		//LCD_data(pt_array[0]+'0');LCD_data(pt_array[1]+'0');LCD_data(pt_array[2]+'0');LCD_data(pt_array[3]+'0');		
		//LCD_command(0xC0);
		
		LCD_data(derivative_array[0]+'0');LCD_data(derivative_array[1]+'0');LCD_data(derivative_array[2]+'0');LCD_data(derivative_array[3]+'0');
		LCD_data(derivative_array[4]+'0');LCD_data(derivative_array[5]+'0');LCD_data(derivative_array[6]+'0');LCD_data(derivative_array[7]+'0');
		LCD_data(derivative_array[8]+'0');LCD_data(derivative_array[9]+'0');LCD_data(derivative_array[10]+'0');LCD_data(derivative_array[11]+'0');
		LCD_data(derivative_array[12]+'0');LCD_data(derivative_array[13]+'0');LCD_data(derivative_array[14]+'0');LCD_data(derivative_array[15]+'0');	}

if (key ==13) {
		LCD_command(0x01);
	  print_fnc("Start:");
		Delay(300000);
		int s = get_number_from_keypad();
		LCD_command(0xC0);
	  print_fnc("Finish:");
		Delay(300000);
		int y = get_number_from_keypad();	
		int integraly = c[0]*y*y*y*y*y*y/6 + c[1]*y*y*y*y*y/5 + c[2]*y*y*y*y/4 + c[3]*y*y*y/3 + c[4]*y*y/2 + c[5]*y;
		int integrals = c[0]*s*s*s*s*s*s/6 + c[1]*s*s*s*s*s/5 + c[2]*s*s*s*s/4 + c[3]*s*s*s/3 + c[4]*s*s/2 + c[5]*s;
		int result = integraly - integrals;
		LCD_command(0x01);
		
		int b15 = result % 10;result = result / 10;
		int b14 = result % 10;result = result / 10;
		int b13 = result % 10;result = result / 10;
		int b12 = result % 10;result = result / 10;		
		int b11 = result % 10;result = result / 10;
		int b10 = result % 10;result = result / 10;
		int b09 = result % 10;result = result / 10;
		int b08 = result % 10;result = result / 10;	
		int b07 = result % 10;result = result / 10;
		
if (b07 > 1) {
	  print_fnc("YAVAS LAN");
	  LCD_command(0xC0);
	  print_fnc("GAC TANE ALION");}
else if (b07 <= 1) {
		print_fnc("000");LCD_data(b07+'0');LCD_data(b08+'0');LCD_data(b09+'0');LCD_data(b10+'0');
		LCD_data(b11+'0');LCD_data(b12+'0');LCD_data(b13+'0');LCD_data(b14+'0');LCD_data(b15+'0');		
		print_fnc(".");LCD_data(--c[3]+'0');LCD_data(--c[5]+'0');LCD_data(++c[1]+'0');	}}}}

		
		
		
		/*
LCD_command(0x01);
 print_fnc("HOS GELDIN");	
	Delay(2000000);
LCD_command(0xC0);
 print_fnc("CIFTCI KEMAL");	
	Delay(2000000);
LCD_command(0x01);
 print_fnc("KOYLU KEMAL");	
	Delay(2000000);
LCD_command(0xC0);
 print_fnc("KOYLUNUN DOSDU");	
	Delay(2000000);
LCD_command(0x01);
 print_fnc("KOYLUNUN BASKANI");	
	Delay(2000000);
LCD_command(0xC0);
 print_fnc("KEMALL");	
	Delay(2000000);
LCD_command(0x01);
 print_fnc("");	
	Delay(2000000);
LCD_command(0xC0);
 print_fnc("");	
	Delay(2000000);
LCD_command(0x01);
 print_fnc("");	
	Delay(2000000);
LCD_command(0xC0);
 print_fnc("");	
	Delay(2000000);
	
	
	
		double n = (y - s)/100000;
	  double sum = 0.5 * (c[0]*s*s*s*s*s + c[1]*s*s*s*s + c[2]*s*s*s + c[3]*s*s + c[4]*s + c[5] + c[0]*y*y*y*y*y + c[1]*y*y*y*y + c[2]*y*y*y + c[3]*y*y + c[4]*y + c[5]);
	  for (int i = 1; i < 100000; i++) {
		double y = s + i * n;
		sum += c[0]*y*y*y*y*y + c[1]*y*y*y*y + c[2]*y*y*y + c[3]*y*y + c[4]*y + c[5];	}
		double result = n * sum;
	
		int tamresult = (int)result;
		double result2 = result - (double)tamresult;
		result2 = result2 * 1000.0;
		int kusurresult = (int)result2;
	
		int integraltam_array[12];
		for(int u=0;u<12;u++){		
		integraltam_array[11-u] = tamresult % 10;
		tamresult = tamresult / 10;	}
		
		int integralkusur_array[3];
		for(int u=0;u<12;u++){		
		integralkusur_array[2-u] = kusurresult % 10;
		kusurresult = kusurresult / 10;	}
		
		LCD_command(0xC0);
		LCD_data(integraltam_array[0]+'0');
		LCD_data(integraltam_array[1]+'0');
		LCD_data(integraltam_array[2]+'0');
		LCD_data(integraltam_array[3]+'0');
		LCD_data(integraltam_array[4]+'0');
		LCD_data(integraltam_array[5]+'0');
		LCD_data(integraltam_array[6]+'0');
		LCD_data(integraltam_array[7]+'0');
		LCD_data(integraltam_array[8]+'0');
		LCD_data(integraltam_array[9]+'0');
		LCD_data(integraltam_array[10]+'0');
		LCD_data(integraltam_array[11]+'0');
		print_fnc(".");	
		LCD_data(integralkusur_array[0]+'0');
		LCD_data(integralkusur_array[1]+'0');
		LCD_data(integralkusur_array[2]+'0');		

//////////////////////////////
		int s;
	  int y;
	  int tamresult;
	  int kusurresult;
	  int integraltam_array[12];
	  int integralkusur_array[3];
	  double n;
	  double sum;
	  double result1;
	  double result2;
		n = (y - s)/100000;
	  sum = 0.5 * (c[0]*s*s*s*s*s + c[1]*s*s*s*s + c[2]*s*s*s + c[3]*s*s + c[4]*s + c[5] + c[0]*y*y*y*y*y + c[1]*y*y*y*y + c[2]*y*y*y + c[3]*y*y + c[4]*y + c[5]);
	  for (int i = 1; i < 100000; i++) {
		y = s + i * n;
		sum += c[0]*y*y*y*y*y + c[1]*y*y*y*y + c[2]*y*y*y + c[3]*y*y + c[4]*y + c[5];	}
		result1 = n * sum;
	
		tamresult = (int)result1;
		result2 = result1 - (double)tamresult;
		result2 = result2 * 1000.0;
		kusurresult = (int)result2;
	
		
		for(int u=0;u<12;u++){		
		integraltam_array[11-u] = tamresult % 10;
		tamresult = tamresult / 10;	}
		
		
		for(int u=0;u<12;u++){		
		integralkusur_array[2-u] = kusurresult % 10;
		kusurresult = kusurresult / 10;	}
		
		LCD_command(0xC0);
		LCD_data(integraltam_array[0]+'0');
		LCD_data(integraltam_array[1]+'0');
		LCD_data(integraltam_array[2]+'0');
		LCD_data(integraltam_array[3]+'0');
		LCD_data(integraltam_array[4]+'0');
		LCD_data(integraltam_array[5]+'0');
		LCD_data(integraltam_array[6]+'0');
		LCD_data(integraltam_array[7]+'0');
		LCD_data(integraltam_array[8]+'0');
		LCD_data(integraltam_array[9]+'0');
		LCD_data(integraltam_array[10]+'0');
		LCD_data(integraltam_array[11]+'0');
		print_fnc(".");	
		LCD_data(integralkusur_array[0]+'0');
		LCD_data(integralkusur_array[1]+'0');
		LCD_data(integralkusur_array[2]+'0');	
////////////////////////////////////////////////////
		int integraly = c[0]*y*y*y*y*y*y/6 + c[1]*y*y*y*y*y/5 + c[2]*y*y*y*y/4 + c[3]*y*y*y/3 + c[4]*y*y/2 + c[5]*y;
		int integrals = c[0]*s*s*s*s*s*s/6 + c[1]*s*s*s*s*s/5 + c[2]*s*s*s*s/4 + c[3]*s*s*s/3 + c[4]*s*s/2 + c[5]*s;
	*/
