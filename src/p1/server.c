#include <comsoc.h>

//handle all children that are returning and collect their returns
void child_handler(int sig)
{
    pid_t pid;
    int status;
    /* EEEEXTEERMINAAATE! */
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        printf("G>Child(%d) has exit\n", pid);
    }
}

void respond(int connFd)
{
    //get filename
    char buffer[FILELEN + 1] = {0};
    char fileBuffer[FILELEN];
    int i = 0, j = 0, k = 0,l=0;
    int32_t fileSize = 0;
    int fStatReturn = -1;
    struct stat fileStat;

    printf("%d>Ready\n", connFd);
    while (i < FILELEN)
    {
        i += recv(connFd, buffer + i, FILELEN - i, 0);
    }

    printf("I>File\"%s\"\n", buffer);

    int fd = open(buffer, O_RDONLY);
    //get a uint32_t size
    if (fd != -1)
    {
        printf("I>Getting file size\n");
        fStatReturn = fstat(fd, &fileStat);
        fileSize = fileStat.st_size;
    }
    fileSize = htonl(fileSize);
    //send the filesize
    send(connFd, &fileSize, sizeof(int32_t), 0);
    fileSize = ntohl(fileSize);
    printf("I>File size %d\n", fileSize);
    //send only if okay
    i=0,j=0,k=0;
    if (fStatReturn != -1 && fd != -1)
    {
        while (j < fileSize)
        {
            i = read(fd, fileBuffer, FILELEN);
            j+=i;
            while (k < i)
            {
                l = write(connFd, fileBuffer, i);
                if(l<0){
                    printf("E> Closed suddenly\n");
                    close(connFd);
                    return;
                }
                k+=l;
                // printf("I>Wrote %d\n",k);
            }
            k=0;
        }
        close(fd);
    }
    else
    {
        fprintf(stderr, "E>Could not open file\n");
    }

    close(connFd);
}

int main()
{
    signal(SIGCHLD, child_handler);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "E>Failed to allocate socket\n");
        return 1;
    }
    else
    {
        printf("I>Allocated socket %d\n");
    }

    //init structure
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_addr = {.s_addr = INADDR_ANY},
        .sin_port = htons(PORT)};

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        fprintf(stderr, "E>failed to bind");
        return 1;
    }

    if (listen(sockfd, 2) < 0)
    {
        fprintf(stderr, "E>Failed to set to listen mode");
        return 1;
    }

    int newSock, pid;
    socklen_t len;
    int t;
    while ((newSock = accept(sockfd, (struct sockaddr *)&address, &len)) >= 0)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("%d>Created to respond\n", getpid());
            respond(newSock);
            close(newSock);
            return 0;
        }
        else if (pid == -1)
        {
            fprintf(stderr, "E>Could not respond\n");
            close(newSock);

            break;
        }
        else
        {
            waitpid(-1, &t, WNOHANG);
        }
    }
    close(sockfd);
}