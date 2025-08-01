#include <stdio.h>      //printf, perror
#include <stdlib.h>     //exit
#include <string.h>     //memset, strlen
#include <unistd.h>     //close
#include <sys/types.h>  //socket data types
#include <sys/socket.h> //sockets
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h>  //htons

#define PORT 3030
#define BACKLOG 10
#define MSG "Hello world!\n"

int main(void *args){
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    //create socket IPv4 TCP
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    //bind socket to addr and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port  = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr,
        sizeof(server_addr)) < 0) {
            perror("Binding error");
            exit(EXIT_FAILURE);
    }

    //Listening
    if (listen(server_fd, BACKLOG) < 0){
        perror("Listening error");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", PORT);

    while (1) {
        printf("Waiting for new connection...\n");
        client_fd = accept(server_fd, 
                            (struct sockaddr*)&client_addr,
                            &client_len);
        if (client_fd < 0) {
            perror("Accept error");
            continue;
        }
        printf("Conected client: %s\n", inet_ntoa(client_addr.sin_addr));

        char buffer[1024] = {0};
        read(client_fd, buffer, sizeof(buffer) - 1);
        printf("Request:\n%s\n", buffer);
        char response[] =   "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/html\r\n"
                            "Content-Length: 13\r\n"
                            "\r\n"
                            MSG;
        write(client_fd, response, strlen(response));

        close(client_fd);
    }
    
    close(server_fd);
}

