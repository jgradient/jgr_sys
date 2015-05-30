#include <time.h>

int
main(int argc, char **argv)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return 0;
}
