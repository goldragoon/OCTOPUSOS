;Last modified 2014-1-3
;Creater Choi gue jin

[org 0x00]                      ;start address 0x00
[bits 16]                       ;this code will be 16bit

SECTION .text                   ;text section(segment)

jmp 0x07C0:START                ;this area should be boot code!!

TOTALSECTORCOUNT: dw 1024

START:
    mov ax, 0x07C0
    mov ds, ax                  ;code, data segment
    mov ax, 0xB800
    mov es, ax                  ;to draw console
    mov si, 0

    mov ax, 0x0000
    mov ss, ax
    mov sp, 0xFFFE
    mov bp, 0xFFFE

.SCREENCLEARLOOP:              ; start SCREENCLEARLOOP
    mov byte [es:si], 0
    mov byte [es:si+1],0x0A
    
    add si, 2
    cmp si, 80 * 25 * 2
    jl .SCREENCLEARLOOP         ; END   SCREENCLEARLOOP

    mov si, 0
    mov di, 0

push MESSAGE1
push 0
push 3
call PRINTMESSAGE
add sp, 6

RESETDISK:
    mov ax, 0
    mov dl, 0
    int 0x13
    jc HANDLEERROR
    
    mov si, 0x1000
    mov es, si
    mov bx, 0x0000
    mov di, word [TOTALSECTORCOUNT]
READDATA:

    cmp di, 0
    je READEND
    sub di, 0x1

    mov ah, 0x02
    mov al, 0x1
    mov ch, byte[TRACKNUMBER]
    mov cl, byte[SECTORNUMBER]
    mov dh, byte[HEADNUMBER]
    mov dl, 0x00
    int 0x13
    jc HANDLEERROR

    add si, 0x0020
    mov es, si
    mov al, byte[SECTORNUMBER]
    add al, 0x01
    mov byte[SECTORNUMBER], al
    cmp al, 19
    jl READDATA

    xor byte[HEADNUMBER], 0x01
    mov byte[SECTORNUMBER], 0x01

    cmp byte[HEADNUMBER], 0x00
    jne READDATA

    add byte[TRACKNUMBER], 0x01
    jmp READDATA
READEND:
    push MESSAGELOADED
    push 1
    push 0
    call PRINTMESSAGE
    add sp, 6

    jmp 0x1000:0000
     

HANDLEERROR:
    push MESSAGEERROR
    push 1
    push 0
    call PRINTMESSAGE
    add sp, 6 

jmp $                           ;infinite loop for this line

PRINTMESSAGE:

    push bp
    mov bp, sp
    pushad 


    mov ax, 0xB800
    mov es, ax

   
    mov ax, word[bp+6]
    mov si, 160
    mul si
    mov di, ax

    mov ax, word[bp+4]
    mov si, 2
    mul si
    add di, ax

    mov si, word[bp+8]

.MESSAGELOOP:
    mov cl, byte[si]
    
  
    cmp cl, 0
    je .MESSAGEEND
    
    mov byte [es:di], cl
    add si, 1
    add di, 2
    
    jmp .MESSAGELOOP
.MESSAGEEND:
    
    popad
    pop bp
    ret


MESSAGE1: db 'OCTOPUS_OS IS COMMING..', 0
MESSAGEERROR: db 'ERROR_IS_OCCURRED', 0
MESSAGELOADED: db 'OCTOPUS_OS LOADED', 0

SECTORNUMBER: db 0x02 
HEADNUMBER: db 0x00
TRACKNUMBER: db 0x00
times 510 - ( $ - $$ ) db 0x00  ;$ - the address for this line
                                ;$$ - current section start address
                                ;$ - $$ the offset which start with current section
                                ;fill with 0x00 current location to address 510

db 0x55
db 0xAA
