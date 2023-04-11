#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void usage(void) {
    char buffer[1024];
    int len = sprintf(buffer, "Usage:\n\n  HOST > ./tres-en-raya -h [PORT]\nCLIENT > ./tres-en-raya -c IP PORT\n");
    write(1, buffer, len);
    exit(1);
}

void die(const char *msg) {
    perror(msg);
    exit(1);
}

char *getip() {
    int fd[2];
    if (pipe(fd) < 0) die("ERROR: Failed to create pipe.\n");
    
    int ret;
    if ((ret = fork()) < 0) die("ERROR: Failed to fork.\n");
    if (ret == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("curl", "curl", "-s", "ifconfig.co", NULL);
        die("ERROR: Failed to mutate.\n");
    }

    close(fd[1]);
    char buffer[256];
    int len = read(fd[0], buffer, sizeof(buffer));
    if (len < 0) die("ERROR: Failed to read from pipe.\n");
    close(fd[0]);

    char *ip = malloc(len * sizeof(char));
    if (ip == NULL) die("ERROR: Failed allocate memory.\n");
    strcpy(ip, buffer);
    return ip;
}

int main(int argc, char *argv[]) {
    char *ip, *port;

    if (argc < 2) usage();
    
    if (strcmp(argv[1], "-c") == 0) {
        if (argc != 4) usage();
        ip = argv[2];
        port = argv[3];
        execlp("./client", "./client", ip, port, NULL);
        die("ERROR: Failed to mutate.\n");
    }
    else if (strcmp(argv[1], "-h") == 0) {
        ip = getip();
        if (argc == 3) port = argv[2];
        else port = "8000"; // random?
        execlp("./server", "./server", ip, port, NULL);
        die("ERROR: Failed to mutate.\n");
    }
    
    usage();
    return 0;
}
