#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>

#include "joystick.h"

#define JOY_DEV		 "/dev/rfcomm0"

struct joy_event{
	char cmd[4];
};

int main()
{
	int fd, keyCode;
	struct joy_event ie;

	if( ( fd = open(JOY_DEV, O_RDWR) ) == -1 ) {
		perror("opening device");
		exit(EXIT_FAILURE);
	}

	while( read(fd, &ie, sizeof(struct joy_event)) ) {
		if(ie.cmd[0] == 48 & ie.cmd[3] == 48)
			if(ie.cmd[1] + ie.cmd[2] == 255){
				#ifdef DEBUG
				printf("cmd[0] = %d, cmd[1] = %d, cmd[3] = %d direction : ",
						ie.cmd[0], ie.cmd[1], ie.cmd[3]);
				#endif
				switch(ie.cmd[1]){
					case 2: callAD(); break;
					case 4: callICM();  break;
					case 5: printf("NATURAL\n"); break;
					case 6: printf("RIGHT\n"); break;
					case 8: printf("UP\n"); break;
					default: printf("UNKNOWN\n"); break;
				}
			}
		
	}

	return 0;
}
