;file AllCommands.as
mov r1,r2
cmp r1,r2
add r1,r2
sub r1,r2
lea go,r1
clr r1
not r1
inc r1
dec r1
go: jmp go
bne *r1
red r1
prn r1
jsr *r1
rts
stop
