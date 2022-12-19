#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "haha2"
#define STRING_LEN 10
   
int main() 
{
  int fifo_fd = open(FIFO_NAME, O_RDONLY);
  if (fifo_fd < 0) {
    perror("Error opening FIFO for reading");
    return 1;
  }

  int highest_id = -1;
  while (1) {
 
    char buffer[STRING_LEN + 1];
    int id;
    while (read(fifo_fd, buffer, STRING_LEN + 1) > 0) {
      sscanf(buffer, "%d %s", &id, buffer);
      printf("Received string with ID %d: %s\n", id, buffer);
      if (id > highest_id) {
        highest_id = id;
      }
    }

    char ack_buffer[10];
    sprintf(ack_buffer, "%d", highest_id);
    if (write(fifo_fd, ack_buffer, strlen(ack_buffer) + 1) < 0) {
      perror("Error writing to FIFO");
    }
  }

  close(fifo_fd);

  return 0;
}
