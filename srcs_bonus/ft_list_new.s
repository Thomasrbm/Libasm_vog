extern malloc

section .text
	global ft_list_new

ft_list_new:
    push    rdi                     ; sauvegarde data
    mov     rdi, 16                 ; sizeof(t_list) = 2 * 8
	sub rsp, 8
    call    malloc wrt ..plt
	add rsp, 8
    pop     rdi
    test    rax, rax
    jz      .error
    mov     [rax], rdi              ; node->data = data
    mov     qword [rax + 8], 0     ; node->next = NULL
    ret
.error:
    xor     rax, rax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits