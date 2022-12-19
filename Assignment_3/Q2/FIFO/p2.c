#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#define FIFO_NAME "haha"
#define STRING_LEN 5
   
int main() 
{
  int fd = open(FIFO_NAME, O_RDONLY);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  int highest_id = -1;
  while (true) 
  {
    char buffer[STRING_LEN];
    int id;
    while (read(fd, buffer, STRING_LEN) > 0) 
    {
      sscanf(buffer, "%d %s", &id, buffer);
      printf("Received string with ID %d: %s\n", id, buffer);
      if (id > highest_id) 
      {
        highest_id = id;
      }
      id++;
    }
    return 0;
  }

  close(fd);

  return 0;
}
