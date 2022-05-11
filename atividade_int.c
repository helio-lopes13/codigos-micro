#define led1 pin_d1
#include <18F4550.h>
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1, PLL5,USBDIV 
#use delay(clock=20000000)

/**
O valor em set_timer foi calculado usando a seguinte fórmula:
set_timer0 = 65536 - (50000 / (12 * PS))
em que PS é o prescaler escolhido, no caso abaixo PS = 8.

O valor encontrado foi então ajustado para que a frequência avaliada
na placa real fosse o mais próximo o bastante do pedido
*/
#int_timer0
void funcao_tempo() {
   static boolean flag;
   static unsigned int32 n;
   set_timer0(13470+get_timer0());
   n++;
   if (n == 1) {
      n = 0;
      flag = !flag;
      output_bit(led1,flag);
   }
}

void main() {
   setup_timer_0 (RTCC_DIV_8 | RTCC_INTERNAL); //16 bits
   set_timer0(13470);                                             
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER0);
   while(true) {}
}
