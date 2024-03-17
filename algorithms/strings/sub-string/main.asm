; Sub-String finder in x86 assembly
; Author: Hossein Khosravi

; nasm -felf64 substr.asm
; ld substr.o

section .text
global _start


substr_found:
    ; Args:
    ;   rdi -> main string
    ;   rsi -> query string
    ;
    ; return -> rax
    push    rbp
    mov     rbp, rsp
    sub     rsp, 8

    mov     [rsp-8], rsi

    jmp     .L1
.L0:
    inc     rdi
.L1:
    cmp     byte[rdi], 0
    je      .ret0
    mov     al, byte[rdi]
    mov     dl, byte[rsi]
    cmp     al, dl
    jne     .L0
    jmp     .L3
.L2:
    inc     rdi
    inc     rsi
.L3:
    cmp     byte[rsi], 0
    je      .ret1
    cmp     byte[rdi], 0
    je      .ret0
    mov     al, byte[rdi]
    mov     dl, byte[rsi]
    cmp     al, dl
    je      .L2
    mov     rsi, [rsp-8]
    jne     .L1
.ret0:
    mov     rax, 0
    jmp     .ret
.ret1:
    mov     rax, 1
.ret:
    leave
    ret


_start:
    mov     rdi, string
    mov     rsi, query
    call    substr_found
    mov     r12, rax

    ; show the result of `substr_found`
    ; in the program exit code.
    ; check with `echo $?` command.
    mov     rax, 60
    mov     rdi, r12
    syscall


section .data
string db "Hello (Assem) From Assembly!", 0x0
query  db "Assembly!", 0x0
