#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "haha"
#define NUM_STRINGS 50
#define STRING_LEN 10
#define GROUP_SIZE 5

// Generate a random string of specified length
char* generateRandomString(int len) 
{
  char* str = malloc(len + 1);
  for (int i = 0; i < len; i++) {
    str[i] = 'a' + (rand() % 26);
  }
  str[len] = '\0';
  return str;
}

int main() {

  //Array for storing random Strings
  char *randomStrings[50];
  
  // Create the FIFO if it doesn't already exist
  printf("Creating FIFO!\n");
  mkfifo(FIFO_NAME, 0666);
  printf("FIFO initialised correctly!\n");

  // Open the FIFO for writing
  int fifo_fd = open(FIFO_NAME, O_WRONLY);
  if (fifo_fd < 0) {
    perror("Error opening FIFO for writing");
    return 1;
  }
  else{
    printf("FIFO opened for writing!\n");
  }

  printf("Generating array of random strings!\n");
  // Generate the array of random strings
  for(int i = 0; i<50; i++){
    randomStrings[i] = generateRandomString(5);
  }
  printf("Random strings generated!");

  for(int i=0;i<50;i++){
    puts(randomStrings[i]);
  }

  
  // char** strings = malloc(NUM_STRINGS * sizeof(char*));
  // for (int i = 0; i < NUM_STRINGS; i++) {
  //   strings[i] = generate_random_string(STRING_LEN);
  // }

  // for(int i=0;i<50;i++){
  //   puts(strings[i]);
  // }

  // int acknowledged_id = -1;
  // int num_sent = 0;
  // while (num_sent < NUM_STRINGS) {
  //   // Send a group of five strings to P2
  //   for (int i = 0; i < GROUP_SIZE; i++) {
  //     int id = acknowledged_id + 1 + i;
  //     if (id >= NUM_STRINGS) {
  //       break;
  //     }

  //     // Write the ID and string to the FIFO
  //     char buffer[STRING_LEN + 1];
  //     sprintf(buffer, "%d %s", id, strings[id]);
  //     if (write(fifo_fd, buffer, strlen(buffer) + 1) < 0) {
  //       perror("Error writing to FIFO");
  //     }
  //     num_sent++;
  //   }

  //   // Read the acknowledged ID from the FIFO
  //   char buffer[10];
  //   if (read(fifo_fd, buffer, 10) < 0) {
  //     perror("Error reading from FIFO");
  //   }
  //   sscanf(buffer, "%d", &acknowledged_id);
  // }

  // // Close the FIFO and free the strings array
  // close(fifo_fd);


  // for (int i = 0; i < NUM_STRINGS; i++) {
  //   free(strings[i]);
  // }
  // free(strings);

  return 0;
}
