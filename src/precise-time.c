#include <assert.h>
#include <sys/time.h>
#include <time.h>
/* unistd.h defines _POSIX_TIMERS */
#include <unistd.h>

#include "precise-time.h"

__thread int now;
__thread double precise_now;
__thread long long precise_now_rdtsc;
long long precise_time;
long long precise_time_rdtsc;

double get_utime_monotonic(void) {
  struct timespec T;
  assert(clock_gettime(CLOCK_MONOTONIC, &T) >= 0);
  precise_now_rdtsc = rdtsc();
  return precise_now = (double)T.tv_sec + (double)T.tv_nsec * 1e-9;
}

double get_double_time(void) {
  static double last_double_time = -1;
  static long long next_rdtsc;
  long long cur_rdtsc = rdtsc();
  if (cur_rdtsc > next_rdtsc) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    next_rdtsc = cur_rdtsc + 1000000;
    return (last_double_time = (double)tv.tv_sec + 1e-6 * (double)tv.tv_usec);
  } else {
    return last_double_time;
  }
}

double get_utime(int clock_id) {
  struct timespec T;
  assert(clock_gettime(clock_id, &T) >= 0);
  double res = (double)T.tv_sec + (double)T.tv_nsec * 1e-9;
  if (clock_id == CLOCK_REALTIME) {
    precise_time = (long long)(res * (1LL << 32));
    precise_time_rdtsc = rdtsc();
  }
  return res;
}

long long get_precise_time(unsigned precision) {
  unsigned long long diff = rdtsc() - precise_time_rdtsc;
  if (diff > precision) {
    get_utime(CLOCK_REALTIME);
  }
  return precise_time;
}

