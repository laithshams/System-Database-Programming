#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#define PORT 8080

struct items
{
    char barcode[15];
    char name[15];
    double price;
    int quantity;
    int line;
};

void *connection_handler(void *nsocket);

struct items *whereItem(char barcode[]);

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("socket has been created\n");
    
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    printf("socket has been attached into port 8080 successfully\n");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("bind successfuly\n");

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("listening...\n");
    
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address,
    (socklen_t*)&addrlen)))
    {
        pthread_t connection;
        if(pthread_create(&connection, NULL, &connection_handler, &new_socket) < 0)
	    {
	        perror("could not create thread");
	        return 1;
	    }
        //pthread_join(connection, NULL);

    }
    return 0;
}

void *connection_handler(void *nsocket)
{
    int *newsocket = (int *) nsocket;
    int new_socket = (int) *newsocket;
    char buffer[15] = {0};
    read( new_socket , buffer, 15);
    buffer[strcspn(buffer, "\n")] = 0;

    struct items *temp = whereItem(buffer);
    if(temp)
    {
        char item[100];
        sprintf(item, "name: %s    price: %.2lf    storage: %d", temp->name, temp->price, temp->quantity);
        write(new_socket, item, strlen(item));
    } else
    {
        char item[] = "item doesn't exist...";
        write(new_socket, item, strlen(item));
    }
}

struct items *whereItem(char barcode[])
{
    struct items *temp;
    
    char cmd[100];
    sprintf(cmd, "./WhereItem.sh %s items.csv", barcode);
    system(cmd);
    
    if(checkIfNull("item.csv") == 1)
    {
        return NULL;
    }

    temp = (struct items*) malloc(sizeof(struct items));
    FILE *fb = fopen("item.csv", "r");
    fscanf(fb, "%d %s %s %lf %d", &temp->line, temp->barcode, temp->name, &temp->price, &temp->quantity);
    fclose(fb);
    system("./WhereItem.sh");
    return temp;
}

int checkIfNull(char file[15])
{
    if(access(file, R_OK))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
