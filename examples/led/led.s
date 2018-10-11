.include "./m2560def.inc"
; Start writing from 0x00
.org    0x00
  jmp   main
main:
  ldi   r17,  0x80  ; First bit on r17 represents 13th PIN
  ; r17 will also work as bitmask
  out   DDRB, r17   ; Setting PB5 as output
  ldi   r16,  0x80  ; Outputing to PIN 13th

loop:
  eor   r16,  r17   ; XOR should blink only PIN 7
  out   PORTB,r16   ; Updating PIN

delay:
  ; Initializing counters as 0xE00000
  ; The point is to count until the counter becomes 0 (overflow)
  ; By initializing in 0xE00000 overflow is reached earlier
  ; Using only n-bits
  ldi   r18,  0x00
  ldi   r19,  0x00
  ldi   r20,  0xE0

delay_loop:
  ; first byte
  inc   r18
  ; repeats until overflow
  brvs  delay_loop_1
  jmp   delay_loop

delay_loop_1:
  ; second byte
  inc   r19
  ; repeats until overflow
  brvs  delay_loop_2
  jmp   delay_loop

delay_loop_2:
  ; third byte, when this overflows it repeats
  inc   r20
  ; repeats until overflow
  breq  end_delay
  jmp   delay_loop

end_delay:
  ; Blink again
  jmp   loop
