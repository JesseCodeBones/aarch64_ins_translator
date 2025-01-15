#ifndef AARCH64CPP_E_HPP
#define AARCH64CPP_E_HPP
#include <cstdint>

/**
EON
Bitwise Exclusive OR NOT
EON (Exclusive OR NOT)
指令对一个寄存器值和一个可选移位的寄存器值执行按位异或非操作，并将结果写入目标寄存器。

// X1 = 0b1100  // 12
// X2 = 0b1010  // 10

// 执行 EON 指令
EON X0, X1, X2  // 对 X1 和 X2 的值进行按位异或非操作，并将结果存储到 X0

X1:  1100
X2:  1010
~X2: 0101
X1 ^ ~X2: 1100 ^ 0101 = 1001
 */
static uint32_t exclusive_or_not_shifted_register(uint8_t sf, uint8_t shift,
                                                  uint8_t rm, uint8_t imm6,
                                                  uint8_t rn, uint8_t rd);

static uint32_t exclusive_or_immediate(uint8_t sf, uint8_t N, uint8_t immr,
                                       uint8_t imms, uint8_t rn, uint8_t rd);

static uint32_t exclusive_or_register(uint8_t sf, uint8_t shift, uint8_t rm,
                                      uint8_t imm6, uint8_t rn, uint8_t rd);

/**
ERET ERETAA, ERETAB  is undefined in EL0
 */

static uint32_t error_synchronization_barrier() {
  return 0b11010101000000110010001000011111;
}

static uint32_t extract_register_from_a_pair_registers(uint8_t sf, uint8_t N,
                                                       uint8_t rm, uint8_t imms,
                                                       uint8_t rn, uint8_t rd);

#endif