#include "recovery.h"
#include "syscalls.h"
#include "string.h"

void recover() {
    char* message = "Recovered!\n";
    write(1, message, strlen(message));
}