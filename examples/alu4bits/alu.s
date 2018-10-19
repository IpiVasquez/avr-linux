.include "./m2560def.inc"
; Start writing from 0x00
.org    0x00
  jmp   main
main:
  ; Mark all DDRB as Inputs
  ; PINs: 13,12,11,10,50,51,52,53
  ldi   r16,  0x00
  out   DDRB, r16
  ; Mark last 3 DDRC as Inputs (Selection)
  ; PINs: 35,36,37
  ldi   r16,  0x07
  out   DDRC, r16
  ; Mark DDRA as Outputs (Result)
  ; PINs: 29,28,27,26,25,24,23,22
  ldi   r16,  0xFF
  out   DDRA, r16
  ; DDRB will hold both operands
  ; DDRC will hold outputs
  ; DDRC will hold operation select
alu_op:
  ; ALU Operation
  in    r16,  PINB ; Read Input numbers, should be: BBBBAAAA
  ; Separate inputs
  mov   r17,  r16
  andi  r16,  0x0F  ; Number A
  andi  r17,  0xF0  ; Number B
  lsr   r17
  lsr   r17
  lsr   r17
  lsr   r17         ; 4 right bit shifts
  ; Operation
  in    r18,  PINC
  andi  r18,  0x07
  ; ldi   r18,  0x02 ; Dummy
  ; Comparisons to select
  cpi   r18,  0x00
  breq  addition
  cpi   r18,  0x01
  breq  substraction
  cpi   r18,  0x02
  breq  multiplication
  cpi   r18,  0x03
  breq  land
  cpi   r18,  0x04
  breq  lor
  jmp   else

addition:
  add   r16,  r17
  mov   r18,  r16   ; Directly to output
  jmp   output
substraction:
  sub   r16,  r17
  mov   r18,  r16   ; Directly to output
  jmp   output
multiplication:
  mul   r16,  r17
  mov   r18,  r0    ; Directly to output
  jmp   output
land:
  and   r16,  r17
  mov   r18,  r16   ; Directly to output
  jmp   output
lor:
  or    r16,  r17
  mov   r18,  r16   ; Directly to output
  jmp   output
else:
  andi  r18,  0x00

output:
  out   PORTA,r18
  ; Infinite loop
  jmp alu_op
