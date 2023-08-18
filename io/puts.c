#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <string.h>

int puts(const char *str) {
    int res = write(1, str, strlen(str));
    res *= write(1, "\n", 1);

    if (res != -1) {
        return res;
    }

    return -1;
}