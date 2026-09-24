#include "syscalls.h"
#include "string.h"
#include "recovery.h"

int main() {
    char* message = "Stinky smellcode!\n";
    write(1, message, strlen(message));
}

int main_with_recovery() {
    main();
    recover();
    return 0;
}
