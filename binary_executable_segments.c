#include <stdio.h>

// Initialized global variable -> goes to .data segment
int initialized_global = 42;

// Uninitialized global variable -> goes to .bss segment
int uninitialized_global;

// Another uninitialized global array (4000 bytes) -> goes to .bss segment
char large_bss_buffer[4000];

int main() {
    // Local variable -> allocated on the Stack at runtime
    int local_stack_var = 10;

    // String literal -> stored in .rodata / .text (code) segment
    printf("Stack var address: %p\n", (void*)&local_stack_var);

    return 0;
}
