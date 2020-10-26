/*****************************************************
    RedLED.cpp
    Bit-thing: Red LED
    Service: Blink the Red LED for an amount of times
    Input: Seconds (Integer)
    Output: None
*****************************************************/

#include <wiringPi.h>
#include <string>
using namespace std;

// LED pin 
#define LED_RED   17

// let the red led blink for x times
void red_led_blink(int times){
	
	for (int i = 0 ; i < times ; i++){
		digitalWrite(LED_RED,HIGH);
		delay(50);
		digitalWrite(LED_RED,LOW);
		
		if (times == i + 1)
			break;
		delay(500);
	}
	
}


int main(void) {

	wiringPiSetupGpio();
	pinMode(LED_RED, OUTPUT);

	int input;
	
	
    printf("Bit-Thing: Red LED \n");
    printf("Service: Blink the red LED for an amount of times\n");
    printf("How many times you want the Red LED to blink: ");
    while (scanf("%d", &input) == 1) {

        printf("\nBlink the red led %d times!\n\n", input);

        red_led_blink(input);

        printf("Please enter another input:");
    }

	return 0;
}
