#include<comsoc.h>

int main(int argc, char** argv){
    char buffer[FILELEN], resp[2000];
    int i=0, j=0, k=0,n=0;
    int32_t fSize = 0;
    printf("I>Hello world\n");
    if (argc < 2)
    {
        printf("E>No addr\n");
        return E_F;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("E>Failed to allocate socket");
        return E_F;
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
        return E_F;
    };

    if (connect(sockfd, (struct sockaddr *)&address, sizeof address) < 0)
    {
        printf("E>Failed connect, cri\n");
        return E_F;
    }
    printf("Enter file name\n:");
    while ((buffer[n++] = getchar()) != '\n') 
            ; 
    buffer[n-1] = 0;

    send(sockfd,buffer,FILELEN,0);


    //get size
    read(sockfd,&fSize,sizeof(int32_t));
    fSize = ntohl(fSize);
    printf("I> Read filesize %d\n",fSize);
    i=0,j=0,k=0;

    // int fd = open(FILE_OP,O_CREAT|O_WRONLY,777);
    if(fSize==0){
        fprintf(stderr,"E> ServerError\n");
        return 0;
    }
    printf("I>File contents:\n");
    while(j<fSize){
        i= recv(sockfd,resp,sizeof(resp),0);
        j+=i;
        // printf("I>READ up %d\n",i);
        for(k=0;k<i;k++){
            printf("%c",resp[k]);
        }
    }

    printf("\nI>File contents over\n");

    // close(fd);
    close(sockfd);


}