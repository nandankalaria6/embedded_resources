#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "dh11.h" 
/*pd2 = data
pullup resistor b/w data and vcc 
*/

uint8_t read_bit(void)
{
    int ret;
    while(!(PIND & (1<<PD2)));// wait for 50us LOW period to end
    _delay_us(40);// middle of high pulse
    if(PIND & (1<<PD2)) ret= 1;
    else ret =0;
    if(PIND & (1<<PD2)) while((PIND & (1<<PD2)));
    return ret;
    // data 0 is low for 50u, high for 26u
    //data 1 is low for 50u, high for 70u
    // agar 50u e low atle 26u pura ane 0 che, neter 1
}
uint8_t read_byte(void)
{
    uint8_t data = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        data <<= 1;
        data |= read_bit();
    }
    return data;
}

bool read_dh11(uint8_t* humidity_int,uint8_t* humidity_dec,uint8_t* temp_int, uint8_t* temp_dec,uint8_t* checksum )
{
    DDRD |= (1<< PD2); // output
    PORTD &= ~(1<< PD2);// line pulled 0 for 20ms
    _delay_ms(20);

    PORTD |= (1<<PD2);// pullup high(not required as did pullup with tesistor)
    DDRD &= ~(1<<PD2); // data lne to input

    while(PIND & (1<<PD2));// after 20ms high dh11 goe 80us high
    while(!(PIND & (1<<PD2)));// then 80us low
    while(PIND & (1<<PD2));

    *humidity_int = read_byte();
    *humidity_dec = read_byte();

    *temp_int = read_byte();
    *temp_dec = read_byte();

    *checksum = read_byte();
    bool done;
    if(*checksum== *humidity_int + *humidity_dec + *temp_int + *temp_dec) done=true;
    else done =false;
    return done;
}
