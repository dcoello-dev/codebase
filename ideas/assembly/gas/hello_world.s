# sandbox_idea: assembly/gas
# sandbox_name: hello_world
# sandbox_description: hello world in assembler
# sandbox_env: gas

.section .data
msg:    .asciz "Hello, World!"

.section .text
.globl _start

_start:
    # Write the message to stdout
    movl $4, %eax ; system call (sys write)
    movl $1, %ebx ; file descriptor stdout
    leal msg, %ecx ; message to write
    movl $13, %edx ; messasge lenght
    int $0x80 ; call kernel

    # Terminate the program
    movl $1, %eax ; system call (sys exit)
    xorl %ebx, %ebx 
    int $0x80 ; call kernel
