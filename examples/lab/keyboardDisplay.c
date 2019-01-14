#include <avr/io.h>
#include <util/delay.h>

int matrix[][4] = {
    {1, 2, 3, 10}, {4, 5, 6, 11}, {7, 8, 9, 12}, {13, 0, 15, 14}};

int teclado() {
  if (PINC & 0x0F && PINC & 0xF0) {
    short x = 0;
    short y = 0;

    for (int i = 0; i < 4; i++) {
      if (PINC & (1 << i))
        y = i;
      if (PINC & (1 << (i + 4)))
        x = i;
    }

    return matrix[x][y];
  }

  return 0;
}

// void show(int key) {
//   lcd.setCursor(cursor_pos, line_pos);
//   lcd.print(key);
// }

int main() {
  DDRA |= 0x0F;
  DDRC = 0x00;

  while (1) {
    int tec = teclado();
    // if (tec) {
    PORTA = tec;
    // }
    _delay_ms(1000);
  }
}
