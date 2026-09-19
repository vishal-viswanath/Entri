/*
 * Distance_measurement.c
 *
 * Created: 19-09-2026 11:30:27
 * Author : User
 */ 

/*
 * Ultrasonic Distance Controlled Servo
 * Arduino UNO - Register Level Programming
 *
 * TRIG  -> D6 (PD6)
 * ECHO  -> D7 (PD7)
 * SERVO -> D10 (PB2 / OC1B)
 *
 * Distance: 5 cm to 40 cm
 * Servo angle: 0 degree to 180 degree
 */

#include <avr/io.h>

/* Function declarations */

void UART_Init(void);
void UART_SendChar(char data);
void UART_SendString(const char *str);
void UART_SendNumber(unsigned int num);

void Timer1_Init(void);
void Servo_SetAngle(unsigned int angle);

unsigned long getEchoTime(void);
unsigned int getDistance(void);

void delay_us(unsigned int us);
void delay_ms(unsigned int ms);


/* Main program */

int main(void)
{
    unsigned int distance;
    unsigned int angle;

    /* D6 -> TRIG as output */
    DDRD |= (1 << PD6);

    /* D7 -> ECHO as input */
    DDRD &= ~(1 << PD7);

    /* Initially keep TRIG LOW */
    PORTD &= ~(1 << PD6);

    UART_Init();
    Timer1_Init();

    UART_SendString("Ultrasonic Servo Control\r\n");

    while (1)
    {
        distance = getDistance();

        /*
         * If the distance is outside our required range,
         * keep it within 5 to 40 cm.
         */
        if (distance < 5)
        {
            distance = 5;
        }

        if (distance > 40)
        {
            distance = 40;
        }

        /*
         * Convert distance from 5-40 cm
         * into servo angle from 0-180 degrees.
         * angle = (distance - 5) * 180 / 35
         */
        angle = ((distance - 5) * 180) / 35;

        Servo_SetAngle(angle);

        UART_SendString("Distance: ");
        UART_SendNumber(distance);
        UART_SendString(" cm  Servo angle: ");
        UART_SendNumber(angle);
        UART_SendString(" degree\r\n");

        delay_ms(50);
    }
}


/* UART FUNCTIONS*/

void UART_Init(void)
{
    /*
     * Arduino UNO clock = 16 MHz
     * Baud rate = 9600
     * UBRR = F_CPU/(16*Baud)-1
     *      = 16,000,000/(16*9600)-1
     *      = 103
     */

    UBRR0H = 0;
    UBRR0L = 103;

    /* Enable transmitter */
    UCSR0B = (1 << TXEN0);

    /* 8-bit data, 1 stop bit, no parity */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}


void UART_SendChar(char data)
{
    /* Wait until transmit buffer is empty */
    while (!(UCSR0A & (1 << UDRE0)))
    {
        ;
    }

    UDR0 = data;
}


void UART_SendString(const char *str)
{
    while (*str)
    {
        UART_SendChar(*str);
        str++;
    }
}


void UART_SendNumber(unsigned int num)
{
    char buffer[6];
    int i = 0;

    if (num == 0)
    {
        UART_SendChar('0');
        return;
    }

    while (num > 0)
    {
        buffer[i] = (num % 10) + '0';
        num = num / 10;
        i++;
    }

    while (i > 0)
    {
        i--;
        UART_SendChar(buffer[i]);
    }
}


/* TIMER1 - SERVO PWM */

void Timer1_Init(void)
{
    /*
     * Servo signal is generated on OC1B = Arduino D10.
     * Fast PWM mode 14
     * TOP = ICR1
     * Prescaler = 8
     * Timer frequency:
     * 16 MHz / 8 = 2 MHz
     * One timer tick = 0.5 us
     * 20 ms period:
     * 20,000 / 0.5 = 40,000
     * Therefore:
     * ICR1 = 39999
     */

    /* D10 (PB2) as output */
    DDRB |= (1 << PB2);

    /* Fast PWM mode 14 */
    TCCR1A = (1 << COM1B1) | (1 << WGM11);

    TCCR1B = (1 << WGM13) |
             (1 << WGM12) |
             (1 << CS11);

    /* 20 ms PWM period */
    ICR1 = 39999;

    /* Start servo around 90 degrees */
    OCR1B = 3000;
}


void Servo_SetAngle(unsigned int angle)
{
    /*
     * Servo pulse:
     * 0 degree   -> approximately 1 ms
     * 180 degree -> approximately 2 ms
     * Timer tick = 0.5 us
     * 1 ms = 2000 ticks
     * 2 ms = 4000 ticks
     */

    if (angle > 180)
    {
        angle = 180;
    }

    OCR1B = 2000 + ((unsigned long)angle * 2000) / 180;
}


/* ULTRASONIC SENSOR */

unsigned long getEchoTime(void)
{
    unsigned long count = 0;

    /* Make sure TRIG is LOW */
    PORTD &= ~(1 << PD6);
    delay_us(2);

    /* Send 10 us trigger pulse */
    PORTD |= (1 << PD6);
    delay_us(10);
    PORTD &= ~(1 << PD6);

    /*
     * Wait until ECHO becomes HIGH.
     */
    count = 0;

    while (!(PIND & (1 << PD7)))
    {
        delay_us(1);

        count++;

        /*
         * Timeout to prevent the program
         * from getting stuck.
         */
        if (count > 30000)
        {
            return 0;
        }
    }

    /*
     * Measure how long ECHO stays HIGH.
     */
    count = 0;

    while (PIND & (1 << PD7))
    {
        delay_us(1);

        count++;

        if (count > 30000)
        {
            return 0;
        }
    }

    return count;
}


unsigned int getDistance(void)
{
    unsigned long echoTime;
    unsigned int distance;

    echoTime = getEchoTime();

    if (echoTime == 0)
    {
        return 40;
    }

    /*
     * Speed of sound ? 0.034 cm/us
     * Distance = time × 0.034 / 2
     * Approximately:
     * Distance = time / 58
     */

    distance = echoTime / 58;

    return distance;
}


/* SIMPLE DELAY FUNCTIONS */

void delay_us(unsigned int us)
{
    unsigned int i;

    while (us--)
    {
        /*
         * Approximate delay for 16 MHz Arduino UNO.
         */
        for (i = 0; i < 4; i++)
        {
            __asm__ __volatile__("nop");
        }
    }
}


void delay_ms(unsigned int ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}
