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

    int server_fd;
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) die("ERROR: Failed to create a socket.");
    
    //if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) die("");
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(argv[2]));
}
