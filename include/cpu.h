// Copyright 2024 Michael White
#ifndef NES_EMU_CPU_H_
#define NES_EMU_CPU_H_
#include <vector>
#include <iostream>
#include "opcode.h"

class CPU {
    public:
    uint8_t REGISTER_A; 
    uint8_t REGISTER_X; 
    uint8_t REGISTER_Y;
    uint8_t STATUS;
    uint16_t PROGRAM_COUNTER; 
    std::vector<uint8_t> MEMORY; 
    
    CPU();

    // Reads Program Code from Memory
    // @param addr uint16_t address in Memory
    // @return uint8_t Program Code
    uint8_t mem_read(uint16_t); 

    // Transforms Little-Endian Code into Mem Address
    // @param pos uint16_t address position
    // @return uint16_t Mem Address
    uint16_t mem_read_u16(uint16_t);

    void mem_write(uint16_t, uint8_t);

    void mem_write_u16(uint16_t, uint16_t);

    void load(std::vector<uint8_t>&);

    void reset();

    void run();

    void load_and_run(std::vector<uint8_t>&);

    uint16_t get_operand_address(AdressingMode);

    void lda(AdressingMode);

    void tax();

    void adc(AdressingMode);

    void inx();

    void sta(AdressingMode);

    void updateZeroAndNegFlags(uint8_t);

    void updateCarryFlag(bool);
};
#endif // NES_EMU_CPU_H_
