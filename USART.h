#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

#define recive_buffer_size 128
#define transmit_buffer_size 128

#define UART1_DDR   DDRD
#define UART1_PORT  PORTD
#define UART1_TX    PD3
#define UART1_RX    PD2

#define RS_RE_DDR   DDRC
#define RS_RE_PORT  PORTC
#define RS_RE_PIN   PC7

#define RS_DE_DDR   DDRE
#define RS_DE_PORT  PORTE
#define RS_DE_PIN   PE2

void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );

#endif // USART_H_INCLUDED
