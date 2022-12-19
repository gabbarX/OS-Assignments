#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_NAME "/tmp/socket1"

int main() 
{
  int maxlen = 5;
  int stringNum = 50;
  int packetNum = 5;

  int sockfd;
  struct sockaddr_un server_addr;

  sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Error creating socket");
    exit(1);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strcpy(server_addr.sun_path, SOCKET_NAME);

  if (connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    perror("Error connecting to server");
    exit(1);
  }

  char strings[stringNum][maxlen + 1];
  for (int i = 0; i < stringNum; i++) {
    for (int j = 0; j < maxlen; j++) {
      strings[i][j] = 'a' + rand() % 26;
    }
    strings[i][maxlen] = '\0';
  }

  int next_id = 0;
  while (next_id < stringNum) 
  {
    for (int i = 0; i < packetNum; i++) {
      int id = next_id + i;
      if (id >= stringNum) 
      {
        break;
      }
      send(sockfd, &id, sizeof(int), 0);
      send(sockfd, strings[id], maxlen + 1, 0);
    }

    int acknowledged_id;
    recv(sockfd, &acknowledged_id, sizeof(int), 0);
    printf("Received acknowledgement for ID %d\n", acknowledged_id);
    next_id = acknowledged_id + 1;
  }

  close(sockfd);

  return 0;
}
