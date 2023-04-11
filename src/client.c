#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main (int argc, char *argv[]) {
    char buffer[512];
    int len = sprintf(buffer, "SOY EL CLIENTE. La IP del servidor es %s y el PORT es %s\n", argv[1], argv[2]);
    write(1, buffer, len);

    // WORKING ON

    int client_fd;
    struct sockaddr_in address;
    int addr_len = sizeof(address);
    int opt_value[1] = { 1 };

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        die("ERROR: Failed to create a socket.");
    
    if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, opt_value, sizeof(opt_value)) < 0) 
        die("ERROR: Failed to specify a socket's behaviour.");
    
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &address.sin_addr) <= 0)
        die("");
  
    if (connect(client_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
        die("");

    while (1) {
        int cont = read(client_fd, buffer, sizeof(buffer));
        if (cont < 0) die();
        write(1, buffer, cont);
        close(client_fd);
    }
}
