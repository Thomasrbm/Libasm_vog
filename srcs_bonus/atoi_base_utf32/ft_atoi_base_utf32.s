extern ft_base_strlen_check
extern ft_is_base_dups
extern ft_find_char_index

section .text
    global ft_atoi_base_utf32

ft_atoi_base_utf32:
    push    r12

    mov     r8, rdi
    mov     r9, rsi
    xor     r12, r12

    call    ft_base_strlen_check    ; return la taille et check cette taille
    test    rax, rax
    jz      .done

    mov     r10, rax

    call    ft_is_base_dups
    test    rax, rax
    jz      .done

    mov     r11, 1






; PAS EXTERN car maj des truc important pour ici semblait plus clair a garder


.next:
    mov     eax, [r8]               ; (4 bytes)
    cmp     rax, ' '
    je      .skip
    cmp     rax, 9
    jb      .sign_check             ;  below
    cmp     rax, 13
    ja      .sign_check             ;  above

.skip:
    add     r8, 4               
    jmp     .next

.sign_check:
    cmp     rax, '-'
    je      .minus

    cmp     rax, '+'
    jne     .loop                   ;   c est un char on rentre dans loo

    add     r8, 4                   ; sinon skip
    jmp     .next

.minus:
    neg     r11
    add     r8, 4                   ; avance au char suivant
    jmp     .next                   ; reboucle







.loop:
    mov     eax, [r8]               ; lit 4 bytes avec eax

    test    rax, rax
    jz      .apply_sign             ;  FINI DONC END

    mov     rdi, r9                 ; arg1 = base ptr
    mov     rsi, r10                ; arg2 = base_len
    mov     rdx, rax                ; arg3 = char à chercher

    call    ft_find_char_index
    cmp     rax, -1
    je      .apply_sign             ; pas dans la base → stop la 

    imul    r12, r10                ; result = result * base_len
    add     r12, rax                ; result += index
   
    add     r8, 4                   ; avance au char suivant
    jmp     .loop                   ; reboucle

.apply_sign:
    imul    r12, r11                ; result * signe (1 ou -1)

.done:
    mov     rax, r12                ; met le résultat dans rax (valeur de retour)
    pop     r12                     ; restaure r12 (callee-saved)
    ret                             ; retourne

section .note.GNU-stack noalloc noexec nowrite progbits