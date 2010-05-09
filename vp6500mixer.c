#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/soundcard.h>

#define MAXLEVEL 100

int main(int argc, char *argv[])
{
	int mixer_fd  = -1;
	int err       = -1;
	int device    = SOUND_MIXER_VOLUME;
	int vol       = -1;

	if (argc == 2) {

		if (sscanf(argv[1], "%d", &vol) == 1) {
			
			if (vol < 0) {
				vol = 0;
			}
			if (vol > MAXLEVEL) {
				vol = MAXLEVEL;
			}
			vol = vol + (vol << 8);

			if (! ((mixer_fd = open("/dev/mixer1", O_WRONLY)) < 0)) {
				
				if (ioctl(mixer_fd, MIXER_WRITE(SOUND_MIXER_VOLUME), &vol) == -1) {
					fprintf(stderr, "err: MIXER_WRITE ioctl to VOLUME failed\n");
				}
				if (ioctl(mixer_fd, MIXER_WRITE(SOUND_MIXER_SPEAKER), &vol) == -1) {
					fprintf(stderr, "err: MIXER_WRITE ioctl to SPEAKER failed\n");
				}
				
				close(mixer_fd);
			} else {
				fprintf(stderr, "err: /dev/mixer1 not opened\n");
			}
		} else {
			fprintf(stderr, "err: could not parse volume: <%s>\n", argv[1]);
		}
	} else {
		fprintf(stderr, "err: enter volume as first argument\n");
	}

	return 0;
}
