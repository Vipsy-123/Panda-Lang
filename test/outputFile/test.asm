global _main
_main:
	mov rax, 3
	push rax,
	mov rax, 1
	push rax,
	mov rax, 1
	push rax,
	push QWORD[rsp + 8],
	pop rax,
	pop rbx,
	sub rax,rbx
	push rax,
	pop rax,
	test rax,rax
	jz label_0
	mov rax, 69
	push rax,
	mov rax, 0x2000001
	pop rdi,
	syscall
	add rsp,0
label_0:
	mov rax, 1
	push rax,
	mov rax, 0x2000001
	pop rdi,
	syscall

	mov rax, 0x2000001
	mov rdi, 0
	syscall
