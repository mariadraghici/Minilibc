// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <internal/syscall.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
	long res = syscall(__NR_stat, path, buf);
	if (res >= 0) {
		return res;
	}

	errno = -res;
	return -1;
}
