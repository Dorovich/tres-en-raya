#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void usage(void) {
    // modo de uso
}

void die(const char *msg) {
    perror(msg);
    exit(1);
}

char *getip() {
    int fd[2];
    if (pipe(fd) < 0) die("PIPE ERROR\n");
    
    if (fork() == 0) {
        close(fd[1]);
        dup2(fd[0], STDOUT_FILENO);
        close(fd[0]);
        execlp("curl", "curl", "-s", "ifconfig.co", NULL);
        die("FORK ERROR\n");
    }

    close(fd[0]);
    char buffer[256];
    int len = read(fd[1], buffer, sizeof(buffer));
    if (len < 0) die("READ FAIL\n");
    close(fd[1]);

    char *ip = malloc(len);
    strcpy(ip, buffer);
    return ip;
}

int main(int argc, char *argv[]) {
    /*
    char *ip, *port;

    if (argc < 2) usage();
    
    if (strcmp(argv[1], "-c") == 0) {
        if (argc != 4) usage();
        ip = argv[2];
        port = argv[3];
        execlp("./client", "./client", ip, port, NULL);
        exit(1);
    }
    else if (strcmp(argv[1], "-h") == 0) {
        if (fork() == 0) {
            execlp("./server", "./server", NULL);
            exit(1);
        }
        execlp("./client", "./client", NULL);
        exit(1);
    }
    
    usage();
    return 0;
    */

    char *ip = getip();
    printf("la ip es: %s\n", ip);
    free(ip);
}