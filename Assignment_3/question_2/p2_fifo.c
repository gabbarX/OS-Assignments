#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "fifo"
#define STRING_LENGTH 10
#define GROUP_SIZE 5

int main() {
int fd, id;
char buffer[GROUP_SIZE][STRING_LENGTH];

// Open the FIFO file for reading
if ((fd = open(FIFO_NAME, O_RDONLY)) < 0) {
perror("Error opening FIFO file");
exit(1);
}
