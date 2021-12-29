GAL16V8
HobgoblinV2IO

M1  IOWR  A3   A4      A5    A6      A7   A8   A9   GND ; M1 and IOWR are active-low
A10  A15  A14  ROMOFF  IOCF  IOUART  A13  A12  A11  VCC

/ROMOFF = M1 * /IOWR * A3 * A4 * A5 * /A6 * /A7 * /A8 * /A9 * /A10 * /A11 * /A12 * /A13 * /A14 * /A15 ; ROM disable, port 0x38 & IOWR
/IOCF   = M1 * /A6 * A7 * /A8 * /A9 * /A10 * /A11 * /A12 * /A13 * /A14 * /A15 ; CF card, port 0x80
/IOUART = M1 * /A3 * A4 * /A5 * /A6 * /A7 * /A8 * /A9 * /A10 * /A11 * /A12 * /A13 * /A14 * /A15 ; UART, port 0x10

DESCRIPTION:
IO address decoding for Hobgoblin V2
