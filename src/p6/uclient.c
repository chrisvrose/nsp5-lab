#include <comsoc.h>

#define BUFFER_SIZE 500
int main(int argc, char** argv) {
    printf("I>Hello world\n");

    char buffer[BUFFER_SIZE], resp[BUFFER_SIZE];
    int i = 0, j = 0, k = 0, n = 0;

#pragma region Boilerplate
    if (argc < 2) {
        printf("E>No addr\n");
        return 1;
    }
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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
        printf("E>Could not get convert addr\n");
        return 1;
    }

    // check
    if (connect(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        printf("\n Error : Connect Failed \n");
        exit(0);
    }
#pragma endregion

#pragma region input to `buffer`
    printf("Enter string to send\n:");
    while ((buffer[n++] = getchar()) != '\n')
        ;
    buffer[n - 1] = 0;

    k = strlen(buffer);
    printf("I>Got data \"%s\",%d\n", buffer, k);
#pragma endregion

    if (sendto(sockfd, buffer, sizeof(buffer), 0, &address, sizeof(address)) !=
        sizeof(buffer)) {
        printf("E> Could not send string\n");
        return 0;
    }
    printf("I>Sent buffer\n");
    if (recvfrom(sockfd, resp, sizeof(resp), 0, NULL, NULL) != sizeof(buffer)) {
        printf("E> Could not recv string\n");
        return 0;
    }

    printf("I>Received:");
    for (i = 0; i < k; i++) {
        if (!resp[i]) {
            break;
        }
        printf("%c", resp[i]);
    }
    printf("\nI>Done\n");

    close(sockfd);
}