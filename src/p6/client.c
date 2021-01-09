/*
 * Process - 
 * 1. Send a unsigned 16 bit integer that is the size of the string
 * 2. Expect the same reply, and print it
 *  
*/

#include <comsoc.h>

#define BUFFER_SIZE 500
int main(int argc, char **argv)
{
    char buffer[BUFFER_SIZE], resp[BUFFER_SIZE];
    int i=0, j=0, k=0,n=0;

    #pragma region Boilerplate
    printf("I>Hello world\n");
    if (argc < 2)
    {
        printf("E>No addr\n");
        return 1;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("E>Failed to allocate socket");
        return 1;
    }
    else
    {
        printf("I>Allocated socket %d\n");
    }

    //init structure
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
    };
    if (inet_pton(AF_INET, argv[1], &(address.sin_addr)) < 0)
    {
        printf("E>Could not get self addr\n");
        return 1;
    };

    if (connect(sockfd, (struct sockaddr *)&address, sizeof address) < 0)
    {
        printf("E>Failed connect, cri\n");
        return 1;
    }
    #pragma endregion 

    //send req
    printf("Enter data\n:");
    // scanf("%s",buffer);
    
    printf("Enter string to send\n:");
    while ((buffer[n++] = getchar()) != '\n') 
            ; 
    buffer[n-1] = 0;


    k = strlen(buffer);
    printf("I>Got data \"%s\",%d\n", buffer,k);
    
    
    //send size
    uint16_t size = htons(k);
    if( send(sockfd,&size,sizeof (size),0) != sizeof(size) ) {
        //something went wrong
        printf("E> Closing socket as could not send size\n");
        close(sockfd);
    }

    //send string
    while (j<k)
    {
        if ((i = send(sockfd, buffer+j, k-j,0)) == 0) break;
        j += i;
        printf("I>Wrote %d/%d chars\n", j, k);
    }
    printf("I>Done, wrote %d/%d\n",j,k);

    //recv resp
    printf("I>Response:\n");
    fflush(stdout);
    j=0;
    while (j<k)
    {
        if ((i = recv(sockfd, resp+j, k-j,0)) == 0) break;
        j+=i;
        fflush(stdout);
        if(j>=BUFFER_SIZE) break;
    }
    for(int i=0;i<k&&i<BUFFER_SIZE;i++){
        printf("%c", resp[i]);
    }
    printf("\nI>Done\n");

    close(sockfd);
}