#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    char buffer[512];
    int len = sprintf(buffer, "SOY EL CLIENTE. La IP del servidor es %s y el PORT es %s\n", argv[1], argv[2]);
    write(1, buffer, len);
}
