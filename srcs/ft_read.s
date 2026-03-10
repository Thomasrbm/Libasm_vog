extern __errno_location

section .text
	global ft_read

ft_read:
	mov rax, 0
	syscall

	cmp rax, 0
	jl .error

	ret

.error:
	neg rax
	push rax
	sub rsp, 8
	call __errno_location wrt ..plt
	add rsp, 8
	pop r10
	mov [rax], r10
	mov rax, -1
	ret


section .note.GNU-stack noalloc noexec nowrite progbits