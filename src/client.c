#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int client_fd;
    struct sockaddr_in server_address;
    char buffer[1024];

    // Crear el socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("");

    // Establecer la dirección del servidor
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]); // dirección IP del servidor
    server_address.sin_port = htons(atoi(argv[2]));

    // Conectar al servidor
    if (connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
        die("");
    printf("Conexión establecida.\n");

    // Leer y escribir datos
    while (1) {
        printf("Cliente: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_fd, buffer, sizeof(buffer), 0);
        recv(client_fd, buffer, sizeof(buffer), 0);
        printf("Servidor: %s", buffer);
    }

    // Cerrar el socket
    close(client_fd);

    return 0;
}
