section .text
	global ft_strcpy


ft_strcpy:
	xor rax, rax
	xor rcx, rcx

	test rsi, rsi
	jz .end

	mov rax, rdi


.copy:
	mov r11b, [rsi + rcx]
	mov [rax + rcx], r11b
	cmp r11b, 0
	je .end

	inc rcx
	jmp .copy


.end:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits