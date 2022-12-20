#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>


#define FIFO_NAME "haha"

int main()
{

  time_t begin = time(NULL);
  int maxlen = 5;
  int stringNum = 50;
  int group = 5;
  char *strings[stringNum];
  char buf[maxlen];
  int hx[10];

  int acknowledged_id = -1;

  printf("Generating random strings.......\n");
  for (int i = 0; i < stringNum; i++)
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
  int j = 0;
  int temp = 0;
  while (j < stringNum)
  {

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

  printf("Files sent to fifo successfully!\n");
  close(fd);
  printf("File descriptor closed for program P1");

  time_t end = time(NULL);
  printf("Elapsed time is %d seconds.\n",(end-begin));

  return 0;
}