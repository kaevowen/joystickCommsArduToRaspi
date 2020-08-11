#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>

#define JOY_DEV		 "/dev/rfcomm0"

struct joy_event{
	char cmd[5];
};

int main()
{
	int fd;
	struct joy_event ie;

	printf("attempt bluetooth connect...\n");

	if( ( fd = open(JOY_DEV, O_RDWR) ) == -1 ) {
		perror("opening device");
		exit(EXIT_FAILURE);
	} 
	
	printf("----- Command List -----\n");
	printf("UP      : SHTC3\n");
	printf("DOWN    : AD1015\n");
	printf("NATURAL : NOTHING\n");
	printf("LEFT    : ICM20948\n");
	printf("RIGHT   : LPS22HB\n"); 
	printf("PUSH    : TCS34725\n");

	while( read(fd, &ie, sizeof(struct joy_event)) ) {
		#ifdef DEBUG
			printf("cmd[0] = %d, cmd[1] = %d, cmd[3] = %d\n",
					ie.cmd[0], ie.cmd[1], ie.cmd[3]);
		#endif

		if(ie.cmd[0] == 70 && ie.cmd[4] == 48)
			if(ie.cmd[1] + ie.cmd[2] == 255){
			
				switch(ie.cmd[1]){
					case  2: callAD(); break;
					case  4: callICM();  break;
					case  5: break;
					case  6: callLPS(); break;
					case  8: callSHTC3(); break;
					case 99: callTCS(); break;
					default: printf("UNKNOWN\n"); break;
				}
			}
		
	}

	return 0;
}
