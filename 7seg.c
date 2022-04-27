/*
PROGRAMA SIMULA��O DE DISPLAY DE 7 SEGMENTOS PLACA PICG�NIOS
AUTOR PROF. F�BIO TIMB�
*/
#include<18F4550.h>           
#use delay (clock=20000000)        
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 

int conta = 0;
int digito1, digito2;

/*Matriz de 10 posi��es contendo o valor a ser enviado para a porta D a fim de
   mostrar o d�gito referente nos displays */
int digito[10] =
               {0b00111111,    //D�gito 0
                0b00000110,    //D�gito 1
                0b01011011,    //D�gito 2
                0b01001111,    //D�gito 3
                0b01100110,    //D�gito 4
                0b01101101,    //D�gito 5
                0b01111101,    //D�gito 6
                0b00000111,    //D�gito 7
                0b01111111,    //D�gito 8
                0b01101111     //D�gito 9
               };
void main() {
   port_b_pullups(TRUE);
   output_d(0);
   
   while (true) {
      if (conta <= 16) {
         digito1 = conta / 10;
         digito2 = conta % 10;
         
         output_d(digito[digito1]);
         output_a(0b00010000);
         output_d(digito[digito2]);
         output_a(0b00100000);
         
         delay_ms(1000);
         conta++;
      }
   }
}
