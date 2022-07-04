#include <18F4550.h>
#define ventilador pin_c2
#define transmit pin_c6
#define receive pin_c7
#device adc=10
#use delay (clock=20000000)
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1
#use rs232(baud=9600, xmit = PIN_C6, rcv = PIN_C7)
float ad;
unsigned int32 ad0;

#int_timer0
void trata_t0() {
   static unsigned int32 n;
   
   SET_TIMER0(100+get_timer0());
   n = 0;
   set_adc_channel(0);
   ad = read_adc();
   delay_us(10);
   ad0 = ad * 100.0 / 1023;
   
   if () {
   }
   
   printf("Setpoint: %u\r\nValor: %u\r\n", ad0, ad1);
   output_bit(ventilador, (ad1 > ad0));
}

void main() {
   SET_TRIS_D(0x00);
   ENABLE_INTERRUPTS(GLOBAL|INT_TIMER0);
   SETUP_TIMER_0(RTCC_INTERNAL | RTCC_DIV_256 | RTCC_8_BIT);
   setup_adc_ports(an0_to_an1);
   setup_adc(adc_clock_internal);
   SET_TIMER0(100);
   while(true) { }
}
