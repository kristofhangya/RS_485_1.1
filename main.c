#define F_CPU 8000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <avr/iom128.h>
#include <util/delay.h>
#include "FIFO.h"
#include <avr/interrupt.h>
#include "USART.h"

uint8_t sent_commands();

int main(){

    USART_Init(MYUBRR);
    RS_drivebus();
    uint8_t tmp;
    sei();

    DDRB = 0xf0;

    while(1){
        /*
        if(tmp = USART_Receive()){
            PORTB = tmp & 0xf0;
        }*/

        for(tmp=0x10; tmp<0xf0; tmp ++){
            USART_Transmit(tmp);
            _delay_ms(5);
        }

    }

    return 0;
}




