#ifndef AARCH64CPP_B_HPP
#define AARCH64CPP_B_HPP
#include <cstdint>
#include <stdint.h>

/**
  Branch causes an unconditional branch to a label at a PC-relative offset,
  with a hint that this is not a subroutine call or return. to the value in
  the program counter.
  @param imm26 26bit immediate value,
  bits(64) offset = SignExtend(imm26:'00', 64);
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/B--Branch-
 */
static uint32_t branch_immediate(uint32_t imm26);
#endif