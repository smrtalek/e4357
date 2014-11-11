#include "mbed.h"

/* Program Example 14.3: Uses digital input and output using control registers, and
flashes an LED. LEDS connect to mbed pins 25 and 26. Switch input to pin 9.
*/
// function prototypes
void delay(void);
//Define Digital I/O registers

/*
typedef union {
    struct {
      unsigned int b0: 1;
      unsigned int b1: 1;
      unsigned int b2: 1;
      unsigned int b3: 1;
      unsigned int b4: 1;
      unsigned int b5: 1;
      unsigned int b6: 1;
      unsigned int b7: 1;
   };
   unsigned char byte; 
} byte_bits;
*/

#define FIO_0_DIR_0_ADDR ((unsigned char *)0x2009C000) // PORT0 byte 0
#define FIO_0_PIN_0_ADDR ((unsigned char *)0x2009C014) // 8bit REG0

#define FIO_1_DIR_0_ADDR ((unsigned char *)0x2009C020) // PORT0 byte 0
#define FIO_1_PIN_3_ADDR ((unsigned char *)0x2009C036) // 8bit REG0

#define FIO_2_DIR_0_ADDR ((unsigned char *)0x2009C040) //PORT2 byte 0
#define FIO_2_PIN_0_ADDR ((unsigned char *)0x2009C054) // 8bit REG0

volatile unsigned char *port0 = FIO_0_DIR_0_ADDR;
volatile unsigned char *port1 = FIO_1_DIR_0_ADDR;
volatile unsigned char *port2 = FIO_2_DIR_0_ADDR;

volatile unsigned char *port0pin0 = FIO_0_PIN_0_ADDR;
volatile unsigned char *port1pin3 = FIO_1_PIN_3_ADDR;
volatile unsigned char *port2pin0 = FIO_2_PIN_0_ADDR;

DigitalOut led1(LED1);

void delay(void) {
    for (int j = 0; j < 1000000; j++) {
        j++;
        j--; //waste time
    }
}

int main() {
    char a, b, i;
    *port0 = 0x00; // set all bits of port 0 byte 0 to input
    *port1 = 0xFF;
    *port2 = 0xFF; // set all bits of port 2 byte 0 to output
    while(1) {
        if (*port0pin0 & 0x01 == 0x01){ // bit test port 0 pin 0 (mbed pin 9)
            a = 0x01; // this reverses the order of LED flashing (change mbded pin26)
            b = 0x02; // based on the switch position (change mbed pin25 - binks more)
            //*port2pin0 = 0x01;
        } else {
            a = 0x02; // change pin25
            b = 0x01; // change pin26 (blinks more)
            //*port2pin0 = 0x00;
        }

        if (*port0pin0 & 0x01 == 0x01)
            led1 = 1;
        else
            led1 = 0;

        *port2pin0 |= a;
        delay();
        *port2pin0 &= ~a;
        delay();
        for (i = 0; i < 10; i++) {
            *port2pin0 |= b;
            delay();
            *port2pin0 &= ~b;
            delay();
        }
    } //end while loop
}
