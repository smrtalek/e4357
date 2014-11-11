/*Program Example 7.9: Sets the mbed up for async communication, and exchanges data with
a similar node, sending its own switch positions, and displaying those of the other.
*/

#include "mbed.h"

//Serial async_port(p9, p10); //set up TX and RX on pins 9 and 10
Serial pc(USBTX, USBRX); //tx, rx

DigitalOut red_led(p25); //red led
DigitalOut green_led(p26); //green led
DigitalOut strobe(p7); //a strobe to trigger the scope

DigitalIn switch_ip1(p5);
DigitalIn switch_ip2(p6);

char switch_word ; //the word we will send
char recd_val; //the received value

int main() {
    //async_port.baud(9600); //set baud rate to 9600 (ie default)
    //accept default format, of 8 bits, no parity
    while (1) {
        //Set up the word to be sent, by testing switch inputs
        //switch_word=0xa0; //set up a recognizable output pattern
        //if (switch_ip1 == 1)
        //    switch_word = switch_word | 0x01; //OR in lsb
        //if (switch_ip2 == 1)
        //    switch_word = switch_word | 0x02; //OR in next lsb
        //strobe = 1; //short strobe pulse
        //wait_us(10);
        //strobe = 0;
        //async_port.putc(switch_word); //transmit switch_word
        if (pc.readable() == 1) //is there a character to be read?
            recd_val = pc.getc(); //if yes, then read it
        recd_val= recd_val & 0x0F; //AND out unwanted bit
        if (recd_val == 1)
            red_led = 1;
        if (recd_val == 2)
            green_led = 1;
        if (recd_val == 3){
            red_led = 1;
            green_led = 1;
        }
        if (recd_val == 4){
            red_led = 0;
            green_led = 0;
        }
    }
}