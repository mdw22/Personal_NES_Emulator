// Copyright 2024 Michael White
#ifndef NES_EMU_ADDRESSINGMODE_H_
#define NES_EMU_ADDRESSINGMODE_H_

enum AdressingMode {
    Immediate,
    ZeroPage,
    ZeroPage_X,
    ZeroPage_Y,
    Absolute,
    Absolute_X,
    Absolute_Y,
    Indirect_X,
    Indirect_Y,
    NoneAddressing,
};
#endif // NES_EMU_ADDRESSINGMODE_H_
