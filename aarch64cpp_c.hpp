#ifndef AARCH64CPP_V_HPP
#define AARCH64CPP_V_HPP
#include <cstdint>

/**

CAS, CASA, CASAL, CASL
Compare and Swap word or doubleword in memory reads a 32-bit word or 64-bit doubleword from memory
CAS, CASA, CASAL, 和 CASL 是 ARMv8 架构中的指令，用于在内存中执行比较并交换操作（Compare and Swap）。这些指令用于实现原子操作，确保在多处理器环境中对共享内存的访问是安全的。
CAS：Compare and Swap。执行比较并交换操作。
CASA：Compare and Swap with Acquire。执行比较并交换操作，并在成功时获取内存屏障。
CASAL：Compare and Swap with Acquire and Release。执行比较并交换操作，并在成功时获取和释放内存屏障。
CASL：Compare and Swap with Release。执行比较并交换操作，并在成功时释放内存屏障。
<Ws> 或 <Xs>：源寄存器，包含要比较的值。
<Wt> 或 <Xt>：目标寄存器，包含要写入的值。
[<Xn|SP>]：内存地址，指向要比较和交换的内存位置。
https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/CAS--CASA--CASAL--CASL--Compare-and-Swap-word-or-doubleword-in-memory-
 */
static uint32_t compare_and_swap_world_or_double_world(uint8_t x, uint8_t L, uint8_t rs, uint8_t oO, uint8_t rn, uint8_t rt);

/**
    CASB, CASAB, CASALB, CASLB
    同上，不过是byte级别
 */
static uint32_t compare_and_swap_byte(uint8_t L, uint8_t rs, uint8_t oO, uint8_t rn, uint8_t rt);
/**
    CASH, CASAH, CASALH, CASLH
    同上，不过是half word级别
 */
static uint32_t compare_and_swap_half_world(uint8_t L, uint8_t rs, uint8_t oO, uint8_t rn, uint8_t rt);

/**
    CASP, CASPA, CASPAL, CASPL
    同上，不过是Pair of words or doublewords级别
 */
static uint32_t compare_and_swap_pair_of_words(uint8_t sz, uint8_t L, uint8_t rs, uint8_t oO, uint8_t rn, uint8_t rt);


/**
CBNZ
Compare and Branch on Nonzero compares the value in a register with zero, and conditionally branches to a label at a PC-relative offset if the comparison is not equal. It provides a hint that this is not a subroutine call or return. This instruction does not affect the condition flags.
CBNZ（Compare and Branch on Nonzero）指令用于比较寄存器中的值与零，并在值不为零时条件性地跳转到一个相对当前程序计数器（PC）的偏移地址。该指令不会影响条件标志。

 */
static uint32_t compare_and_branch_on_non_zero(uint8_t sf, uint32_t imm19, uint8_t rt);
/**
CBNZ
与上面相同，不过为0时跳转
*/
static uint32_t compare_and_branch_on_zero(uint8_t sf, uint32_t imm19, uint8_t rt);

/**
    CCMN (immediate)
    Conditional Compare Negative (immediate) sets the value of the condition flags to the result of the comparison of a register value and a negated immediate value if the condition is TRUE, and an immediate value otherwise.
    用于根据条件比较寄存器值和一个取反的立即数，并设置条件标志。如果条件为真，则条件标志设置为比较结果；如果条件为假，则条件标志设置为另一个立即数
    <Wn|Xn>：要比较的寄存器（32 位或 64 位）。
    #<imm>：立即数。
    #<nzcv>：条件标志的值（N, Z, C, V）。
    <cond>：条件码，指定在什么条件下执行比较。

    // 比较 X0 和 -3，如果条件为真，则设置条件标志
    // 如果条件为假，则将条件标志设置为 0b0010 (Z=1, 其他为0)
    CCMN X0, #3, 0b0010, EQ
 */
static uint32_t conditional_compare_negative_with_immediate(uint8_t sf, uint8_t imm5, uint8_t cond, uint8_t rn, uint8_t nzcv);
/**同上 */
static uint32_t conditional_compare_negative_with_register(uint8_t sf, uint8_t rm, uint8_t cond, uint8_t rn, uint8_t nzcv);
/** 同上，只是不negative */
static uint32_t conditional_compare_with_immediate(uint8_t sf, uint8_t imm5, uint8_t cond, uint8_t rn, uint8_t nzcv);
static uint32_t conditional_compare_with_register(uint8_t sf, uint8_t rm, uint8_t cond, uint8_t rn, uint8_t nzcv);

/**
    CFINV
    Invert Carry Flag. This instruction inverts the value of the PSTATE.C flag.
 */
static uint32_t carry_flag_invert();

#endif