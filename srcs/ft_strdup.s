extern malloc
extern ft_strcpy
extern ft_strlen

section .text
global ft_strdup

ft_strdup:
    test    rdi, rdi
    jz      .error
    push    rdi                     ; sauvegarde str original
    call    ft_strlen wrt ..plt     ; rax = len
    inc     rax                     ; +1 pour \0
    mov     rdi, rax
    call    malloc wrt ..plt        ; rax = nouveau buffer
    test    rax, rax
    jz      .error_pop
    mov     rdi, rax                ; rdi = dest
    pop     rsi                     ; rsi = src (str original)
    push    rdi                     ; sauvegarde dest avant ft_strcpy
    call    ft_strcpy wrt ..plt
    pop     rax                     ; recupere dest = valeur de retour
    ret

.error_pop:
    pop     rdi                     ; nettoie la pile
.error:
    xor     rax, rax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits