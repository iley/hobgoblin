use super::*;

pub struct RAM {
    size: u16,
    data: Vec<u8>,
}

impl RAM {
    pub fn new(size: u16) -> RAM {
        RAM {
            size,
            data: vec![0; size as usize],
        }
    }
}

impl Device for RAM {
    fn write(&mut self, addr: u16, val: u8) {
        if addr >= self.size {
            // TODO: Report out-of-bounds memory access when in debug mode.
            return;
        }
        self.data[addr as usize] = val;
    }

    fn read(&self, addr: u16) -> u8 {
        if addr >= self.size {
            // TODO: Report out-of-bounds memory access when in debug mode.
            return 0;
        }
        return self.data[addr as usize];
    }
}

pub struct ROM {
    data: Vec<u8>,
}

impl ROM {
    pub fn new(data: Vec<u8>) -> ROM {
        ROM { data: data.clone() }
    }
}

impl Device for ROM {
    fn write(&mut self, _addr: u16, _val: u8) {
        // NOP
    }

    fn read(&self, addr: u16) -> u8 {
        if addr as usize >= self.data.len() {
            return 0;
        }
        return self.data[addr as usize];
    }
}
