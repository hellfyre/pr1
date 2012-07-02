#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>

// ### Interface
/*
   Resets time measurement.
   Needs to be called first
   before any succeeding call
   of getTime() or getTimes(). 
 */
void resetTime();
/*
   Returns the time elapsed since last call
   of resetTime(), getTime() or getTimes().
   Time unit: seconds [s]
   Accuracy (on AKB): 1-2 microseconds
 */
double getTime();
/*
   Behaves like getTime().
   Additionally *utime and *stime are set
   to the user time and system time consumed
   by the calling process.
 */
double getTimes(double *utime, double *stime);

// ### Attributes
static long ticks;
static double startTime;

// ### Implementation

void resetTime()
{
    struct timeval tv;
    struct timezone tz;
    ticks = sysconf(_SC_CLK_TCK);
    gettimeofday(&tv, &tz);
    startTime = (double)tv.tv_sec + ((double)tv.tv_usec)*0.000001;
}

double getTime()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    double curTime = (double)tv.tv_sec + ((double)tv.tv_usec)*0.000001;
    return curTime - startTime;
}

double getTimes(double *utime, double *stime)
{
    struct timeval tv;
    struct timezone tz;
    struct tms ts;
    gettimeofday(&tv, &tz);
    double curTime = (double)tv.tv_sec + ((double)tv.tv_usec)*0.000001;
    if ((clock_t) times(&ts) == -1) { printf("[gettime.c] times function reported error: %d\n", errno); }
    *utime = (double)ts.tms_utime/ticks;
    *stime = (double)ts.tms_stime/ticks;
    return curTime - startTime;
}

