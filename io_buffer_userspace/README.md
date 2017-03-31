# User space serial port reading in C
This is my attempt to write continuously data to the UART1 port of the BeagleBone with an Arduino and reading those 
inputs on the BeagleBone. The input is written to a file.
There is specified a number of messages transferred, the goal is to find out if the BegleBone will drop some messages
(and thus, to check if an UART FIFO overflow might occour) when reading the I/O from userspace. This experiment teaches me
accessing the serial port from C and will have an impact on my implementation decision. If it turns out that user space
performace is too bad I will try to configure the serial driver to redirect DMA directly to a log file.
