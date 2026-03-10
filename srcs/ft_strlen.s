section .text
	global ft_strlen


ft_strlen:
	xor rax, rax

	test rdi, rdi
	jz .end


.count:
	cmp byte [rdi + rax], 0
	je .end

	inc rax
	jmp .count 


.end:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits