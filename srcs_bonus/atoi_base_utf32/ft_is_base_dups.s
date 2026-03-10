section .text
global ft_is_base_dups

ft_is_base_dups:
    xor     rcx, rcx                ; rcx = i = 0 (index outer)

.outer_boucle:
    cmp     rcx, r10                ; i == base_len ?
    jge     .valid                  ; oui → pas de doublons

    mov     eax, [r9 + rcx*4]      ; eax = base[i]
    mov     rdx, rcx                ; rdx = j = i (j rattrape i)
    inc     rdx                     ; j = i + 1

.inner_boucle:
    cmp     rdx, r10                ; j == base_len ?
    jge     .next_outer                   ; oui → passe au i suivant

    cmp     eax, [r9 + rdx*4]       ; base[i] == base[j] ?
    je      .invalid                ; oui → doublon trouvé

    inc     rdx                     ; j++
    jmp     .inner_boucle           ; reboucle inner

.next_outer:
    inc     rcx                     ; i++
    jmp     .outer_boucle            ; reboucle outer

.valid:
    mov     rax, 1                  ; retourne 1 (pas de doublons)
    ret

.invalid:
    xor     rax, rax                ; retourne 0 (doublon trouvé)
    ret

section .note.GNU-stack noalloc noexec nowrite progbits