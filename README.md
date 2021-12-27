# Hobgoblin: Z80-based single-board computer

## Specs

 - Z80 CPU running at 10MHz
 - 64 KiB RAM
 - 8 x 16 KiB ROM. ROM bank is selectable with a DIP switch
 - ROM can be paged out for CP/M compatibility
 - Built-in usb-to-serial adapter for convenience of use with modern computers
 - 2 RC2014-compatible extension slots.

## Memory map

```
    FFFF ┌─────────┐
         │         │
         │         │
         │         │
         │         │
         │   RAM   │
         │         │
         │         │
         │         │
    4000 ├─────────┤
         │         │
         │   ROM   │
         │         │
    0000 └─────────┘
```
