// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	long cls = syscall(__NR_close, fd);
	if (cls >= 0) {
		return cls;
	}

	errno = -cls;
	return -1;
}
