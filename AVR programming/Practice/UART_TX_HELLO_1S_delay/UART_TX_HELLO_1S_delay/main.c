/*
 * UART_TX_HELLO_1S_delay.c
 *
 * Created: 11-01-2026 12:30:46
 * Author : User
 */ 
 #define F_CPU 16000000UL
 #include <avr/io.h>
 #include <util/delay.h>


 int main(void)
 {
	 
	 char fine[6]={'H','e','l','l','o','\0'}; // load a string
	 
	 UBRR0H=0; // Configure baud rate
	 UBRR0L=103;
	 
	 UCSR0C&=~(1<<UPM01)|(1<<UPM00)|(1<<USBS0); // No parity and 1 stop bit
	 
	 UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01); // Select 8 bit mode
	 
	 UCSR0B|=(1<<TXEN0); // Transmitter enable
	 
	 while (1)
	 {
		 for (int i=0; i<=4; i++)
		 {
			 UDR0=fine[i];                     // loading string into UDR0
			 while(!(UCSR0A & (1<<UDRE0)));    // wait until UDR0 empty
			 _delay_ms(1000);
		 }
		 
		 while(!(UCSR0A & (1<<UDRE0)));
		 UDR0='\n';  // for new line
		 _delay_ms(1000);
			 
	 }
 }

