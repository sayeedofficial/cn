
//fifo  server


#include<stdio.h>
#include<signal.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
//#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
#define FIFO1 "fifo.1"
#define FIFO2 "fifo.2"
#define MAXLINE 4096

void server(int readfd,int writefd)
{
int fd;
ssize_t n;
char buf[MAXLINE+1];

printf("\nreading from pipe the filename ");

//if((n=read(readfd,buf,MAXLINE))==0)
//printf("end of file while reading the pathname");
n=read(readfd,buf,MAXLINE);
buf[n]='\0';

printf("  %s  ",buf);
 /*if((fd=open(buf,O_RDONLY))<0)
{
//snprintf(buf+n,sizeof(buf)-n,"cant open %s\n",strerror(errno));
strcpy(buf,"SERVER ERROR");
n=strlen(buf);
write(writefd,buf,n);
}
else
{ */

fd=open(buf,O_RDONLY);
printf("\nreading from pipe the contents of the file and writing to client");

while((n=read(fd,buf,MAXLINE))>0)
{
write(writefd,buf,n);
write(STDOUT_FILENO,buf,n);
}
close(fd);
//}
}



int main(int argc,char** argv)
{
int readfd,writefd;
printf("\ncreating pipe1");

   mkfifo(FIFO1, 0666);
   mkfifo(FIFO2, 0666);

/*if((mkfifo(FIFO1,FILE_MODE)<0)&&(errno!=EEXIST))
printf("cant create %s\n",FIFO1);
printf("\ncreating pipe2");

if((mkfifo(FIFO2,FILE_MODE)<0)&&(errno!=EEXIST))
{
//unlink(FIFO1);
printf("cant create %s\n",FIFO2);
} */
readfd=open(FIFO1,O_RDONLY,0);
writefd=open(FIFO2,O_WRONLY,0);
server(readfd,writefd);
_exit(0);
}
