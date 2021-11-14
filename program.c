#include <mega32.h>
#include <delay.h>
#include <stdlib.h>

// Alphanumeric LCD functions
#include <alcd.h>
int posisi, key;
long int operand1 = 0 , operand2 = 0, operator = 0;
float hasil = 0 ;
char bufferLCD[32] ;

int bacaKeyPad(){
    while(1){ 
        PORTB = 0b11111110;
        if(PINB.4 == 0)
            return 7;
        if(PINB.5 == 0)
            return 8;
        if(PINB.6 == 0)
            return 9;
        if(PINB.7 == 0)
            return 10; // :
//==========================================
        PORTB = 0b11111101;
        if(PINB.4 == 0)
            return 4;
        if(PINB.5 == 0)
            return 5;
        if(PINB.6 == 0)
            return 6;
        if(PINB.7 == 0)
            return 11; // x
//==========================================
        PORTB = 0b11111011;
        if(PINB.4 == 0)
            return 1;
        if(PINB.5 == 0)
            return 2;
        if(PINB.6 == 0)
            return 3;
        if(PINB.7 == 0)
            return 12; // -
//==========================================
        PORTB = 0b11110111;
        if(PINB.4 == 0)
            return 15; // Clear
        if(PINB.5 == 0)
            return 0;
        if(PINB.6 == 0)
            return 14; // =
        if(PINB.7 == 0)
            return 13; // +
    }
}


// Declare your global variables here

void main(void)
{
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0xF0;
DDRB=0x0F;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0xFF;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 16
lcd_init(16);
posisi = 1;
lcd_gotoxy(0,0);

while (1)
      {
      key = bacaKeyPad();         //baca Keypad
            if(key == 15){              //Jika tombol clear ditekan
                lcd_clear();
                lcd_gotoxy(0,0);
                operand1 = 0;
                operand2 = 0;
                operator = 0;
                hasil = 0; 
                posisi = 1;
            }
            else if(key >= 0 && key <=9){   //jika angka yang ditekan
                if(posisi == 1){            //jika masih input angka pertama
                    operand1 = (operand1*10)+ key ;          // operand 1 didapat dari nilai operand sebelumnya * 10 + angka yg diinput. dikali 10 agar yg awalnya satuan jadi puluhan, puluhan jadi ratusan, dsb
                    itoa(key, bufferLCD);                    // mengubah int ke string
                    lcd_puts(bufferLCD);                     
                }
                else if(posisi == 2){       //jika input angka ke 2
                    operand2 = (operand2*10)+ key ;
                    itoa(key, bufferLCD);                    
                    lcd_puts(bufferLCD);                      
                }                      
            }
            else if(key>=10 && key <=13){   //jika operator yg ditekan 
                if(key == 10)lcd_putchar('/') ;
                if(key == 11)lcd_putchar('X') ;
                if(key == 12)lcd_putchar('-') ;
                if(key == 13)lcd_putchar('+') ;   
                operator = key;                   //simpan operator yg ditekan
                posisi = 2;                       //ketika sudah menekan operator berarti inputan beralih ke operand2
            }
            else if(key == 14){                   //jika sama dengan yg ditekan maka diproses
                lcd_putchar('=');
                if(operator == 10) // jika ditekan '/'
                    hasil = operand1 / operand2 ;
                if(operator == 11) // jika ditekan 'X'
                    hasil = operand1 * operand2 ;
                if(operator == 12) // jika ditekan '-'
                    hasil = operand1 - operand2 ;
                if(operator == 13) // jika ditekan '+'
                    hasil = operand1 + operand2 ;
                ftoa(hasil,1,  bufferLCD);      //mengubah float ke string
                lcd_puts(bufferLCD);
            }
            delay_ms(50); 
      } 

}
