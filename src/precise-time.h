#ifndef __PRECISE_TIME_H__
#define __PRECISE_TIME_H__

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RDTSC */
#if defined(__i386__)
static __inline__ unsigned long long rdtsc(void) {
  unsigned long long int x;
  __asm__ volatile("rdtsc" : "=A"(x));
  return x;
}
#elif defined(__x86_64__)
static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}
#endif

/* net-event.h */
extern __thread int now;
extern __thread double precise_now;
extern __thread long long precise_now_rdtsc;
double get_utime_monotonic(void);

/* common/server-functions.h */
double get_utime(int clock_id);
extern long long precise_time;       // (long long) (2^16 * precise unixtime)
extern long long precise_time_rdtsc; // when precise_time was obtained
long long get_precise_time(unsigned precision);

/* ??? */
double get_double_time(void);

static inline void precise_sleep(int seconds, int nanoseconds) {
  struct timespec t;
  t.tv_sec = seconds;
  t.tv_nsec = nanoseconds;
  nanosleep(&t, NULL);
}
#endif

#ifdef __cplusplus
}
#endif
