#include<stdio.h>

unsigned short checksum(unsigned fields[10])
{
    int i;
    int sum=0;
    printf("Enter IP header information in 16 bit words\n:");

    for(i=0;i<9;i++){
        printf("Field %d\n",i+1);
        scanf("%x",&fields[i]);

        sum=sum+(unsigned short)fields[i];

        while(sum>>16)
        sum=(sum&0xFFFF)+(sum>>16);

    }
    sum=~sum;
    return (unsigned short)sum;
}

int main(){
    unsigned senderfields[10],recvfields[10];
    unsigned short result1,result2;
    //sender msg
    printf("Sender:\n");
    result1=checksum(senderfields);
    printf("Computed checksum @ sender: %x\n",result1);


    printf("Receiver:\n");
    result2=checksum(recvfields);

    printf("Computed checksum @ reciever: %x\n",result2);

    if(result1==result2){
        printf("No error detected\n");
    }
    else{
        fprintf(stderr,"Error detected\n");
    }
}