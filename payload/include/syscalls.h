#ifndef SMELLCODE_SYSCALLS_H
#define SMELLCODE_SYSCALLS_H

#include <stddef.h>
#include <stdio.h>

#define SYS_write 1

static inline long raw_syscall(
    long number, 
    unsigned long a1,
    unsigned long a2,
    unsigned long a3,
    unsigned long a4,
    unsigned long a5,
    unsigned long a6
) {
    register long rax __asm__("rax") = number;
    register long rdi __asm__("rdi") = (long)a1;
    register long rsi __asm__("rsi") = (long)a2;
    register long rdx __asm__("rdx") = (long)a3;
    register long r10 __asm__("r10") = (long)a4;
    register long r8 __asm__("r8") = (long)a5;
    register long r9 __asm__("r9") = (long)a6;
    
    long ret;
    __asm__ volatile (
        "syscall"
        : "=a"(ret)
        :  "r"(rax), "r"(rdi), "r"(rsi), "r"(rdx), "r"(r10), "r"(r8), "r"(r9)
        : "rcx", "r11", "memory"
    );
    
    return ret;
}

static inline int is_err(long ret)
{
    return (unsigned long)ret >= (unsigned long)-4096UL;
}

static inline long write(int fd, const void *buf, size_t n)
{
    return raw_syscall(SYS_write, (unsigned long)fd, (unsigned long)buf, n, 0, 0, 0);
}

#endif