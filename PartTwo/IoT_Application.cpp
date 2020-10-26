/*****************************************************
    IoT_Application.cpp
    This is a simple code for sending tweets to the Atlas server on my rawpberry pi.
	please set the SERVER_IP and SERVER_PORT below for connecting to another Atlas server.

	Usage: ./IoT_Application TweetType ThingID SpaceID ServiceName Input
    Output: response tweet from Atlas server

	There are four services for my Atlas IoT-DDL, and they all accept a positive integer as input,
	examples showing below:

	./IoT_Application Service MyRPI_5341 MySmartSpace RedLEDBlink 5
	./IoT_Application Service MyRPI_5341 MySmartSpace DetectButtonPress 5
	./IoT_Application Service MyRPI_5341 MySmartSpace DetectSound 5
	./IoT_Application Service MyRPI_5341 MySmartSpace DetectLight 5
*****************************************************/



#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
using namespace std;


#define SERVER_IP "192.168.3.55"
#define SERVER_PORT 6668

int main(int argc, char *argv[]) {
	char tweet[1024];
	char TweetType[32];
	char ThingID[32];
	char SpaceID[32];
	char ServiceName[32];
	char Inputs[32];

	if (argc != 6){
		printf("Wrong input arguments!\n");
		printf("\n\n ./IoT_Application TweetType ThingID SpaceID ServiceName Input\n\n");
		return 0;
	}

	// copy the arguments respectively
	strcpy(TweetType, argv[1]);
	strcpy(ThingID, argv[2]);
	strcpy(SpaceID, argv[3]);
	strcpy(ServiceName, argv[4]);
	strcpy(Inputs, argv[5]);
	
	// coposing the tweet of JSON form
	bzero(tweet, 1024);
	strcpy(tweet, "{\"Tweet Type\":\"");
	strcat(tweet, TweetType);
	strcat(tweet, "\",\"Thing ID\":\"");
	strcat(tweet, ThingID);
	strcat(tweet, "\",\"Space ID\":\"");
	strcat(tweet, SpaceID);
	strcat(tweet, "\",\"Service Name\":\"");
	strcat(tweet, ServiceName);
	strcat(tweet, "\",\"Service Inputs\":\"(");
	strcat(tweet, Inputs);
	strcat(tweet, ")\"}");
	printf("Input tweet: %s\n", tweet);
	

	// initial the server socket
	int serverSocket;
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// set socket address
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serv_addr.sin_port = htons(SERVER_PORT);

	// try to connect to server via socket
    int res = connect(serverSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   	if (res < 0)
		{ printf("Connecting to server failed!\n"); close(serverSocket); return 0; }

	printf("Send tweet to Atlas Server...\n");
	write(serverSocket, tweet, strlen(tweet));

	// try to get response from server
	char buffer[1024];
	bzero(buffer,1024);
	read(serverSocket, buffer, sizeof(buffer)-1);
	printf("Response tweet: %s\n", buffer);

	close(serverSocket);
	return 0;
}


/***  tweet for testing  ***/
char call1[] = " {\"Tweet Type\":\"Service call\",\"Thing ID\":\"MySmartThing01\",\"Space ID\":\"MySmartSpace\",\"Service Name\":\"Service4\",\"Service Inputs\":\"(5)\"}";
char call2[] = " {\"Tweet Type\":\"Service call\",\"Thing ID\":\"MySmartThing01\",\"Space ID\":\"MySmartSpace\",\"Service Name\":\"ServiceButton\",\"Service Inputs\":\"(5)\"}";
char call3[] = " {\"Tweet Type\":\"Service call\",\"Thing ID\":\"MyRPI_5341\", \
					\"Space ID\":\"MySmartSpace\",\"Service Name\":\"RedLEDBlink\",\"Service Inputs\":\"(5)\"}";
char call4[] = " {\"Tweet Type\":\"Service call\",\"Thing ID\":\"MyRPI_5341\", \
					\"Space ID\":\"MySmartSpace\",\"Service Name\":\"DetectButtonPress\",\"Service Inputs\":\"(5)\"}";
char call5[] = " {\"Tweet Type\":\"Service call\",\"Thing ID\":\"MyRPI_5341\", \
					\"Space ID\":\"MySmartSpace\",\"Service Name\":\"DetectSound\",\"Service Inputs\":\"(5)\"}";
char call6[] = " {\"Tweet Type\":\"Service call\",\"Thing ID\":\"MyRPI_5341\", \
					\"Space ID\":\"MySmartSpace\",\"Service Name\":\"DetectLight\",\"Service Inputs\":\"(5)\"}";