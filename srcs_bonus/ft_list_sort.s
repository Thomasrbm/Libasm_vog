%include "t_list.inc"

section .text
    global ft_list_sort

ft_list_sort:
    push r12
    push r13
    push r14
    push r15

    test rdi, rdi
    jz .end

    mov r12, rdi
    mov r13, rsi

.restart:
    xor r14, r14
    mov r15, r12

.sort:
    mov rax, [r15]

    mov rdx, [rax + t_list.next]    ; fin de liste
    test rdx, rdx
    jz .check


    mov rdi, [rax + t_list.data]
    mov rsi, [rdx + t_list.data]
    call r13

    jle .next



.swap:
    mov rax, [r15]

    mov rdx, [rax + t_list.next]
    mov rcx, [rdx + t_list.next]

    mov [rax + t_list.next], rcx
    mov [rdx + t_list.next], rax
    mov [r15], rdx
    mov r14, 1
    jmp .sort

.next:
    mov rax, [r15]
    lea r15, [rax + t_list.next]
    jmp .sort

.check:
    test r14, r14
    jnz .restart

.end:
    pop r15
    pop r14
    pop r13
    pop r12
    ret

section .note.GNU-stack noalloc noexec nowrite progbits