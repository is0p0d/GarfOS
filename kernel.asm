;kernel.asm
;Jim Moroney
;due: 09.16.22
;HW1 - CSC4100

GLOBAL k_hidecursor
GLOBAL k_printstr
GLOBAL k_clearscr

GLOBAL go
GLOBAL go_rest
GLOBAL dispatch
GLOBAL dispatch_leave
GLOBAL yield

GLOBAL init_timer_dev
GLOBAL outportb

EXTERN dequeue
EXTERN enqueue
EXTERN makeNode
EXTERN currProDeq
EXTERN currProEnq

;variables
EXTERN PCBqueue
EXTERN currProcess

; with heavy hand this rock was clove from terra firma
; formed with presses, molded with hands guided by wisdom divine
; endued with the might of lightning, and inscribed with runes
; revealed to the heavens, praised among mortals, i386

; through these runes i shall cast spells in its arcane tongue
; with careful words and billowing commands
; this computing golem shall do as I say:

k_printstr:
    ;routine for moving a given 0-terminated string to video memory
    ;sub-routines are indicated by starting a routine name with an underscore (_)
    
    ;push all general purpose registers and flags
    push ebp
    ;moving stack pointer ontop ebp for arguments passed from C
    mov ebp, esp
    pushf
    push eax
    push edx
    push edi
    push esi

    ;position calculation equation
    ;(offset = ((row * 80) + col) * 2)
    mov eax, [ebp+12]   ;move 2nd var (row) into accumulator
    mov edx, [ebp+16]   ;move 3rd var (col) into data register
    imul eax, 80        ;(row * 80)
    add eax, edx        ;(row * 80) + col
    imul eax, 2         ;((row * 80) + col) * 2
                        ;offset is now in eax
    add eax, 0xB8000    ;add the beginning of the ISA hole to the offset
    mov edi, eax        ;move into destination index for movsb

    ;starting the print
    mov esi, [ebp+8]    ;move 1st var (address of string) into source index


_contPrint:
    ;loop for continuous movement of characters into video memory
    ;will continue until [esi] reaches that end of a 0 terminated string
    cmp edi, 0xB8F9E    ;compare edi to end of video mem
    jg _donePrint       ;if we're past video memory, clean up and return

    cmp BYTE [esi], 0       ;compare current byte in esi to 0
    je _donePrint       ;if it hits the end of the string, clean up and return

    movsb
    mov BYTE es:[edi], 06
    inc edi
    jmp _contPrint

_donePrint:              
    pop esi
    pop edi
    pop edx
    pop eax
    popf
    pop ebp
    ;return to main program
    ret

k_clearscr:
    pushad
    pushf
    mov edi, 0xB8000    ;move to the beginning of video memory
    mov ecx, 4000       ;fill the counter with max video mem 80 * 25 * 2
    ;build an empty character byte
    mov al, ' '         ;empty space
    mov ah, 06          ;give it a color, mostly for the background color
    ;writing this character to screen til ecx is 0
    rep stosw
    ;clean up and return
    popf
    popad
    ret

go:
    push PCBqueue       ;push global PCBqueue onto the stack
    call currProDeq
    ;pop dword [currProcess]
go_rest:
    mov esi, [currProcess]
    mov esp, [esi]
    popa
    ret

dispatch:
    call yield
dispatch_leave:
    push eax

    mov al, 0x20
    out 0x20, al
    
    pop eax
    iret

yield:
    pusha
    mov esi, [currProcess]
    mov [esi], esp
    push PCBqueue       ;add the first
    call currProEnq       ;call enqueue
    push PCBqueue  
    call currProDeq

    jmp go_rest

    init_timer_dev:
    push ebp
    mov ebp, esp
    pushf
    push edx
    push eax
    mov edx, [ebp+8]
    imul edx, 1193
    movzx edx, dx

    mov al, 0b00110110
    out 0x43, al
    mov ax, dx
    out 0x40, al
    xchg ah, al
    out 0x40, al
    pop eax 
    pop edx 
    popf
    pop ebp 
    ret

    ; outportb:
    ; pushf
    ; push ebp
    ; mov ebp, esp
    ; push eax
    ; push edx


    ; xor eax, eax
    ; xor edx, edx ;clear register for posterity
    ; mov dx, [ebp+8]
    ; mov al, [ebp+12]
    ; out dx, al

    ; pop edx
    ; pop eax
    ; pop ebp
    ; popf
    ; ret

    
k_hidecursor:
    ;this was a quick attempt to get rid of the bios cursor, it
    ;ended up not working - wanted to ask about it.
    push cx

    mov cx, 2607h       ;move an instruction into cx for the bios
    int 10h

    pop cx