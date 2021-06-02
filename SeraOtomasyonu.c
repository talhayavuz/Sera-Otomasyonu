#include <16F877A.h>
#device ADC=10
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay(clock = 4000000)
#use fast_io(a)
#define use_portb_lcd TRUE
#include <lcd.c>

#define ENTER PIN_C3
#define ASAGI  PIN_C1
#define YUKARI  PIN_C0
#define ESC  PIN_C2

int8 referans=70,menu_say=0;
unsigned long int bilgi;
float nem;

void nem_oku () 
{
set_adc_channel(0);
   
    delay_us(20);
    
    bilgi=read_adc();
    nem=bilgi/7.13;

}

void eprom_oku ()
{
referans=read_eeprom(0);
}


void main () 
{

 setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_a(0x01);
   set_tris_d(0); // RD portu çýkýþ olarak yönlendirildi
   output_d(0); // RD portunun tüm çýkýþlarý sýfýrlandý
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0);
   lcd_init();



while (1) {

while (2) {
bas:
switch(menu_say)
         {
            case 0:
               lcd_gotoxy(1,1);
               printf(lcd_putc,">1-Baslat ");
               lcd_gotoxy(1,2);
               printf(lcd_putc," 2-Ayarlar");
               if (input(ENTER)){
               while ((input(ENTER)))
    {
    }
               printf(lcd_putc,"\f"); goto sulama;} //set menüye git
               break;
            case 1:
               lcd_gotoxy(1,1);
               printf(lcd_putc," 1-Baslat ");
               lcd_gotoxy(1,2);
               printf(lcd_putc,">2-Ayarlar");
               if (input(ENTER)) {
               while ((input(ENTER)))
    {
    }
               printf(lcd_putc,"\f"); goto ayarlar;} //set menüye git
               break;
         
}



if(input(ASAGI)&&(menu_say<1))
         {
             while(input(ASAGI));
             ++menu_say;
             //if(menu_say==5)
              // menu_say=0;
               }
          else if(input(YUKARI)&&(menu_say>0))     
               {
             while(input(YUKARI));
             --menu_say;
             //if(menu_say==0)
             //  menu_say=0;
               }


}

while (3) 
{
sulama:
nem_oku();
eprom_oku();
LCD_gotoxy(1,1); 
   printf(lcd_putc,"NEM=%%%f",nem);
    if(nem < referans){
    
         lcd_putc("\nSULAMA YAPILIYOR");
         output_high(pin_D0);
    
    }
    else{
   
     lcd_putc("\n IDEAL NEM ORANI");
    output_low(pin_D0);
    
    }
    
     if(input(ESC))
    {
    while ((input(ESC)))
    {
    }
  output_low(pin_D0); printf(lcd_putc,"\f"); goto bas;
    } 
      }
    

while (4) 
{
               ayarlar:
               lcd_gotoxy(1,1);
               printf(lcd_putc," NEM SINIRI  ");
               lcd_gotoxy(1,2);
               printf(lcd_putc," SET :%2d",referans);
               if(input(ENTER)) {write_eeprom (0,referans);} 
              if(input(ASAGI)&&(referans>0))
              {
              while(input(ASAGI));
              --referans;
               }
             else if(input(YUKARI)&&(referans<100))     
               {
             while(input(YUKARI));
             ++referans;
               }


             if(input(ESC))
    {
    while ((input(ESC)))
    {
    }
   printf(lcd_putc,"\f"); goto bas;
    }
}













}
}
