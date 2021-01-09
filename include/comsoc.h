#ifndef __COMSOC_H
#define __COMSOC_H 1

#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
// all system type aliases
#include<sys/types.h>

// fstat
#include<sys/stat.h>
#include<fcntl.h>

//all the nps headers
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>

// wait
#include<sys/wait.h>
// select call 
#include<sys/select.h>
#include<unistd.h>

#define PORT 3000
//time buffer size
#define FILELEN 100

#endif