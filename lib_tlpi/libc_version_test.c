#include <gnu/libc-version.h>
#include <stdio.h>

const char *gnu_get_libc_version(void);


int main(void) {
    printf("Версия glibc: %s\n", gnu_get_libc_version());
    return 0;
}