#define vermelho pin_d2
#define amarelo pin_d0
#define verde pin_d1
#include <18F4550.h>
#use delay (clock=20000000)
#fuses HS,PLL5, CPUDIV1, USBDIV
#use rs232(baud=9600, xmit = PIN_C6, rcv = PIN_C7)
#include "12Keys.c"

int i, tamanho_senha = 5;

void main() {
	char senha[5] = {'5', '0', '2', '0', '6'};
	char senha_digitada[5];
	int contador = 0;
	boolean comparador;
	tecla_pres = 0;

	port_b_pullups(True);
   
	while(TRUE) {
		tecla = trata_teclas();

		if (tecla_pres) {
			printf("%c  ", tecla);
			
			if (tecla == '#') {
				for (i = 0; i < tamanho_senha; i++) {
					printf("%c", senha_digitada[i]);
				}
				
				printf("\n");
				
				comparador = true;
				for (i = 0; i < tamanho_senha; i++) {
					comparador = comparador && (senha[i] == senha_digitada[i]);
					
					
					if (!comparador) {
						printf("Senha errada\n");
						output_high(vermelho);
					}
				}
				
				if (comparador) {
					printf("Senha correta\n");
					output_low(vermelho);
					output_high(verde);
					delay_ms(5000);
					output_low(verde);
				}
				
				contador = 0;
				for (i = 0; i < tamanho_senha; i++) {
					senha_digitada[i] = '\0';     
				}
			} else {
				if (contador == tamanho_senha) {
					contador = 0;
					for (i = 0; i < tamanho_senha; i++) {
						senha_digitada[i] = '\0';
					}
				}
				
				senha_digitada[contador] = tecla;
				
				contador++;
				
				for (i = 0; i < tamanho_senha; i++) {
					printf("%c", senha_digitada[i]);
				}
				
				printf("\n");
			}
		}
	}
}
