#include <iostream>
#include <assert.h>
#include "cpu.h"

void test_0xA9_lda_immediate() {
    CPU cpu;
    std::vector<uint8_t> instructions = {0xa9, 0x05, 0x00};  
    cpu.interpret(instructions);
    assert(cpu.REGISTER_A == 0x05); 
    assert((cpu.STATUS & 0b00000010) == 0b00);
    assert((cpu.STATUS & 0b10000000) == 0);
    std::cout << "0xA9 LDA Immediate Test Passed" << std::endl;
}

void test_0xA9_lda_zero_flag() {
    CPU cpu;
    std::vector<uint8_t> instructions = {0xA9, 0x00, 0x00};
    cpu.interpret(instructions);
    assert((cpu.STATUS & 0b00000010) == 0b10);
    std::cout << "0xA9 LDA Zero Flag Test Passed" << std::endl;
}

void test_0xAA_tax_move() {
    CPU cpu;
    std::vector<uint8_t> instructions = {0xA9, 0x0C, 0xaa, 0x00};
    cpu.interpret(instructions);
    assert(cpu.REGISTER_A == 0x0C);
    assert(cpu.REGISTER_X == 0x0C);
    std::cout << "0xAA TAX Move Test Passed" << std::endl;
}

void test_0x69_adc_overflow() {
    CPU cpu;
    std::vector<uint8_t> instructions = {0xA9, 0xFF, 0x69, 0x13, 0x00};
    cpu.interpret(instructions);
    assert(cpu.REGISTER_A == 0x12);
    assert((cpu.STATUS & 0b00000001) == 0b00000001);
    std::cout << "0x69 ADC Overflow Test Passed" << std::endl;
}

void test_0xe8_inc() {
    CPU cpu;
    std::vector<uint8_t> instructions = {0xA9, 0x01, 0xaa, 0xe8, 0x00};
    cpu.interpret(instructions);
    assert(cpu.REGISTER_X == 0x02);
    std::cout << "0xe8 INX Test Passed" << std::endl;
}

void test_five_ops_working() {
    CPU cpu;
    std::vector<uint8_t> instructions = {0xa9, 0xc0, 0xaa, 0xe8, 0x00};
    cpu.interpret(instructions);
    assert(cpu.REGISTER_X == 0xc1);
    std::cout << "Five Ops Test Passed" << std::endl;
}

void test_inx_overflow() {
    CPU cpu;
    cpu.REGISTER_X = 0xFF;
    std::vector<uint8_t> instructions = {0xe8, 0xe8, 0x00};
    cpu.interpret(instructions);
    assert(cpu.REGISTER_X == 1);
    std::cout << "INX Overflow Test Passed" << std::endl;
}

int main(int argc, char *argv[])
{
    test_0xA9_lda_immediate();
    test_0xA9_lda_zero_flag();
    test_0xAA_tax_move();
    test_0x69_adc_overflow();
    test_0xe8_inc();
    test_five_ops_working();
    test_inx_overflow();
}
