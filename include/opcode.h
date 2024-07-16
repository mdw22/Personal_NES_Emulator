// Copyright 2024 Michael White
#ifndef NES_EMU_OPCODE_H_
#define NES_EMU_OPCODE_H_
#include <cstdint>
#include <string>
#include <map>
#include "addressingmode.h"

class OpCode {
    public:
    std::string name;
    uint8_t bytes; 
    uint8_t cycles;
    AdressingMode mode;

    OpCode(std::string n, uint8_t b, uint8_t c, AdressingMode m) {
        name = n;
        bytes = b;
        cycles = c;
        mode = m;
    };
};

extern std::map<uint8_t, OpCode> MP_OPS_CODES;

#endif // NES_EMU_OPCODE_H_
