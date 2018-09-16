/*
    g++ -o client client.c
    ./client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#include<unistd.h>

#include <time.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
#define PORT_N 6000   //The port on which to send data


void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);

    // OPENING CONNECTION --------------

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT_N);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }


    // SENDING DATA -------------------
    FILE * file;
    file = fopen( argv[1] , "r");
    char str[100];

    float lat=0, lon=0, alt=0;
    float pitch=0, roll=0, yaw=0;
    int p=0,r=0,y=0;
    // skips first line
    fscanf(file, "%*[^\n]\n");

    while (fscanf(file, "%f;%f;%f;%f;%f;%f", &lat, &lon, &alt, &pitch, &roll, &yaw)!=EOF)
    {
        printf("PITCH     ROLL      YAW\n");
        printf("%f %f %f\n", pitch, roll, yaw);
        // Send attitude data
        memset(str, 0, sizeof(str));
        p = (int) pitch;
        r = (int) roll;
        y = (int) yaw;
        sprintf(str,"1 %d %d %d \n",p, r, y);
        //send the message
        if (sendto(s, str, strlen(str) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }


        //sleep
        usleep(100000);

    }


	memset(str, 0, sizeof(str));
	sprintf(str,"-1");
	if (sendto(s, str, strlen(str) , 0 , (struct sockaddr *) &si_other, slen)==-1)
	{
		die("sendto()");
	}

	close(s);
	return 0;
}
