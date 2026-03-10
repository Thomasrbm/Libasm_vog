section .text
	global ft_strcmp


ft_strcmp:
	xor rax, rax

	test rdi, rdi
	jz .error

	test rsi, rsi
	jz .error

.compare:
	mov r8b, [rdi + rax]
	mov r9b, [rsi + rax]

	cmp r8b, 0
	je .end

	cmp r9b, 0
	je .end

	cmp r8b, r9b
	jne .end

	inc rax
	jmp .compare


.end:
	movzx rax, r8b
	movzx rcx, r9b
	sub rax, rcx
	ret


.error:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits