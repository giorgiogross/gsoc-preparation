#include "connector.h"

#define BAUDRATE B230400

int connectToSerial(char* device_node) {
    if(device_node == NULL) return -1;

    int devFd = open(device_node, O_RDWR | O_NOCTTY);
    if(devFd == -1) {
        printf("Error opening %s\n", device_node);
        return -1;
    } else printf("Opened %s\n", device_node);

    // sync
    // fcntl(devFd, F_SETFL, 0);

    /* Make the file descriptor asynchronous (the manual page says only 
    O_APPEND and O_NONBLOCK, will work with F_SETFL...) */

    // async receive
    // fcntl(devFd, F_SETFL, FNDELAY);
    // fcntl(devFd, F_SETFL,  O_ASYNC );

    struct termios config;
    // get current settings of serial port
    if(tcgetattr(devFd, &config) == -1) {
        printf("Not able to get attributes\n");
    }

    // adjust baud rate
    if(cfsetispeed(&config, (speed_t)BAUDRATE) == -1) {
        printf("Not able to set ctfo speed\n");
    }
    if(cfsetospeed(&config, (speed_t)BAUDRATE) == -1) {
        printf("Not able to set ctfi speed\n");
    }

    config.c_cflag |= (CLOCAL | CREAD);
    // 8N1
    config.c_cflag &= ~CSIZE;
    config.c_cflag |= CS8;
    config.c_cflag &= ~PARENB;
    config.c_cflag &= ~CSTOPB;

    /* setup for non-canonical mode */
    config.c_iflag &= ~(ISTRIP | IXON);
    config.c_lflag &= ~(ICANON);
    config.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    config.c_cc[VMIN] = 255; // maximum is 255 bytes
    config.c_cc[VTIME] = 1;

    // apply the settings
    tcflush(devFd, TCIFLUSH);
    if(tcsetattr(devFd, TCSANOW | TCSAFLUSH, &config) == -1) {
        printf("Not able to set tio attributes\n");
    }

    return devFd;
}

void disconnect(int fd) {
    if(fd >= 0) close(fd);
}