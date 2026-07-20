#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#define BCD_PORT PORTD
#define BCD_DDR  DDRD
#define A PD2
#define B PD3
#define C PD4
#define D PD5

#define DIGIT_PORTD PORTD
#define DIGIT_DDRD DDRD
#define H1 PD6
#define H2 PD7

#define DIGIT_PORTB PORTB
#define DIGIT_DDRB DDRB
#define M1 PB0
#define M2 PB1
#define S1 PB2
#define S2 PB3

volatile uint8_t hours = 12;
volatile uint8_t minutes = 0;
volatile uint8_t seconds = 0;

static inline void all_digits_off(void)
{
    DIGIT_PORTD &= ~((1<<H1)|(1<<H2));
    DIGIT_PORTB &= ~((1<<M1)|(1<<M2)|(1<<S1)|(1<<S2));
}

static inline void bcd_out(uint8_t n)
{
    BCD_PORT &= ~((1<<A)|(1<<B)|(1<<C)|(1<<D));
    BCD_PORT |= (n & 0x0F) << 2;
}

static inline void show(uint8_t digit, uint8_t port, uint8_t pin)
{
    all_digits_off();
    bcd_out(digit);

    if(port==0)
        DIGIT_PORTD |= (1<<pin);
    else
        DIGIT_PORTB |= (1<<pin);

    _delay_ms(1);
}

void display_time(void)
{
    show(hours/10,0,H1);
    show(hours%10,0,H2);
    show(minutes/10,1,M1);
    show(minutes%10,1,M2);
    show(seconds/10,1,S1);
    show(seconds%10,1,S2);
}

ISR(TIMER1_COMPA_vect)
{
    seconds++;

    if(seconds>=60)
    {
        seconds=0;
        minutes++;

        if(minutes>=60)
        {
            minutes=0;
            hours++;

            if(hours>=24)
                hours=0;
        }
    }
}

void timer1_init(void)
{
    TCCR1A=0;
    TCCR1B=0;
    TCNT1=0;

    OCR1A=15624;

    TCCR1B |= (1<<WGM12);
    TCCR1B |= (1<<CS12)|(1<<CS10);

    TIMSK1 |= (1<<OCIE1A);

    sei();
}

int main(void)
{
    BCD_DDR |= (1<<A)|(1<<B)|(1<<C)|(1<<D);

    DIGIT_DDRD |= (1<<H1)|(1<<H2);
    DIGIT_DDRB |= (1<<M1)|(1<<M2)|(1<<S1)|(1<<S2);

    all_digits_off();

    timer1_init();

    while(1)
    {
        display_time();
    }
}
