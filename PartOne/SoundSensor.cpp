/*****************************************************
    SoundSensor.cpp
    Bit-thing: Sound Sensor
    Service: Detect if a sound is loud enough in an anmount of time
    Input: Seconds (Integer)
    Output: 1 for no sound detected, 0 for sound detected

    Sound Sensor Output: 
        HIGH for detecting a sound that is louder than default loudness, otherwise, LOW

    TODO: After receiving a ADC, could have add another service for setting the sound loudness
*****************************************************/

#include <ctime>
#include <wiringPi.h>
#include <string>
using namespace std;

// Sensor pin 
#define SND_PIN   24

// detect if the any sound is captured by the sensor in a period of time (sec)
int detect_sound_for_time_period (int time){
struct timespec ts;
	clock_t start, end;
	int duration;

    clock_gettime( CLOCK_MONOTONIC, &ts );
    start = (uint64_t)ts.tv_sec;

	while (true){
        clock_gettime( CLOCK_MONOTONIC, &ts );
        end = (uint64_t)ts.tv_sec;

		if (digitalRead(SND_PIN) == HIGH){
			return 0;
		}

		duration = end - start;

		if (duration >= time)
			return 1;
	}
}


int main(void) {

	wiringPiSetupGpio();
	pinMode(SND_PIN, INPUT);

	int input, ret;
	
	
    printf("Bit-Thing: Sound Sensor \n");
    printf("Service: Detect if a sound is loud enough in an anmount of time\n");
    printf("How long you want to detect a loud sound: ");
    while (scanf("%d", &input) == 1) {

        if (input < 0){
            printf("The time period could only be positive integer! (seconds)\n");
            continue;
        }

        printf("Start detecting a loud sound in %d seconds...\n", input);

        ret = detect_sound_for_time_period(input);
        if (!ret)
            printf("\nSound detected! Output: %d\n\n", ret);
        else
            printf("\nSound NOT detected! Output: %d\n\n", ret);
        
        
        
        printf("Please enter another input: ");
    }

	return 0;
}
