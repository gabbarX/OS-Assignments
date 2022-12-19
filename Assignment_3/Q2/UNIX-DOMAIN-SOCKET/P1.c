#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_NAME "/tmp/socket"
#define MAX_STR_LEN 10
#define NUM_STRINGS 50
#define STRINGS_PER_PACKET 5

int main(int argc, char** argv) {
  int sockfd;
  struct sockaddr_un server_addr;

  // Create socket
  sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Error creating socket");
    exit(1);
  }

  // Set up server address
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strcpy(server_addr.sun_path, SOCKET_NAME);

  // Connect to server
  if (connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    perror("Error connecting to server");
    exit(1);
  }

  // Generate array of random strings
  char strings[NUM_STRINGS][MAX_STR_LEN + 1];
  for (int i = 0; i < NUM_STRINGS; i++) {
    for (int j = 0; j < MAX_STR_LEN; j++) {
      strings[i][j] = 'A' + rand() % 26;
    }
    strings[i][MAX_STR_LEN] = '\0';
  }

  int next_id = 0;
  while (next_id < NUM_STRINGS) {
    // Send a group of five strings to the server
    for (int i = 0; i < STRINGS_PER_PACKET; i++) {
      int id = next_id + i;
      if (id >= NUM_STRINGS) 
      {
        break;
      }
      send(sockfd, &id, sizeof(int), 0);
      send(sockfd, strings[id], MAX_STR_LEN + 1, 0);
    }

    // Wait for acknowledgement from the server
    int acknowledged_id;
    recv(sockfd, &acknowledged_id, sizeof(int), 0);
    printf("Received acknowledgement for ID %d\n", acknowledged_id);
    next_id = acknowledged_id + 1;
  }

  close(sockfd);

  return 0;
}
