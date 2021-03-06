#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include<unistd.h>
#define HELLO_PORT 12345
#define HELLO_GROUP "224.0.0.1"
//"225.0.0.37"
//"127.10.10.8"

#ifndef __USE_MISC
struct ip_mreq
  {
    /* IP multicast address of group.  */
    struct in_addr imr_multiaddr;

    /* Local IP address of interface.  */
    struct in_addr imr_interface;
  };
#endif

int main(int argc, char* argv[]) {
    struct sockaddr_in addr;
    int fd, cnt;
    struct ip_mreq mreq;
    char* message = "RVCE-CSE";

    /* create what looks like an ordinary UDP socket */
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    /* set up destination address */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(HELLO_GROUP);
    addr.sin_port = htons(HELLO_PORT);

    /* now just sendto() our destination! */
    while (1) {
        if (sendto(fd, message, sizeof(message), 0, (struct sockaddr*)&addr,
                   sizeof(addr)) < 0) {
            perror("sendto");
            exit(1);
        }
        sleep(1);
    }
}