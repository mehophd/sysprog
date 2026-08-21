#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    char buf[BUF_SIZE];
    ssize_t numRead;

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        cmdLineErr("%s inputfile outputfile", argv[0]);
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;

    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        errExit("opening file %s", argv[1]);
    
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
        errExit("opening file %s", argv[2]);
    
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        int i = 0;

        while (i < numRead) {
            if (buf[i] == '\0') {
                int holeLen = 0;
                while (i < numRead && buf[i] == '\0') {
                    holeLen++;
                    i++;
                }

                if (lseek(outputFd, holeLen, SEEK_CUR) == -1)
                    errExit("lseek");
            } else {
                int dataStart = i;
                int dataLen = 0;
                while (i < numRead && buf[i] != '\0') {
                    dataLen++;
                    i++;
                }

                if (write(outputFd, &buf[dataStart], dataLen) != dataLen)
                    fatal("couldn't write whole buffer to stdout");
            }
        }
    }

    if (numRead == -1)
        errExit("read");
    if (close(inputFd) == -1)
        errExit("close input");
    if (close(outputFd) == -1)
        errExit("close output");
}