global _main
_main:
	mov rax, 10
	push rax,
	mov rax, 20
	push rax,
	push QWORD[rsp + 0],
	mov rax, 0x2000001
	pop rdi,
	syscall
	mov rax, 0x2000001
	mov rdi, 0
	syscall
