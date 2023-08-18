// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp) {
   long res = syscall(__NR_nanosleep, rqtp, rmtp);
   if (res >= 0) {
      return res;
   }

   errno = -res;
   return -1;
}

unsigned int sleep(unsigned int seconds) {
   struct timespec t;
   t.tv_sec = seconds;
   t.tv_nsec = 0;
   int res = nanosleep(&t, NULL);
   return res;
   return 0;
}