#ifndef __LINUXSERIAL_H__
#define __LINUXSERIAL_H__


#include "linuxserial.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>   
#include <termios.h>
#include <errno.h>  
 
#define DEVICE "/dev/ttyS0"  


int openItem();
int closeItem();



#endif 