#include "linuxserial.h"

  
int serial_fd = 0;  
  
 
int init_serial()  
{  
    serial_fd = open(DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);  
    if (serial_fd < 0) {  
        perror("open");  
        return -1;  
    }  
      
    struct termios options;  
      
    tcgetattr(serial_fd, &options);  
    
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE; 
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CSTOPB;
    options.c_iflag |= IGNPAR; 
    options.c_oflag = 0; 
    options.c_lflag = 0; 
    cfsetospeed(&options, B9600);  
      
 
    tcflush(serial_fd, TCIFLUSH);
    tcsetattr(serial_fd, TCSANOW, &options);  
      
    return 0;  
}  
  

int uart_send(int fd, unsigned char *data, int datalen)  
{  
    int len = 0;  
    len = write(fd, data, datalen);
    if(len == datalen) {  
        return len;  
    } else {  
        tcflush(fd, TCOFLUSH); 
        return -1;  
    }  
      
    return 0;  
}  
  
 
int uart_recv(int fd, unsigned char *data, int datalen)  
{  
    int len=0, ret = 0;  
    fd_set fs_read;  
    struct timeval tv_timeout;  
      
    FD_ZERO(&fs_read);  
    FD_SET(fd, &fs_read);  
    tv_timeout.tv_sec  = (10*20/115200+2);  
    tv_timeout.tv_usec = 0;  
      
    ret = select(fd+1, &fs_read, NULL, NULL, &tv_timeout);  
    printf("ret = %d\n", ret);  
       
    if (FD_ISSET(fd, &fs_read)) {  
        len = read(fd, data, datalen);  
        printf("len = %d\n", len);  
        return len;  
    } else {  
        perror("select");  
        return -1;  
    }  
      
    return 0;  
}  

unsigned char manuOpenCMD[] = {0x05, 0x0C, 0x05, 0xB9, 0xB1, 0x07, 0x00, 0x3F, 0x47, 0x5C};
unsigned char manuCloseCMD[] = {0x05, 0x0C, 0x05, 0xB9, 0xB1, 0x07, 0x00, 0xBF, 0x46, 0xFC};




  
int openItem() {  
    init_serial();  
  
    for(int i = 0; i < 300; i ++)
     	uart_send(serial_fd, manuOpenCMD, 10);  
    
    close(serial_fd);  
    return 0;  
}  


int closeItem() {
	init_serial();  
  
    for(int i = 0; i < 300; i ++)
    	uart_send(serial_fd, manuCloseCMD, 10);  
    
    close(serial_fd);  
    return 0;  
}