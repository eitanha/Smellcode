#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char ** argv) {
    if (argc != 2) {
        return 1;
    }

    int shellcode_fd = open(argv[1], 0);
    if (shellcode_fd == -1) {
        return 1;
    }

    struct stat shellcode_stat;
    if (fstat(shellcode_fd, &shellcode_stat)) {
        return 1;
    }
    
    size_t shellcode_size = (size_t)shellcode_stat.st_size;
    void* shellcode_buffer = mmap(
        NULL,
        shellcode_size,
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_PRIVATE,
        shellcode_fd, 0
    );

    if (shellcode_buffer == MAP_FAILED) {
        return 1;
    }

    int (*shellcode)() = (int (*)())shellcode_buffer;
    return shellcode();
}