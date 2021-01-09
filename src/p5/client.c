/*
 * Process -
 * 1. Send a unsigned 16 bit integer that is the size of the string
 * 2. Expect the same reply, and print it
 *
 */

#include <comsoc.h>

#define BUFFER_SIZE 500

int writer(int sockfd) {
    // getchar();
    while (1) {
        char buffer[BUFFER_SIZE];
        int n = 0, i = 0, j = 0, k = 0;
        // print output
        // send req
        // scanf("%s",buffer);
        while ((buffer[n++] = getchar()) != '\n')
            ;
        buffer[n - 1] = 0;
        k = strlen(buffer);
        printf("I>Got data \"%s\",%d\n", buffer, k);

        // send size
        uint16_t size = htons(k);
        if (send(sockfd, &size, sizeof(size), 0) != sizeof(size)) {
            // something went wrong
            printf("E> Closing socket as could not send size\n");
            close(sockfd);
            return 1;
        }

        // send string
        if ((i = send(sockfd, buffer, k, 0)) != k) {
            printf("W>Could not send whole string\n");
        }
        printf("I>Sent %d/%d\n", i, k);
    }
}

int reader(int sockfd) {
    printf("I>Setting up reader\n");
    fd_set fdset;
    char resp[500];
    int k = 0;
    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);

    uint16_t size = 0;
    while (select(sockfd + 1, &fdset, NULL, NULL, NULL)) {
        // get size
        if (read(sockfd, &size, sizeof(size)) != sizeof(size)) {
            printf("E>ABORT\n");
            return 1;
        };
        size = ntohs(size);
        if (recv(sockfd, resp, size, 0) != size) {
            return 1;
        }
        // print the text received
        printf("S>(%d) ", size);
        for (k = 0; k < size && k < 500; k++) {
            printf("%c", resp[k]);
        }

        printf("\n");

        fflush(stdout);

        FD_ZERO(&fdset);
        FD_SET(sockfd, &fdset);
    }
}

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE], resp[BUFFER_SIZE];
    int i = 0, j = 0, k = 0, n = 0;

#pragma region Boilerplate
    printf("I>Hello world\n");
    if (argc < 2) {
        printf("E>No addr\n");
        return 1;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("E>Failed to allocate socket");
        return 1;
    } else {
        printf("I>Allocated socket %d\n");
    }

    // init structure
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
    };
    if (inet_pton(AF_INET, argv[1], &(address.sin_addr)) < 0) {
        printf("E>Could not get self addr\n");
        return 1;
    };

    if (connect(sockfd, (struct sockaddr*)&address, sizeof address) < 0) {
        printf("E>Failed connect, cri\n");
        return 1;
    }
#pragma endregion

    printf("I>Forking\n");
    pid_t pid = fork();

    if (pid == -1) {
        printf("E>fork failed, leaving\n");
        return 1;

    } else if (pid == 0) {
        writer(sockfd);
    } else {
        reader(sockfd);
    }

    close(sockfd);
}
