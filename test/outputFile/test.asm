global _main
_main:
	mov rax, 1
	push rax,
	mov rax, 3
	push rax,
	mov rax, 4
	push rax,
	pop rax,
	pop rbx,
	add rax,rbx
	push rax,
	pop rax,
	pop rbx,
	add rax,rbx
	push rax,
	push QWORD[rsp + 0],
	mov rax, 3
	push rax,
	pop rax,
	pop rbx,
	add rax,rbx
	push rax,
	mov rax, 9
	push rax,
	push QWORD[rsp + 8],
	mov rax, 0x2000001
	pop rdi,
	syscall

	mov rax, 0x2000001
	mov rdi, 0
	syscall
