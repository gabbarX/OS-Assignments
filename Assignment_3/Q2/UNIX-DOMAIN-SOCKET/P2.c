#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


#define MAX_STR_LEN 5  // maximum length of each string
#define NUM_STRINGS 5   // number of strings to receive at a time
#define SOCKET_NAME "/tmp/socket1"  // name of the unix domain socket

int main()
{

    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error binding socket to name");
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        perror("Error listening for incoming connections");
        exit(1);
    }

    int clientfd = accept(sockfd, NULL, NULL);
    if (clientfd < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    while (1) {
        int highest_id = -1; 

        for (int i = 0; i < NUM_STRINGS; i++) 
        {
            int id;
            if (read(clientfd, &id, sizeof(id)) < 0) {
                perror("Error receiving ID");
                exit(1);
            }


            char str[MAX_STR_LEN];
            if (read(clientfd, str, MAX_STR_LEN) < 0) {
                perror("Error receiving string");
                exit(1);
            }

            printf("ID: %d, String: %s\n", id, str);

            if (id > highest_id) {
                highest_id = id;
            }
        }

        if (write(clientfd, &highest_id, sizeof(highest_id)) < 0) {
            perror("Error sending highest ID");
            exit(1);
        }
    }

    close(clientfd);
    close(sockfd);

    return 0;
}
