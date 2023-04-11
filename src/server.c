#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <ifaddrs.h>

void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int server_fd, client_fd;
    struct sockaddr_in server_address, client_address;
    char buffer[1024];

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("");

    // Establecer la dirección del servidor
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(atoi(argv[2]));

    // ----------------------------------------------------

    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) < 0) die("");

    printf("Direcciones IP disponibles:\n");

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) {
            continue;
        }

        if (ifa->ifa_addr->sa_family == AF_INET) {
            struct sockaddr_in *sa = (struct sockaddr_in*)ifa->ifa_addr;
            printf("%s: %s\n", ifa->ifa_name, inet_ntoa(sa->sin_addr));
        }
    }

    freeifaddrs(ifaddr);

    // ----------------------------------------------------

    // Asignar la dirección al socket
    if (bind(server_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
        die("");

    // Configurar el socket para aceptar conexiones entrantes
    if (listen(server_fd, 1) < 0)
        die("");

    // Esperar a que se conecte un cliente
    printf("Servidor escuchando en la ip %s y en el puerto %d.\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
    if ((client_fd = accept(server_fd, (struct sockaddr*)&client_address, NULL)) < 0)
        die("");
    printf("Cliente conectado.\n");

    // Leer y escribir datos
    while (1) {
        recv(client_fd, buffer, sizeof(buffer), 0);
        printf("Cliente: %s", buffer);
        printf("Servidor: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_fd, buffer, sizeof(buffer), 0);
    }

    // Cerrar los sockets
    close(client_fd);
    close(server_fd);

    return 0;
}