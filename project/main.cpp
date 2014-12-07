#include "mbed.h"
#include "ctype.h"
#include "stdlib.h"

PwmOut led1(LED1);
PwmOut led2(LED2);
PwmOut led3(LED3);
PwmOut led4(LED4);

Serial melody(p9,p10);
Serial pc(USBTX, USBRX);

void change_led_on(PwmOut *led, bool doWait = false) {
    for(float p = *led; p <= 1.0f; p += 0.1f) {
        *led = p;
        if (doWait)
            wait(0.1);
    }
}

void change_led_off(PwmOut *led, bool doWait = false) {
    for(float p = *led; p >= 0.0f; p -= 0.1f) {
        *led = p;
        if (doWait)
            wait(0.1);
    }
}

int pattern = -1;

void setPattern(Serial *srl) {
    char c = '$';
    if (srl->readable())
        c = srl->getc();
    else if(pc.readable())
        c = pc.getc();
    if (c == '$')
        return;
    if (isdigit(c))
        pattern = atoi(&c);
    else if (isalpha(c))
        pattern = ((int)c) - 54;
    else
        pattern = -1;
}


//BC127
#define SIZE 13
char UARTBuff[SIZE];
 
/* Responses from Melody, in order characters are stored in FIFO */
char SppConn[SIZE] = {'\r','\n','P','P','S',' ','K','O','_','N','E','P','O'};
char Ok[4] = {'\r','\n','K','O'};

int connected = 0;
int loopback = 0;

void RxParse(void)
{
    if(loopback)
        setPattern(&melody); 
    else {
        /* A character has been received and we are not in loopback.
           Starting to look for a SPP connection indication          */
 
        led1 = 1; //indicate we have started parsing
 
        /* Shifts characters in the FIFO buffer.
           Note: a circular buffer would have been much faster, however,
           we would not have been able to use memcmp() so it is a good
           trade-off in terms of speed.                                */
 
        for(int i = SIZE-2; i>0; i--) 
        {
            UARTBuff[i+1] = UARTBuff[i];
        }
        UARTBuff[1] = UARTBuff[0];
        UARTBuff[0] = melody.getc(); // store current character
 
        if(!connected) { // SPP connection has not been detected yet
            /* Check buffer for SPP connection indication */
            if(memcmp(&UARTBuff[0],&SppConn[0],SIZE)==0)
             {
                /* SPP connection detected */
                led2 = 1; // indicate to the world
                melody.printf("ENTER_DATA\r\n"); // Configure BC127
                connected = 1; // change internal state
 
                return;
            }
            return;
 
        }
        /* We are connected and waiting for a confirmation that our
           configuration has been accepted and the BC127 has entered
           DATA_MODE                                                  */
        else if(memcmp(&UARTBuff[0],&Ok[0],4) == 0) 
        {
            /* Success! We have configured the BC127 and we can now
               send some instruction to Bluetooth terminal via BC127 */
 
            led3 = 1; /* indicate state to the world */
   
            melody.printf(">> Type character(s):\r\n>> ");
            loopback = 1; // change internal state
 
            return;
        } 
    }
 
    return;
}
//END BC127

int main() {
    melody.attach(RxParse);
    while(1) {
                if (pattern == 0) {
                    change_led_off(&led4, true);
                    change_led_off(&led3, true);
                    change_led_off(&led2, true);
                    change_led_off(&led1, true);
                } else if (pattern == 1) {
                    change_led_on(&led1, true);
                    change_led_on(&led2, true);
                    change_led_on(&led3, true);
                    change_led_on(&led4, true);
                } else if (pattern == 2) {
                    led1 = led2 = led3 = led4 = 0;
                    change_led_on(&led1);
                    change_led_on(&led4);
                    wait(0.1);
                } else if (pattern == 3) {
                    led1 = led2 = led3 = led4 = 0;
                    change_led_on(&led2);
                    change_led_on(&led3);
                    wait(0.1);
                } else if (pattern == 4) {
                    change_led_on(&led2);
                    change_led_on(&led3);
                    change_led_off(&led1);
                    change_led_off(&led4);
                    wait(0.1);
                    change_led_on(&led1);
                    change_led_on(&led4);
                    change_led_off(&led2);
                    change_led_off(&led3);
                    wait(0.1);
                } else if (pattern == 11)
                    led1 = 0;
                else if (pattern == 12)
                    led2 = 0;
                else if (pattern == 13)
                    led3 = 0;
                else if (pattern == 14)
                    led4 = 0;
                else if (pattern == 43)
                    led1 = 1;
                else if (pattern == 44)
                    led2 = 1;
                else if (pattern == 45)
                    led3 = 1;
                else if (pattern == 46)
                    led4 = 1;
                else
                    led1 = led2 = led3 = led4 = 0;
    }
}
