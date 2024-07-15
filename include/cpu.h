// Copyright 2024 Michael White
#include <cstdint>
#include <vector>
class CPU {
    public:
    uint8_t REGISTER_A; 
    uint8_t REGISTER_X; 
    uint8_t STATUS;
    uint16_t PROGRAM_COUNTER; 
    
    CPU();
    
    void interpret(std::vector<uint8_t>&);

    void lda(uint8_t);

    void tax();

    void adc(uint8_t);

    void inx();

    void updateZeroAndNegFlags(uint8_t);

    void updateCarryFlag(bool);
};