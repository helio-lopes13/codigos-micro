#define vermelho pin_d2
#define amarelo pin_d0
#define verde pin_d1
#include <18F4550.h>
#use delay (clock=20000000)
#fuses HS,PLL5, CPUDIV1, USBDIV
#use rs232(baud=9600, xmit = PIN_C6, rcv = PIN_C7)
#include "12Keys.c"

boolean flag;
int i;

void main() {
	char senha[5] = {'5', '0', '2', '0', '6'};
	char senha_digitada[5];
	int contador = 0;
	tecla_pres = 0;

	port_b_pullups(True);
   
	while(TRUE) {
		tecla = trata_teclas();

		if (tecla_pres) {
			printf("%c", tecla);
			
			senha_digitada[contador] = tecla;
			contador++;
			
			if (contador == 5) {
				for (i = 0; i < 5; i++) {
					printf("%c", senha_digitada[i]);            
				}

				contador = 0;
			}
		}
		
		switch(tecla) {
			case '1': output_high(verde);break;
			case '2': output_high(amarelo);break;
			case '3': output_high(vermelho);break;
			case '4': output_low(verde);break;
 			case '5': output_low(amarelo);break;
			case '6': output_low(vermelho);break;
			case '7': output_high(verde);output_high(amarelo);break;
			case '8': output_high(verde); output_high(vermelho);break;
			case '9': output_high(amarelo);output_high(vermelho);break;
			case '0': output_high(amarelo);output_high(verde);output_high(vermelho);break;
			case '*': output_low(amarelo);output_low(verde);output_low(vermelho);break;
			case '#': output_low(amarelo);output_low(verde);output_low(vermelho);break;
      }
   }
}
