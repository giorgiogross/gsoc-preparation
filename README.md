# gsoc-preparation
Here are my examples, drafts and sketches to get prepared for GSoC. 
I added BeagleBone serial port comunication from user space to check the performace of the termios API when there are many inputs. 
Proving that no I/O is dropped will help me decide how things can be implemented in the GSoC project.

There is also a web server written in NodeJS. I will explore what's possible with NodeJS on the BeagleBone and add a ReactJS 
interface to gain more experience.

Also make sure to cehck out the GSoC cathegory on my Blog: http://www.giorgio-gross.de/blog/index.php/category/gsoc/ <br>
I'll collect ideas and summarize important information related to the project there.



# Results
Below you can find the results of my tests and experiments.

### Synchronous Serial Port Communication
Even when writing 20000 messages all at once with the maximum baud rate supported by the temios API (B230400) from all four serial ports there were no messages dropped! Reading from the port and writing to a log file all happens synchronously, but the driver seems to take care of pretty much everything. Reading one byte or multiple bytes from the serial buffer does not seem to make a difference and both perform good. I tested this with non-canonical input mode; with canonical input mode (see other branches) I was able to separate the log into single messages devided by their time stamps. When doing this it is easy to find out the limitations of the built in buffer: The serial device can send up to 4096 characters without a line break. But if it sends more, the first messages which arrived will be dropped as the buffer fills up. That makes sense, as one page is 4096 bytes large. To overcome this issue later the user of the serial terminal server should be able to select non-canonical mode. That way the buffer can be read in time. Another possibility would be to use non-canonical mode per default and divide the logs manually after each \n character.

### Asynchronous Serial Port Communication
This was tested with canonical mode and led to the same results as sith synchronous serial port communication. The same limits apply, but inputs can be handled without needing to spawn a new thread for I/O tasks. This can be an improvement for the serial terminal server implementation, as I would like to avoid blocking the UI thread.
