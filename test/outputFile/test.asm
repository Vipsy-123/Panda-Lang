global _main
_main:
	mov rax, 25
	push rdi 
	mov rax, 0x2000001
	pop rdi
	syscall
	mov rax, 0x2000001
	mov rdi, 0
	syscall
