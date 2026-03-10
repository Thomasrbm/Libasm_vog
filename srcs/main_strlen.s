extern ft_strlen
extern printf

section .data
    format db "len = %d", 0
    string db "test", 0

section .text
    global main

main:
    mov rdi, string
    call ft_strlen

    mov rdi, format
    mov rsi, rax
    xor rax, rax
    call printf

    ret 

section .note.GNU-stack noalloc noexec nowrite progbits