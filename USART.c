#include "USART.h"
#include <avr/interrupt.h>
#include "FIFO.h"

static FIFO recieve, transmit;
static uint8_t r[recive_buffer_size],t[transmit_buffer_size];

void USART_Init( unsigned int ubrr )
{
    UART1_DDR |= (1<<UART1_TX);
    UART1_DDR &= (1<<UART1_RX);

    RS_RE_DDR |= (1<<RS_RE_PIN);
    RS_DE_DDR |= (1<<RS_DE_PIN);
    RS_releasebus();

    UBRR1H = 0;
    UBRR1L = 8;

    UCSR1A = 0;
    UCSR1B = ((1<<RXEN)|(1<<TXEN)|(1<<RXCIE1));
    UCSR1C = ((1<<USBS1)|(1<<UCSZ10)|(1<<UCSZ11));

    fifo_init(&recieve,r,recive_buffer_size);
    fifo_init(&transmit,t,transmit_buffer_size);
}

void USART_Transmit( unsigned char data ){
    fifo_send(&transmit,data);
    UCSR1B |= (1 << UDRIE1);
}
unsigned char USART_Receive( void ){
   return fifo_receive(&recieve);
}

ISR(USART1_RX_vect){
    fifo_send(&recieve,UDR1);
}

ISR(USART1_UDRE_vect){
    if(!transmit.fifo_elements){ //tilt
        UCSR1B &= ~(1 << UDRIE1);
    }else{
        UDR1 = fifo_receive(&transmit);
    }
}

void RS_drivebus(/* arguments */) {
  RS_RE_PORT |= (1<<RS_RE_PIN);
  RS_DE_PORT |= (1<<RS_DE_PIN);

}

void RS_releasebus(/* arguments */) {
  RS_DE_PORT  &= ~(1<<RS_RE_PIN);
  RS_DE_PORT  &= ~(1<<RS_DE_PIN);

  /* code */
}
