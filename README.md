# avra-linux

Avra Linux is a repository to explain and teach how to compile & load assembly &
C programs into Arduino boards using Linux. The inspiration is the lack of
resources about it online. Although there are some tutorials, there are not too
many examples.

> This repository is based on Arduino Mega, which uses ATMega2560. Working with
> other boards should not be hard, though definitions should be imported.

# Requirements

Before being able to run any examples inside this on you Arduino Mega you'll
need to install some dependencies first.

## avra & avrdude

We use avra to compile .s or .asm files and avrdude to load them into Arduino
board.

```bash
# On Ubuntu, this should install all deps
sudo apt install avra avra-libc avrdude
```

## Avra 2560

As we're using an ATMega 2560, we'll need to install this [library][avra-2560]
to compile our codes and be able to upload them on Arduino. To install follow
the instructions.

# Compiling & loading

## Assembly

Inside some example folders, the one containing `.s` extension files, the next
lines should compile and update to your Arduino. In this example we'll use
`examples/led`.

```bash
cd examples/led
avra led.s
sudo avrdude -p m2560 -c stk500v2 -P /dev/ttyACM0 -D -U led.s.hex
```

# C

Inside some example folders, the one containing `.c` extension files, the next
lines should compile and update to your Arduino. In this example we'll use
`examples/pingpong`.

```bash
avr-gcc -mmcu=atmega2560 game.c
avr-objcopy -O ihex a.out game.hex
sudo avrdude -p m2560 -c stk500v2 -b 115200 -P /dev/ttyACM0 -D -U game.hex
```

[avra-2560]: https://github.com/timofurrer/avra-atmega
