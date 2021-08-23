extern crate emu;
use emu::device::{Device, RAM, ROM};

#[test]
fn test_ram() {
    let mut ram = RAM::new(10);

    assert_eq!(ram.read(0), 0);

    ram.write(0, 42);
    assert_eq!(ram.read(0), 42);

    ram.write(1, 0xff);
    assert_eq!(ram.read(1), 0xff);

    assert_eq!(ram.read(1000), 0); // Out-of-bounds
}

#[test]
fn test_rom() {
    let mut rom = ROM::new(vec![1, 2, 3]);

    assert_eq!(rom.read(0), 1);
    assert_eq!(rom.read(1), 2);
    assert_eq!(rom.read(2), 3);
    assert_eq!(rom.read(3), 0);

    rom.write(0, 42); // Ignored.
    assert_eq!(rom.read(0), 1);
}
