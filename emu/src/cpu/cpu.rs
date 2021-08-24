use crate::device::Device;

#[derive(Copy, Clone)]
struct Registers {
    af: u16, // Accumulator and flags
    bc: u16,
    de: u16,
    hl: u16, // Indirect address

    // Shadow registers
    afp: u16,
    bcp: u16,
    dep: u16,
    hlp: u16,

    // Index registers
    ix: u16,
    iy: u16,

    i: u8, // Interrupt vector
    r: u8, // Refresh counter

    pc: u16, // Program Counter
    sp: u16, // Stack Pointer
}

const INITIAL_REGISTERS: Registers = Registers {
    af: 0x0000,
    bc: 0x0000,
    de: 0x0000,
    hl: 0x0000,

    afp: 0x0000,
    bcp: 0x0000,
    dep: 0x0000,
    hlp: 0x0000,

    ix: 0x0000,
    iy: 0x0000,

    i: 0x00,
    r: 0x00,

    pc: 0x0000,
    sp: 0xf000,
};

pub struct CPU<'a> {
    reg: Registers,
    mem: &'a mut dyn Device,
    io: &'a mut dyn Device,
}

impl<'a> CPU<'a> {
    pub fn new(mem: &'a mut dyn Device, io: &'a mut dyn Device) -> CPU<'a> {
        CPU {
            reg: INITIAL_REGISTERS,
            mem,
            io,
        }
    }

    pub fn step(&mut self) {
        let opcode1 = self.mem.read(self.reg.pc);
        match opcode1 {
            0x00 => (), // NOP
            0x01 => { // LD BC, **
                self.reg.bc = self.read16(self.reg.sp+1);
                self.reg.pc += 2;
            },
            0x02 => { // LD (BC), A
                self.mem.write(self.reg.bc, (self.reg.af >> 8) as u8);
            },
            0x03 => { // INC BC
                self.reg.bc += 1;
            },
            0x04 => { // INC B
            },
        }
        self.reg.pc += 1;
    }

    fn read16(&self, addr: u16) -> u16 {
        (self.mem.read(addr+1) as u16) << 8 | (self.mem.read(addr) as u16)
    }
}
