#include "syscalls.h"
#include <string.h>

int main() {
    char* message = "Stinky smellcode!\n";
    write(1, message, strlen(message));
}