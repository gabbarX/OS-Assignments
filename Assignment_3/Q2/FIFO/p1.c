#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#define FIFO_NAME "haha"

int main()
{

  int maxlen = 5;
  int StringNum = 50;
  int group = 5;
  char *strings[StringNum];
  char buf[maxlen];

  int acknowledged_id = -1;

  printf("Generating random strings.......\n");
  for (int i = 0; i < StringNum; i++)
  {
    strings[i] = malloc(maxlen + 1);
    for (int j = 0; j < maxlen; j++)
    {
      strings[i][j] = 'a' + (rand() % 26);
    }
    strings[i][maxlen] = '\0';
  }
  printf("Generation of random strings completed.\n");

  printf("Trying to access fifo named %s in the memory!\n",FIFO_NAME);
  if (access(FIFO_NAME, F_OK) == -1)
  {
    printf("Fifo %s does not exists in the memory!\n", FIFO_NAME);
    printf("Now, Creating fifo %s in the memory!\n", FIFO_NAME);
    if (mkfifo(FIFO_NAME, 0666) < 0)
    {
      perror("mkfifo");
      exit(1);
    }
    else{
      printf("FIFO created successfully!\n");
    }
  }
  else{
    printf("Fifo already exists.\n");
  }

  printf("Opening fifo in write only mode!\n");
  int fd = open(FIFO_NAME, O_WRONLY);
  // printf("%d --- fd,",&fd);
  if (fd < 0)
  {
      perror("open");
      exit(1);
  }
  else{
      printf("Successfully opened the fifo '%s'!\n",FIFO_NAME);
  }

  printf("Sending strings to fifo!\n");
  int k = 0;
  while (k < StringNum)
  {

    for (int j = 0; j < group && k < StringNum; j++, k++)
    {
      sprintf(buf, "%s",strings[k]);
      write(fd, buf, strlen(buf));
    }

    int num_read = read(fd, buf, maxlen);
    buf[num_read] = '\0';
    sscanf(buf, "%d", &acknowledged_id);
  }

  printf("Files sent to fifo successfully!\n");
  close(fd);
  printf("File descriptor closed for program P1");
  return 0;
}