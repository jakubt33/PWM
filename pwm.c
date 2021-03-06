#include <avr/io.h>
#define F_CPU 1000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED1 PB1
#define LED2 PB5
#define PWM PB3

void PWM_Init()
{
    TCCR2 |= (1<<WGM21)|(1<<WGM20)|(1<<COM21)|(0<<COM20)|(1<<CS20); //wlaczenie fast pwm, non inverting mode pomiedzy 0 a OCR2 sygnal 0, preskaler 0
    //TIMSK |= (1<<TOIE2)|(1<<OCIE2);

}

int main()
{
    PWM_Init();

    DDRB |= _BV(PWM); //tu jest PWM na timerze 2
    DDRB |= _BV(LED2); //wyjscie na leda
    DDRB |= _BV(LED1);

    sei();
    int licznik=0;

    while(1)
    {
        PORTB &= ~_BV(LED2);
        for(licznik=0;licznik<256;licznik++)
        {
            OCR2 = licznik;
            _delay_ms(32);
        }
        _delay_ms(500);
        OCR2 = 0;
        PORTB |= _BV(LED2);
        _delay_ms(500);

    }

}
