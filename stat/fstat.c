// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <errno.h>
#include <internal/syscall.h>


int fstat(int fd, struct stat *st)
{
	long res = syscall(__NR_fstat, fd, st);
	if (res >= 0) {
		return res;
	}

	errno = -res;
	return -1;
}
