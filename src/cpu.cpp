#include "cpu.h"

CPU::CPU()
{
    REGISTER_A = 0;
    REGISTER_X = 0;
    STATUS = 0;
    PROGRAM_COUNTER = 0;
}

void CPU::interpret(std::vector<uint8_t>& program)
{
    PROGRAM_COUNTER = 0; 
    while(true) {
        uint8_t ops_code = program[PROGRAM_COUNTER];
        PROGRAM_COUNTER++;

        switch (ops_code) 
        {
            case 0xa9: { // LDA Op-Code
                uint8_t param = program[PROGRAM_COUNTER];
                PROGRAM_COUNTER++;
                lda(param);
                break;
            }
            case 0xaa: { // Tax Op-Code
                tax();
                break;
            }
            case 0x69: { // ADC Op-Code
                uint8_t param = program[PROGRAM_COUNTER];
                PROGRAM_COUNTER++;
                adc(param);
                break;
            }
            case 0xe8: { // INX Op-Code
                inx();
                break;
            }
            case 0x00: { // BRK Op-Code
                return;
                break;
            }
            default: {
                break;
            }
        }
    }
}

void CPU::lda(uint8_t value)
{
    REGISTER_A = value; 
    updateZeroAndNegFlags(REGISTER_A);
}

void CPU::tax()
{
    REGISTER_X = REGISTER_A;
    updateZeroAndNegFlags(REGISTER_X);
}

void CPU::adc(uint8_t value)
{
    uint8_t carry = 0;
    if(STATUS & 0b00000001 == 0b00000001) carry = 1;
    REGISTER_A += value + carry; 
    updateCarryFlag(REGISTER_A < value);
    updateZeroAndNegFlags(REGISTER_A);
}

void CPU::inx()
{
    REGISTER_X += 1;
    updateZeroAndNegFlags(REGISTER_X);
}

void CPU::updateZeroAndNegFlags(uint8_t result)
{
    if(result == 0) {
        STATUS |= 0b00000010;
    } else {
        STATUS &= 0b11111101;
    }
    if(result & 0b10000000) {
        STATUS |= 0b10000000;
    } else {
        STATUS &= 0b01111111;
    }
}

void CPU::updateCarryFlag(bool val)
{
    if(val) {
        STATUS |= 0b00000001;
    } else {
        STATUS &= 0b11111110;
    }
}
