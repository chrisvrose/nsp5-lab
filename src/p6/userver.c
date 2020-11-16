#include <comsoc.h>

int respond(int connectfd) {
    char buf1[500];
    pid_t pid = getpid();
    int i = 0, j = 0, k = 0;

    struct sockaddr_in address;
    socklen_t socklen = sizeof(address);
    int len;
    // recvfrom(connectfd,&size,sizeof (size),0,&address,&socklen);

    if ((len = recvfrom(connectfd, buf1, sizeof(buf1), 0, &address,
                        &socklen)) != sizeof(buf1)) {
        // if(len ==-1) return 1;
        // something went wrong
        printf("E> Could not get back size(%d)\n", len);
        return 1;
    }
    printf("I>Got back data\n");
    // print out recved data safely
    printf("I>DATA:");
    for (int l = 0; l < 500; l++) {
        if (!buf1[l])
            break;
        printf("%c", buf1[l]);
    }
    printf("\n");

    if (sendto(connectfd, buf1, sizeof(buf1), 0, &address, sizeof(address)) !=
        sizeof(buf1)) {
        printf("E> Could not send back string (%d)\n", socklen);
        return 1;
    }

    printf("%d>Wrote back data\n", pid);
}

int main() {
    printf("I>Hello world\n");
#pragma region Boilerplate
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("E>Failed to allocate socket\n");
        return E_F;
    } else {
        printf("I>Allocated socket %d\n");
    }

    // init structure
    struct sockaddr_in address = {.sin_family = AF_INET,
                                  .sin_addr = {.s_addr = INADDR_ANY},
                                  .sin_port = htons(PORT)};

    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        printf("E>failed to bind\n");
        return E_F;
    }

#pragma endregion

    for (;;) {
        respond(sockfd);
    }
    close(sockfd);
}