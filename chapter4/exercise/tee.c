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

    if (argc < 2 || argc > 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s [-a] file\n", argv[0]);

    openFlags = O_CREAT | O_WRONLY;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;
    
    if (strcmp("-a", argv[1]) == 0) {
        if (argc < 3)
            usageErr("%s -a file\n", argv[0]);
        outputFd = open(argv[2], openFlags, filePerms);
        if (lseek(outputFd, 0, SEEK_END) == -1)
            errExit("lseek");
    } else {
        outputFd = open(argv[1], openFlags, filePerms);
    }
    if (outputFd == -1)
        errExit("opening file %s", argv[1]);

    numRead = read(0, buf, BUF_SIZE - 1);
    buf[numRead] = '\0';
    write(1, buf, numRead);
    if (write(outputFd, buf, numRead) != numRead)
        fatal("couldn't write whole buffer");
        

}