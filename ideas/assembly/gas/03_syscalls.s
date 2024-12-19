# sandbox_idea: assembly/gas
# sandbox_name: 03_syscalls
# sandbox_description: linux sys calls
# sandbox_env: gas

# You can make use of Linux system calls in your assembly programs. You need to take the following steps for using Linux system calls in your program −

#   - Put the system call number in the EAX register.
#   - Store the arguments to the system call in the registers EBX, ECX, etc.
#   - Call the relevant interrupt (80h).
#   - The result is usually returned in the EAX register.

# There are six registers that store the arguments of the system call used. These are the EBX, ECX, EDX, ESI, EDI, and EBP. These registers take the consecutive arguments, starting with the EBX register. If there are more than six arguments, then the memory location of the first argument is stored in the EBX register.

# %eax	Name	%ebx	%ecx	%edx	%esx	%edi
# 1	sys_exit	int	-	-	-	-
# 2	sys_fork	struct pt_regs	-	-	-	-
# 3	sys_read	unsigned int	char *	size_t	-	-
# 4	sys_write	unsigned int	const char *	size_t	-	-
# 5	sys_open	const char *	int	int	-	-
# 6	sys_close	unsigned int	-	-	-	-

.section .text
.globl _start

_start:
    mov     $1, %rax                # system call 1 is write
    mov     $1, %rdi                # file handle 1 is stdout
    mov     $message, %rsi          # address of string to output
    mov     $13, %rdx               # number of bytes
    syscall                         # invoke operating system to do the write

    # exit(0)
    mov     $60, %rax               # system call 60 is exit
    xor     %rdi, %rdi              # we want return code 0
    syscall                         # invoke operating system to exit

message:
    .ascii  "Hello, world\n"
