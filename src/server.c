#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main (int argc, char *argv[]) {
    char buffer[512];
    int len = sprintf(buffer, "SOY EL SERVIDOR. Mi IP es %s y mi PORT es %s\n", argv[1], argv[2]);
    write(1, buffer, len);

    // WORKING PROGRESS

    int server_fd, client_fd;
    struct sockaddr_in address;
    int addr_len = sizeof(address);
    int opt_value[1] = { 1 };

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        die("ERROR: Failed to create a socket.");
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, opt_value, sizeof(opt_value)) < 0) 
        die("ERROR: Failed to specify a socket's behaviour.");
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(argv[2]));

    if (bind(server_fd, (struct sockaddr*)&address, addr_len) < 0)
        die("ERROR: Failed to bind a socket.");

    if (listen(server_fd, 2))
        die("ERROR: Failed to listen.");

    if ((client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addr_len)) < 0)
        die("ERROR: Failed to accept a connection.");
}
