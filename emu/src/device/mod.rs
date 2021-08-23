mod bus;
mod memory;

pub use self::bus::Bus;
pub use self::memory::RAM;
pub use self::memory::ROM;

pub trait Device {
    fn write(&mut self, addr: u16, val: u8);
    fn read(&self, addr: u16) -> u8;
}
