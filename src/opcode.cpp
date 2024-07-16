// Copyright 2024 Michael White
#include "opcode.h"

std::map<uint8_t, OpCode> MP_OPS_CODES = {
    {0x00, OpCode("BRK", 1, 7, AdressingMode::NoneAddressing)},
    {0xaa, OpCode("TAX", 1, 2, AdressingMode::NoneAddressing)},
    {0xa9, OpCode("LDA", 2, 2, AdressingMode::Immediate)},
    {0xa5, OpCode("LDA", 2, 3, AdressingMode::ZeroPage)},
    {0xb5, OpCode("LDA", 2, 4, AdressingMode::ZeroPage_X)},
    {0xad, OpCode("LDA", 3, 4, AdressingMode::Absolute)},
    {0xbd, OpCode("LDA", 3, 4, AdressingMode::Absolute_X)}, // +1 if page crossed
    {0xb9, OpCode("LDA", 3, 4, AdressingMode::Absolute_Y)}, // +1 if page crossed
    {0xa1, OpCode("LDA", 2, 6, AdressingMode::Indirect_X)},
    {0xb1, OpCode("LDA", 2, 5, AdressingMode::Indirect_Y)}, // +1 if page crossed
    {0x85, OpCode("STA", 2, 3, AdressingMode::ZeroPage)},
    {0x95, OpCode("STA", 2, 4, AdressingMode::ZeroPage_X)},
    {0x8D, OpCode("STA", 3, 4, AdressingMode::Absolute)},
    {0x9D, OpCode("STA", 3, 5, AdressingMode::Absolute_X)},
    {0x99, OpCode("STA", 3, 5, AdressingMode::Absolute_Y)},
    {0x81, OpCode("STA", 2, 6, AdressingMode::Indirect_X)},
    {0x91, OpCode("STA", 2, 6, AdressingMode::Indirect_Y)},
    {0xe8, OpCode("INX", 1, 2, AdressingMode::NoneAddressing)},
    {0x69, OpCode("ADC", 2, 2, AdressingMode::Immediate)},
    {0x65, OpCode("ADC", 2, 3, AdressingMode::ZeroPage)},
    {0x75, OpCode("ADC", 2, 4, AdressingMode::ZeroPage_X)},
    {0x6D, OpCode("ADC", 3, 4, AdressingMode::Absolute)},
    {0x7d, OpCode("ADC", 3, 4, AdressingMode::Absolute_X)}, // + 1 if page crossed
    {0x79, OpCode("ADC", 3, 4, AdressingMode::Absolute_Y)}, // +1 if page crossed
    {0x61, OpCode("ADC", 2, 6, AdressingMode::Indirect_X)},
    {0x71, OpCode("ADC", 2, 5, AdressingMode::Indirect_Y)}, // +1 if page crossed
    
};