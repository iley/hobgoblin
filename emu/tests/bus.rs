extern crate emu;
use emu::device::{Bus, Device, RAM};

#[test]
fn test_bus() {
    let mut bus = Bus::new();
    let mut ram = RAM::new(10);

    bus.attach(&mut ram, 0x1000, 10);
    bus.write(0x1000, 42);

    assert_eq!(bus.read(0x1000), 42);
    assert_eq!(ram.read(0), 42);
}
