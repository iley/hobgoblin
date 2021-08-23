use core::ops::Bound::{Included, Unbounded};
use std::collections::BTreeMap;

use super::*;

pub struct Bus<'a> {
    mappings: BTreeMap<u16, Mapping<'a>>,
}

struct Mapping<'a> {
    start_addr: u16,
    end_addr: u16,
    device: &'a mut dyn Device,
}

impl<'a> Bus<'a> {
    pub fn new() -> Bus<'a> {
        Bus {
            mappings: BTreeMap::new(),
        }
    }

    pub fn attach(&mut self, device: &'a mut dyn Device, start_addr: u16, length: u16) {
        // TODO: Check for overlaps.
        let end_addr = start_addr + length - 1;
        self.mappings.insert(
            start_addr,
            Mapping {
                start_addr,
                end_addr,
                device,
            },
        );
    }
}

impl<'a> Device for Bus<'a> {
    fn write(&mut self, addr: u16, val: u8) {
        match self
            .mappings
            .range_mut((Unbounded, Included(addr)))
            .next_back()
        {
            None => (),
            Some((_, mapping)) => {
                if mapping.start_addr >= addr && addr <= mapping.end_addr {
                    mapping.device.write(addr - mapping.start_addr, val)
                }
            }
        }
    }

    fn read(&self, addr: u16) -> u8 {
        match self.mappings.range((Unbounded, Included(addr))).next_back() {
            None => 0,
            Some((_, mapping)) => {
                if mapping.start_addr >= addr && addr <= mapping.end_addr {
                    mapping.device.read(addr - mapping.start_addr)
                } else {
                    0
                }
            }
        }
    }
}
