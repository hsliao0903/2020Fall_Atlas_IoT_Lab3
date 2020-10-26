/*****************************************************
    LightSensor.cpp
    Bit-thing: Light Sensor
    Service: Detect if the light is bright enough in an anmount of time
    Input: Seconds (Integer)
    Output: 1 for no light detected, 0 for light detected

    Light Sensor Output: 
        LOW for detecting the light is brighter than default brightness, otherwise, HIGH

    TODO: After receiving a ADC, could have add another service for setting the light brightness
*****************************************************/

#include <ctime>
#include <wiringPi.h>
#include <string>
using namespace std;

// Sensor pin 
#define SENSOR_PIN   27

// detect if the any light is captured by the sensor in a period of time (sec)
int detect_light_for_time_period (int time){
	struct timespec ts;
	clock_t start, end;
	int duration;

    clock_gettime( CLOCK_MONOTONIC, &ts );
    start = (uint64_t)ts.tv_sec;

	while (true){
        clock_gettime( CLOCK_MONOTONIC, &ts );
        end = (uint64_t)ts.tv_sec;

		if (digitalRead(SENSOR_PIN) == LOW){
			return 0;
		}

		duration = end - start;

		if (duration >= time)
			return 1;
	}
}


int main(void) {

	wiringPiSetupGpio();
	pinMode(SENSOR_PIN, INPUT);

	int input, ret;
	
	
    printf("Bit-Thing: Light Sensor \n");
    printf("Service: Detect if the light is bright enough in an anmount of time\n");
    printf("How long you want to detect the light: ");
    while (scanf("%d", &input) == 1) {

        if (input < 0){
            printf("The time period could only be positive integer! (seconds)\n");
            continue;
        }

        printf("Start detecting the light in %d seconds...\n", input);

        ret = detect_light_for_time_period(input);
        if (!ret)
            printf("\nLight detected! Output: %d\n\n", ret);
        else
            printf("\nLight NOT detected! Output: %d\n\n", ret);
        
        
        
        printf("Please enter another input: ");
    }

	return 0;
}
