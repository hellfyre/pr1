#ifndef __MEASURE_PROCESSTIME_H__
#define __MEASURE_PROCESSTIME_H__

/**
 * Run measure functions once
 *
 * Apparently calling functions for the first time takes significantly longer
 * than subsequent calls. measure_init() calls clock_gettime(), so the actual
 * measurement calls are more precise.
 */
void measure_init();

/**
 * Starts measurement
 */
void measure_start();

/**
 * Ends measurement
 *
 * Precision approximately 380 nanoseconds, 515 in PBS
 *
 * @return The difference between measure_start() and measure_end().
 */
long measure_end();

#endif /* __MEASURE_PROCESSTIME_H__ */
