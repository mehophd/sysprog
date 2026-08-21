#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE   
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
    char buf[BUF_SIZE];
    ssize_t numRead;
    int outputFd, openFlags;
    mode_t filePerms;
    char *filename;

    if (argc < 2 || argc > 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s [-a] file\n", argv[0]);

    openFlags = O_CREAT | O_WRONLY;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;
    
    if (strcmp("-a", argv[1]) == 0) {
        if (argc < 3)
            usageErr("%s -a file\n", argv[0]);
        filename = argv[2];
    } else {
        filename = argv[1];
        openFlags |= O_TRUNC;
    }

    outputFd = open(filename, openFlags, filePerms);
    if (outputFd == -1)
        errExit("opening file %s", filename);

    if (strcmp("-a", argv[1]) == 0)
        if (lseek(outputFd, 0, SEEK_END) == -1)
            errExit("lseek");
    
    while ((numRead = read(0, buf, BUF_SIZE)) > 0 ) {
        if (write(1, buf, numRead) != numRead)
            fatal("couldn't write whole buffer to stdout");

        if (write(outputFd, buf, numRead) != numRead)
            fatal("couldn't write whole buffer to file");
    }

    if (numRead == -1)
        errExit("read");

    if (close(outputFd) == -1)
        errExit("close");
}