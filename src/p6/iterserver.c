#include <comsoc.h>

//handle all children that are returning and collect their returns
// void child_handler(int sig)
// {
//     pid_t pid;
//     int status;
//     /* EEEEXTEERMINAAATE! */
//     while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
//     {
//         printf("G>Child(%d) has exit\n", pid);
//     }
// }

int respond(int connectfd)
{

    char buf1[500], buf2[500];
    pid_t pid = getpid();
    int i = 0, j = 0, k = 0;

    //get input length from client
    uint16_t size;
    if( recv(connectfd,&size,sizeof (size),0) != sizeof(size) ) {
        //something went wrong
        printf("E> Closing socket as could not send size\n");
        return 1;
    }

    //convert back to our computer's endianness - wooo
    size = ntohs(size);
    printf("%d>Got size (%d)\n", pid,size);

    //now recieve the size of it
    printf("%d>Attempting to get input\n", pid);
    //get client req
    while ((i = recv(connectfd, buf1 + j, size-j,0)) > 0)
    {
        j += i;
        printf("%d>Read %d,=%d,(%d)\n", pid, i, buf1[j], j);
        if (j >= k || j>=500)
        {
            printf("%d> Input over\n", pid);
            break;
        }
    }
    printf("%d>Processed input\n", pid);
    printf("%d>Fin Read string length %d\n", pid, strlen(buf1));
    //respond back with j chars
    while (k < size)
    {
        i = send(connectfd, buf1 + k, size-k,0);
        if (i == 0)
            break;
        k += i;
    }
    printf("%d>Wrote back data\n", pid);
}

int main()
{
    // signal(SIGCHLD, child_handler);
    printf("I>Hello world\n");
    #pragma region Boilerplate
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("E>Failed to allocate socket\n");
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
        printf("E>failed to bind\n");
        return 1;
    }

    if (listen(sockfd, 2) < 0)
    {
        printf("E>Failed to set to listen mode\n");
        return 1;
    }

    #pragma endregion

    int newSock, pid;
    socklen_t len;
    int t;
    while ((newSock = accept(sockfd, (struct sockaddr *)&address, &len)) >= 0)
    {
        respond(newSock);
        close(newSock);
            
    }
    close(sockfd);
}