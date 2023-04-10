#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    char buffer[512];
    int len = sprintf(buffer, "SOY EL SERVIDOR. Mi IP es %s y mi PORT es %s\n", argv[1], argv[2]);
    write(1, buffer, len);
}
