.include "./m2560def.inc"
; Start writing from 0x00
.org    0x00
  jmp   main
main:
  ; Mark all DDRB as Inputs
  ; PINs: 50,51,52,53 (bits 3-0)
  ldi   r16,  0x00
  out   DDRB, r16
  ; Mark DDRA as Outputs (Result to 7seg display)
  ; PINs: 29,28,27,26,25,24,23,22
  ldi   r16,  0xFF
  out   DDRA, r16

decod:
  ; Reading input number to decod
  in    r18,  PINB
  ; Clean input
  andi  r18,  0x0F
  ; Comparisons to select
  cpi   r18,  0x00
  breq  n0
  cpi   r18,  0x01
  breq  n1
  cpi   r18,  0x02
  breq  n2
  cpi   r18,  0x03
  breq  n3
  cpi   r18,  0x04
  breq  n4
  cpi   r18,  0x05
  breq  n5
  cpi   r18,  0x06
  breq  n6
  cpi   r18,  0x07
  breq  n7
  cpi   r18,  0x08
  breq  n8
  cpi   r18,  0x09
  breq  n9
  cpi   r18,  0x0A
  breq  n10
  cpi   r18,  0x0B
  breq  n11
  cpi   r18,  0x0C
  breq  n12
  cpi   r18,  0x0D
  breq  n13
  cpi   r18,  0x0E
  breq  n14
  cpi   r18,  0x0F
  breq  n15

n0:
  ldi   r16,  0x7E
  jmp   output
n1:
  ldi   r16,  0x30
  jmp   output
n2:
  ldi   r16,  0x6D
  jmp   output
n3:
  ldi   r16,  0x79
  jmp   output
n4:
  ldi   r16,  0x33
  jmp   output
n5:
  ldi   r16,  0x5B
  jmp   output
n6:
  ldi   r16,  0x5F
  jmp   output
n7:
  ldi   r16,  0x70
  jmp   output
n8:
  ldi   r16,  0x7F
  jmp   output
n9:
  ldi   r16,  0x73
  jmp   output
n10:
  ldi   r16,  0x77
  jmp   output
n11:
  ldi   r16,  0x1F
  jmp   output
n12:
  ldi   r16,  0x4E
  jmp   output
n13:
  ldi   r16,  0x3D
  jmp   output
n14:
  ldi   r16,  0x4F
  jmp   output
n15:
  ldi   r16,  0x47
  jmp   output

output:
  out   PORTA,r16
  ; Infinite loop
  jmp decod
