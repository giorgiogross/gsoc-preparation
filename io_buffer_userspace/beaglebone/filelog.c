#include "filelog.h"

int createFile(char* path) {
    int fd = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRWXU | S_IRGRP | S_IWGRP);
    if(fd == -1) {
        printf("Could not open/create file\n");
        return -1;
    }
}

int logMessage(int fd, char* buf, int size) {
    if(buf == NULL || fd < 0 || size < 0) return -1;

    // get time
    time_t rTime;
    struct tm * mTime;
    time(&rTime);
    mTime = localtime(&rTime);

    char* ascTime = asctime(mTime);
    int ascTimeLen = strlen(ascTime);
    ascTime[ascTimeLen - 1] = 0; // get rid of the new line
    int count = ascTimeLen + 1 + size + 6;
    char mBuf[count];
    // copy everiting into a convenient message:
    sprintf(mBuf, "%s ## %s\n", ascTime, buf);

    // write and return
    return 0 <= write(fd, &mBuf, count);
}