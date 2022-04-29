/*
PROGRAMA SIMULAÇÂO DE DISPLAY DE 7 SEGMENTOS PLACA PICGÊNIOS
AUTOR PROF. FÁBIO TIMBÓ
*/
#include<18F4550.h>
#use delay (clock=20000000)        
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 

int conta = 0;
int digito1, digito2, i;

/*Matriz de 10 posições contendo o valor a ser enviado para a porta D a fim de
   mostrar o dígito referente nos displays */
int digito[10] =
               {0b00111111,    //Dígito 0
                0b00000110,    //Dígito 1
                0b01011011,    //Dígito 2
                0b01001111,    //Dígito 3
                0b01100110,    //Dígito 4
                0b01101101,    //Dígito 5
                0b01111101,    //Dígito 6
                0b00000111,    //Dígito 7
                0b01111111,    //Dígito 8
                0b01101111     //Dígito 9
               };
void main() {
   port_b_pullups(TRUE);
   output_a(0);
   output_d(0);
   output_b(0xFF);
   
   while (true) {
      if (input(pin_b0) == 0) {
         while (conta <= 16) {
            digito1 = conta / 10;
            digito2 = conta % 10;
            
            for (i = 1; i <= 50; i++) {
               output_d(digito[digito1]);
               output_a(0b00010000);
               delay_ms(10);
               output_d(digito[digito2]);
               output_a(0b00100000);
               delay_ms(10);
            }
   
            conta++;
         }
         
         output_d(0);
         output_a(0);
         conta = 0;
      }   
   }
}
