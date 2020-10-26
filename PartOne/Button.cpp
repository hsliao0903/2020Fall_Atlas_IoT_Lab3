/*****************************************************
    Button.cpp
    Bit-thing: Button
    Service: Detect a button press in an amount of seconds
    Input: Seconds (Integer)
    Output: 1 for button not pressed, 0 for button pressed
*****************************************************/

#include <ctime>
#include <string>
#include <wiringPi.h>
using namespace std;

// Sensor pin 
#define BTN_PIN   23

// detect if the button is pressed in a period of time (sec)
int detect_button_pressed_for_time_period (int time){
    struct timespec ts;
	clock_t start, end;
	int duration;

    clock_gettime( CLOCK_MONOTONIC, &ts );
    start = (uint64_t)ts.tv_sec;

	while (true){
        clock_gettime( CLOCK_MONOTONIC, &ts );
        end = (uint64_t)ts.tv_sec;

		if (digitalRead(BTN_PIN) == HIGH){
			return 0;
		}

		duration = end - start;

		if (duration >= time)
			return 1;
	}
}


int main(void) {

	wiringPiSetupGpio();
	pinMode(BTN_PIN, INPUT);

	int input, ret;
	
	
    printf("Bit-Thing: Button \n");
    printf("Service: Detect a button press in an amount of seconds\n");
    printf("How long you want to detect a button press: ");
    while (scanf("%d", &input) == 1) {

        if (input < 0){
            printf("The time period could only be positive integer! (seconds)\n");
            continue;
        }

        printf("Start detecting a button press in %d seconds...\n", input);

        ret = detect_button_pressed_for_time_period(input);
        if (!ret)
            printf("\nButton pressed! Output: %d\n\n", ret);
        else
            printf("\nButton NOT pressed! Output: %d\n\n", ret);
        
        
        
        printf("Please enter another input: ");
    }

	return 0;
}
