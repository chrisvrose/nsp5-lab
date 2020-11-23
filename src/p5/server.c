#include <comsoc.h>
#define BUFFER_SIZE 500
// handle all children that are returning and collect their returns
void child_handler(int sig) {
    pid_t pid;
    int status;
    /* EEEEXTEERMINAAATE! */
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("G>Child(%d) has exit\n", pid);
    }
}

void respond(int connFd) {
    printf("I>forking again\n");
    pid_t pid = fork();

    if (pid == -1) {
        printf("E> could not fork\n");
    } else if (pid == 0) {
        fd_set fdset;
        char resp[500];
        int k = 0;
        FD_ZERO(&fdset);
        FD_SET(connFd, &fdset);

        uint16_t size = 0;
        printf("I>waiting for input\n");
        fflush(stdout);
        while (select(connFd+1, &fdset, NULL, NULL, NULL)!=-1) {
            // get size
            fflush(stdout);
            if(recv(connFd, &size, sizeof(size),0)!=sizeof(size)){
                printf("E>ABORTED\n");
                return;
            }

            size = ntohs(size);
            
            if(recv(connFd, resp, size, 0)!=size){
                printf("E>ABORTED\n");
                return;
            };
            printf("C>(%d) ",size);
            fflush(stdout);
            // print the text received
            for (k = 0; k < size&& k<BUFFER_SIZE; k++) {
                printf("%c", resp[k]);
            }
            printf("\n");

            fflush(stdout);
            FD_ZERO(&fdset);
            FD_SET(connFd, &fdset);
        }

        printf("E>Got out\n");
        fflush(stdout);
    } else {
        char buffer[BUFFER_SIZE];
        while (1) {
            int n = 0, i = 0, j = 0, k = 0;
            // print output
            while ((buffer[n++] = getchar()) != '\n')
                ;
            buffer[n - 1] = 0;
            //get len
            k = strlen(buffer);

            printf("I>Got data from stdin \"%s\",%d\n", buffer, k);

            // send size
            uint16_t size = htons(k);
            if (send(connFd, &size, sizeof(size), 0) != sizeof(size)) {
                // something went wrong
                printf("E> Closing socket as could not send size\n");
                close(connFd);return ;
            }

            // send string
            if ((i = send(connFd, buffer, k, 0)) != k) {
                printf("W>Could not send whole string\n");
            }
        }
    }

    close(connFd);
}

int main() {
    signal(SIGCHLD, child_handler);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "E>Failed to allocate socket\n");
        return E_F;
    } else {
        printf("I>Allocated socket %d\n");
    }

    // init structure
    struct sockaddr_in address = {.sin_family = AF_INET,
                                  .sin_addr = {.s_addr = INADDR_ANY},
                                  .sin_port = htons(PORT)};

    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        fprintf(stderr, "E>failed to bind");
        return E_F;
    }

    if (listen(sockfd, 2) < 0) {
        fprintf(stderr, "E>Failed to set to listen mode");
        return E_F;
    }

    int newSock, pid;
    socklen_t len;
    int t;
    while ((newSock = accept(sockfd, (struct sockaddr*)&address, &len)) >= 0) {
        pid = fork();
        if (pid == 0) {
            printf("%d>Created to respond\n", getpid());
            respond(newSock);
            close(newSock);
            return 0;
        } else if (pid == -1) {
            fprintf(stderr, "E>Could not respond\n");
            close(newSock);

            break;
        } else {
            waitpid(-1, &t, WNOHANG);
        }
    }
    close(sockfd);
}