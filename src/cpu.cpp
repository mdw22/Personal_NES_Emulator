#include "cpu.h"

CPU::CPU()
{
    REGISTER_A = 0;
    REGISTER_X = 0;
    REGISTER_Y = 0;
    STATUS = 0;
    PROGRAM_COUNTER = 0;
    MEMORY.reserve(0xFFFF); // Allocates 64kB of space for Memory
}

uint8_t CPU::mem_read(uint16_t addr)
{
    return MEMORY[addr];
}

uint16_t CPU::mem_read_u16(uint16_t pos)
{
    uint16_t lo = mem_read(pos);
    uint16_t hi = mem_read(pos + 1);
    return ((hi << 8) | lo);
}

void CPU::mem_write(uint16_t addr, uint8_t data)
{
    MEMORY[addr] = data;
}

void CPU::mem_write_u16(uint16_t pos, uint16_t data)
{
    uint16_t hi = (data >> 8);
    uint16_t lo = (data & 0xFF);
    mem_write(pos, lo);
    mem_write(pos + 1, hi);
}

void CPU::load(std::vector<uint8_t>& program)
{
    std::copy(program.begin(), program.end(), MEMORY.begin() + 0x8000);
    mem_write_u16(0xFFFC, 0x8000);
}

void CPU::reset()
{
    REGISTER_A = 0;
    REGISTER_X = 0;
    STATUS = 0;

    PROGRAM_COUNTER = mem_read_u16(0xFFFC);
}

void CPU::run()
{
    while(true) {
        uint8_t ops_code = mem_read(PROGRAM_COUNTER);
        PROGRAM_COUNTER++;
       
        auto it = MP_OPS_CODES.find(ops_code);
        if(it != MP_OPS_CODES.end()) {
            OpCode& op_code = it->second;
            std::string name = op_code.name;
            uint8_t bytes = op_code.bytes;
            uint8_t cycles = op_code.cycles;
            AdressingMode mode = op_code.mode;

            // TO-DO : Match by num instead?
            if(name == "LDA") {
                lda(mode);
                PROGRAM_COUNTER += (bytes - 1);
            } else if(name == "STA") {
                sta(mode);
                PROGRAM_COUNTER += (bytes - 1);
            } else if(name == "BRK") {
                return;
            } else if(name == "TAX") {
                tax();
            } else if(name == "ADC") {
                adc(mode);
                PROGRAM_COUNTER += (bytes - 1);
            } else if(name == "INX") {
                inx();
            }
        } else {
            std::cerr << "Unknown opcode: " << std::hex << static_cast<int>(ops_code) << std::endl;
            return;
        }
    }
}

void CPU::load_and_run(std::vector<uint8_t> & program)
{
    load(program);
    reset();
    run();
}

uint16_t CPU::get_operand_address(AdressingMode mode)
{
    switch(mode) {
        case AdressingMode::Immediate: {
            return static_cast<uint16_t>(PROGRAM_COUNTER);
        }
        case AdressingMode::ZeroPage: {
            return static_cast<uint16_t>(mem_read(PROGRAM_COUNTER));
        }
        case AdressingMode::ZeroPage_X: {
            uint8_t pos = mem_read(PROGRAM_COUNTER);
            return static_cast<uint16_t>(pos + REGISTER_X); 
        }
        case AdressingMode::ZeroPage_Y: {
            uint8_t pos = mem_read(PROGRAM_COUNTER);
            return static_cast<uint16_t>(REGISTER_Y + pos);
        }
        case AdressingMode::Absolute: {
            return mem_read_u16(PROGRAM_COUNTER);
        }
        case AdressingMode::Absolute_X: {
            uint16_t base = mem_read_u16(PROGRAM_COUNTER);
            return static_cast<uint16_t>(REGISTER_X + base);
        }
        case AdressingMode::Absolute_Y: {
            uint16_t base = mem_read_u16(PROGRAM_COUNTER);
            return static_cast<uint16_t>(base + REGISTER_Y);
        }
        case AdressingMode::Indirect_X: {
            uint8_t base = mem_read(PROGRAM_COUNTER);
            uint8_t ptr = base + REGISTER_X; // Both are already uint8_t type
            uint16_t lo = mem_read(static_cast<uint16_t>(ptr));
            uint16_t hi = mem_read(static_cast<uint16_t>(ptr + 1));
            return ((hi << 8) | lo); // Return hi bitshift to the left + lo
        }
        case AdressingMode::Indirect_Y: {
            uint8_t base = mem_read(PROGRAM_COUNTER);
            uint16_t lo = mem_read(static_cast<uint16_t>(base));
            uint16_t hi = mem_read(static_cast<uint16_t>(base + 1));
            uint16_t deref_base = ((hi << 8) | lo);
            return deref_base + static_cast<uint16_t>(REGISTER_Y);
        }
        default: {
            std::cout << "mode %s is not supported" << std::endl;
            exit(1);
            break;
        }
    }
}

void CPU::lda(AdressingMode mode)
{
    uint16_t addr = get_operand_address(mode);
    uint8_t value = mem_read(addr);
    REGISTER_A = value;
    updateZeroAndNegFlags(REGISTER_A);
}

void CPU::tax()
{
    REGISTER_X = REGISTER_A;
    updateZeroAndNegFlags(REGISTER_X);
}

void CPU::adc(AdressingMode mode)
{
    uint16_t addr = get_operand_address(mode);
    uint8_t value = mem_read(addr);
    uint8_t carry = 0;
    if((STATUS & 0b00000001) == 0b00000001) carry = 1; // If carry bit is set, add it to result
    REGISTER_A += value + carry; 
    updateCarryFlag(REGISTER_A < value);
    updateZeroAndNegFlags(REGISTER_A);
}

void CPU::inx()
{
    REGISTER_X += 1;
    updateZeroAndNegFlags(REGISTER_X);
}

void CPU::sta(AdressingMode mode)
{
    uint16_t addr = get_operand_address(mode);
    mem_write(addr, REGISTER_A);
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
