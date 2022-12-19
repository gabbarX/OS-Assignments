#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_NAME "/tmp/socket1"

int main() 
{
  int maxlen = 1;
  int stringNum = 50;
  int packetNum = 5;
  int fd;
  struct sockaddr_un server_addr;
  char *strings[stringNum];
  char buf[maxlen];

  fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("Error creating socket");
    exit(1);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strcpy(server_addr.sun_path, SOCKET_NAME);

  if (connect(fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    perror("Error connecting to server");
    exit(1);
  }

//generating string
  for (int i = 0; i < stringNum; i++)
  {
    strings[i] = malloc(maxlen + 1);
    for (int j = 0; j < maxlen; j++)
    {
      strings[i][j] = 'a' + (rand() % 26);
    }
    strings[i][maxlen] = '\0';
  }


//test string
  // for(int i=0;i<stringNum;i++)
  // {
  //   puts(strings[i]);
  // }

int j=0;
int temp = 0;
int group = 5;
  while (j < stringNum)
  {

    // for (int j = 0; j < group && k < stringNum; j++, k++)
    // {
    //   sprintf(buf, "%s",strings[k]);
    //   write(fd, buf, strlen(buf));
    // }
    for(j=temp;j<group;j++)
    {
      sprintf(buf,"%s",strings[j]);
      write(fd,buf,strlen(buf));
      sleep(1);
    }
    temp = group;
    // hx[j++] = group;
    printf("highest id -> %d\n",group-1);
    group+=5;
  }

  // int next_id = 0;
  // while (next_id < stringNum) 
  // {
  //   for (int i = 0; i < packetNum; i++) {
  //     int id = next_id + i;
  //     if (id >= stringNum) 
  //     {
  //       break;
  //     }
  //     send(fd, &id, sizeof(int), 0);
  //     send(fd, strings[id], maxlen + 1, 0);
  //     // write(fd, strings[id], maxlen + 1);
  //   }

  //   int acknowledged_id;
  //   recv(fd, &acknowledged_id, sizeof(int), 0);
  //   printf("Received acknowledgement for ID %d\n", acknowledged_id);
  //   next_id = acknowledged_id + 1;
  // }

  close(fd);

  return 0;
}
