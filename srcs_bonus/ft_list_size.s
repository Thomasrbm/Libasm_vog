section .text
	global ft_list_size

ft_list_size:
	xor rax, rax


.size:
	test rdi, rdi
	jz .end

	inc rax
	mov rdi, [rdi + 8]

	jmp .size

.end:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits