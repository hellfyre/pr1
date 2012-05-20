#include <time.h>

static struct timespec begin, end;
static long timediff = 0;

void measure_init() {
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
}

void measure_start() {
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
}

long measure_end() {
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
  timediff = end.tv_nsec-begin.tv_nsec;
  return timediff;
}
