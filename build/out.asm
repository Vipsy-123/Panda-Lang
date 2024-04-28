section .data
    text0:     db ' 1', 10
    textLen0:  equ  $-text0
    text1:     db ' 2', 10
    textLen1:  equ  $-text1
    text2:     db ' 3', 10
    textLen2:  equ  $-text2

section  .text
    global _start
_start:
    ; let
    mov rax, 2
    push rax
    mov rax, 3
    push rax
    mov rax, 2
    push rax
    pop rax
    pop rbx
    mul rbx
    push rax
    mov rax, 10
    push rax
    pop rax
    pop rbx
    sub rax, rbx
    push rax
    pop rax
    pop rbx
    div rbx
    push rax
    ; /let
    ; if
    mov rax, 0
    push rax
    pop rax
    test rax, rax
    jz label0
    mov rax, 1
    push rax
    pop rax
    mov [rsp + 0], rax
    mov rax, 1 
    mov rdi, 1 
    mov rsi, text0
    mov rdx, textLen0
    syscall
    jmp label1
label0:
    ;; elif
    mov rax, 0
    push rax
    pop rax
    test rax, rax
    jz label2
    mov rax, 2
    push rax
    pop rax
    mov [rsp + 0], rax
    mov rax, 1 
    mov rdi, 1 
    mov rsi, text1
    mov rdx, textLen1
    syscall
    jmp label1
label2:
    ;; else
    mov rax, 3
    push rax
    pop rax
    mov [rsp + 0], rax
    mov rax, 1 
    mov rdi, 1 
    mov rsi, text2
    mov rdx, textLen2
    syscall
label1:
    ; /if
    ; exit
    mov rax, 1
    push rax
    push QWORD [rsp + 8]
    pop rax
    pop rbx
    add rax, rbx
    push rax
    mov rax, 60
    pop rdi
    syscall
    ; /exit
    mov rax, 60
    mov rdi, 0
    syscall
