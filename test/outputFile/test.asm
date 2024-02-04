global _main
_main:
	mov rax, 3
	push rax,
	mov rax, 2
	push rax,
	mov rax, 98
	push rax,
	push QWORD[rsp + 0],
	mov rax, 0x2000001
	pop rdi,
	syscall
	add rsp,8
	add rsp,8
	mov rax, 1
	push rax,
	push QWORD[rsp + 0],
	mov rax, 0x2000001
	pop rdi,
	syscall

	mov rax, 0x2000001
	mov rdi, 0
	syscall
