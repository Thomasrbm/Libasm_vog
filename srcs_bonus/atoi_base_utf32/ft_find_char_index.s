section .text
global ft_find_char_index

ft_find_char_index:
    xor     rax, rax

.find:
    cmp     rax, rsi                ; index == base_len ?
    je      .not_found

    cmp     edx, [rdi + rax*4]
    je      .found

    inc     rax
    jmp     .find

.found:
    ret                             ; rax = index, déjà en place

.not_found:
    mov     rax, -1                 ; retourne -1 (pas trouvé)
    ret

section .note.GNU-stack noalloc noexec nowrite progbits