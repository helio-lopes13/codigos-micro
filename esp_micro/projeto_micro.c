#include <18F4550.h>
#define botao0 pin_b0
#define botao1 pin_b1
#define bit_lampada pin_d0
#device adc=10
#use delay (clock=20000000)
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1
#use rs232(baud=9600, xmit = PIN_C6, rcv = PIN_C7)

float ad;
unsigned int32 ad0, b0 = 0, b1 = 0, n = 0;
boolean led = true, verifica_ad = false, botoes_pressionados = false;
char caractere;

void processa_caractere(char caractere) {
   if (caractere == 'L') {
      output_high(bit_lampada);
   }
   if (caractere == 'D') {
      output_low(bit_lampada);
   }
}

#int_timer0
void trata_t0() {
   SET_TIMER0(200+get_timer0());
   
   n++;
   set_adc_channel(0);
   ad = read_adc();
   delay_us(10);
   ad0 = ad * 100.0 / 1023;
   
   if (ad0 > 50) {
      verifica_ad = true;
      output_high(pin_d3);
   } else {
      output_low(pin_d3);
   }
   
   b0 = input(botao0);
   b1 = input(botao1);
   
   if (b0 == 0 && b1 == 0) {
      botoes_pressionados = true;
   }
   
   if (verifica_ad && botoes_pressionados) {
      do {
         caractere = getc();
      } while ((caractere != 'L') && (caractere != 'D'));
      
      processa_caractere(caractere);
   }
   
   if (n == 2500) {
      n = 0;
      led = !led;
      output_bit(pin_d1, led);
   }
}

void main() {
   SET_TRIS_B(0xFF);
   SET_TRIS_D(0x00);
   port_b_pullups(TRUE);
   ENABLE_INTERRUPTS(GLOBAL|INT_TIMER0);
   SETUP_TIMER_0(RTCC_INTERNAL | RTCC_DIV_2 | RTCC_8_BIT);
   setup_adc_ports(an0_to_an1);
   setup_adc(adc_clock_internal);
   SET_TIMER0(200);
   while(true) { }
}
