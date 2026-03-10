%include "t_list.inc"





section .text
    global ft_list_remove_if

; FREE VA MODIF les registres DONC push et pop

ft_list_remove_if:
    push    r12
    push    r13
    push    r14
    push    r15

    mov     r12, rdi        ; r12 = curseur    ======>   &begin  puis changera. ne serait plus dutout begin. mais touchera pas a begin, on recoit son adresse pas begin lui meme.  si on envoyait begin on aurait donc ca valeur CAD l adresse du premier noeud.
    mov     r13, rsi        ; r13 = data_ref
    mov     r14, rdx        ; r14 = cmp
    mov     r15, rcx        ; r15 = free_fct

    test    r12, r12
    jz      .ret

.loop:
    mov     rax, [r12]              ; rax = noeud courant (*r12, ce que r12 pointe)
  
    test    rax, rax                ; est-ce que le noeud est NULL ?
    jz      .ret                    ; oui → fin de liste, on sort

    mov     rdi, [rax + t_list.data]    ; rdi = noeud->data (1er arg pour cmp)
    mov     rsi, r13                ; rsi = data_ref (2e arg pour cmp)

    call    r14                     ; cmp(noeud->data, data_ref) → resultat dans rax

    test    rax, rax                ; est-ce que cmp a retourné 0 ?
    jnz     .next                ; != 0 → pas de match → on avance  



; RE MOVE DANS RAX CAR CALL R14, modif rax 

; pointeur vers adresse de begin.  dereference = 1rst  node.
; next node
; begin pointe vers next node
; on free l autre.

.remove:
    mov     rax, [r12]              ; rax = noeud a supprimer (si premier node va supprimer premier et pointer begin vers 2e)
    mov     rdx, [rax + t_list.next]    ; rcx = noeud->next (le suivant)
    mov     [r12], rdx              ; *r12 = noeud->next → court-circuite le noeud (si r12=&begin alors begin change, sinon c est prev->next qui change)
  
    mov     rdi, rax                ; rdi = noeud a liberer (arg pour free)
    call    r15                     ; free(noeud)

    jmp     .loop                   ; r12 n a pas bougé → on relit [r12] qui pointe maintenant sur le suivant



.next:
    mov     rax, [r12]              ; rax = noeud courant (r12 change d adresse)
    lea     r12, [rax + t_list.next]; r12 = &noeud->next → r12 avance vers le champ next du noeud courant
    jmp     .loop                   ; on repart au debut de la boucle



.ret:
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    ret

section .note.GNU-stack noalloc noexec nowrite progbits