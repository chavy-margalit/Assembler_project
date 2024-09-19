.entry LENGTH 
.extern W 
jmp 
mcar m1 
MAIN: mov #78, r0 
BB: .string "Bvu" 
endmacr mov 
LOOP: jmp L1(#-1,r6) 
prn #-5 
bne W(r4,#89) 
sub r1, r4 
macr jmp 
bne L3 
endmacr 
L1: inc K 
.entry LOOP 
bne LOOP(K,W) 
inc r6 
END: stop 
m1 
jsr K(r1,#-78) 
STR: .string "ttalaksghdfkajhds" 
LENGTH: .data 6,-9, 15 
K: .data 22 
.extern L3 
macr m2 B 
.entry BB 
endmacr 
Main: mov #5, BB 
