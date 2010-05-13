#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "aic14_ioctl.h"

#define MAXLEVEL 255
#define AIC14_DEV "/dev/aic14"

static u_int8_t bytereg[4];

int main(int argc, char *argv[])
{
	int aic14_fd  = -1;
	int vol       = -1;

	bytereg[0]    = 0;
	bytereg[1]    = 0;
	bytereg[2]    = 0;
	bytereg[3]    = 0;

	if (argc == 2) {

		if (sscanf(argv[1], "%d", &vol) == 1) {
			
			if (vol < 0) {
				vol = 0;
			}
			if (vol > MAXLEVEL) {
				vol = MAXLEVEL;
			}
			bytereg[0] = vol;

			if (! ((aic14_fd = open(AIC14_DEV, O_WRONLY)) < 0)) {
				
				if (ioctl(aic14_fd, AIC14_SET_DAC_GAIN, bytereg) == -1) {
					fprintf(stderr, "err: AIC14_SET_DAC_GAIN ioctl failed\n");
				}
				
				close(aic14_fd);
			} else {
				perror("err: " AIC14_DEV " not opened");
			}
		} else {
			fprintf(stderr, "err: could not parse volume: <%s>\n", argv[1]);
		}
	} else {
		fprintf(stderr, "err: enter volume as first argument (range 0-255)\n");
	}

	return 0;
}
