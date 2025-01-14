#ifndef AARCH64CPP_C_HPP
#define AARCH64CPP_C_HPP
#include <cstdint>

/**

CAS, CASA, CASAL, CASL
Compare and Swap word or doubleword in memory reads a 32-bit word or 64-bit
doubleword from memory CAS, CASA, CASAL, 和 CASL 是 ARMv8
架构中的指令，用于在内存中执行比较并交换操作（Compare and
Swap）。这些指令用于实现原子操作，确保在多处理器环境中对共享内存的访问是安全的。
CAS：Compare and Swap。执行比较并交换操作。
CASA：Compare and Swap with
Acquire。执行比较并交换操作，并在成功时获取内存屏障。 CASAL：Compare and Swap
with Acquire and Release。执行比较并交换操作，并在成功时获取和释放内存屏障。
CASL：Compare and Swap with
Release。执行比较并交换操作，并在成功时释放内存屏障。 <Ws> 或
<Xs>：源寄存器，包含要比较的值。 <Wt> 或 <Xt>：目标寄存器，包含要写入的值。
[<Xn|SP>]：内存地址，指向要比较和交换的内存位置。
https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/CAS--CASA--CASAL--CASL--Compare-and-Swap-word-or-doubleword-in-memory-
 */
static uint32_t compare_and_swap_world_or_double_world(uint8_t x, uint8_t L,
                                                       uint8_t rs, uint8_t oO,
                                                       uint8_t rn, uint8_t rt);

/**
    CASB, CASAB, CASALB, CASLB
    同上，不过是byte级别
 */
static uint32_t compare_and_swap_byte(uint8_t L, uint8_t rs, uint8_t oO,
                                      uint8_t rn, uint8_t rt);
/**
    CASH, CASAH, CASALH, CASLH
    同上，不过是half word级别
 */
static uint32_t compare_and_swap_half_world(uint8_t L, uint8_t rs, uint8_t oO,
                                            uint8_t rn, uint8_t rt);

/**
    CASP, CASPA, CASPAL, CASPL
    同上，不过是Pair of words or doublewords级别
 */
static uint32_t compare_and_swap_pair_of_words(uint8_t sz, uint8_t L,
                                               uint8_t rs, uint8_t oO,
                                               uint8_t rn, uint8_t rt);

/**
CBNZ
Compare and Branch on Nonzero compares the value in a register with zero, and
conditionally branches to a label at a PC-relative offset if the comparison is
not equal. It provides a hint that this is not a subroutine call or return. This
instruction does not affect the condition flags. CBNZ（Compare and Branch on
Nonzero）指令用于比较寄存器中的值与零，并在值不为零时条件性地跳转到一个相对当前程序计数器（PC）的偏移地址。该指令不会影响条件标志。

 */
static uint32_t compare_and_branch_on_non_zero(uint8_t sf, uint32_t imm19,
                                               uint8_t rt);
/**
CBNZ
与上面相同，不过为0时跳转
*/
static uint32_t compare_and_branch_on_zero(uint8_t sf, uint32_t imm19,
                                           uint8_t rt);

/**
    CCMN (immediate)
    Conditional Compare Negative (immediate) sets the value of the condition
   flags to the result of the comparison of a register value and a negated
   immediate value if the condition is TRUE, and an immediate value otherwise.
    用于根据条件比较寄存器值和一个取反的立即数，并设置条件标志。如果条件为真，则条件标志设置为比较结果；如果条件为假，则条件标志设置为另一个立即数
    <Wn|Xn>：要比较的寄存器（32 位或 64 位）。
    #<imm>：立即数。
    #<nzcv>：条件标志的值（N, Z, C, V）。
    <cond>：条件码，指定在什么条件下执行比较。

    // 比较 X0 和 -3，如果条件为真，则设置条件标志
    // 如果条件为假，则将条件标志设置为 0b0010 (Z=1, 其他为0)
    CCMN X0, #3, 0b0010, EQ
 */
static uint32_t conditional_compare_negative_with_immediate(
    uint8_t sf, uint8_t imm5, uint8_t cond, uint8_t rn, uint8_t nzcv);
/**同上 */
static uint32_t
conditional_compare_negative_with_register(uint8_t sf, uint8_t rm, uint8_t cond,
                                           uint8_t rn, uint8_t nzcv);
/** 同上，只是不negative */
static uint32_t conditional_compare_with_immediate(uint8_t sf, uint8_t imm5,
                                                   uint8_t cond, uint8_t rn,
                                                   uint8_t nzcv);
static uint32_t conditional_compare_with_register(uint8_t sf, uint8_t rm,
                                                  uint8_t cond, uint8_t rn,
                                                  uint8_t nzcv);

/**
    CFINV
    Invert Carry Flag. This instruction inverts the value of the PSTATE.C flag.
 */
static uint32_t carry_flag_invert();

/**

    CINC
    Conditional Increment returns, in the destination register, the value of the
   source register incremented by 1 if the condition is TRUE, and otherwise
   returns the value of the source register.

    MOV X0, #5          // 将值 5 加载到寄存器 X0
    MOV X1, #0          // 将值 0 加载到寄存器 X1

    // 如果条件 EQ（相等）为真，则将 X0 的值加 1 并存储到 X1
    // 否则，将 X0 的原始值存储到 X1
    CINC X1, X0, EQ
 */

static uint32_t conditional_increment_returns(uint8_t sf, uint8_t rm,
                                              uint8_t cond, uint8_t rn,
                                              uint8_t rd);
/** 同上 */
static uint32_t conditional_invert_returns(uint8_t sf, uint8_t rm, uint8_t cond,
                                           uint8_t rn, uint8_t rd);

/**
CLREX
Clear Exclusive clears the local monitor of the executing PE.
CLREX
指令用于清除本地监视器，以确保在多处理器系统中不会出现死锁或数据竞争。它通常与
LDREX 和 STREX 指令一起使用，用于实现互斥锁和其他同步机制。
 */
static uint32_t clear_exclusive_clears();

/**
CLS
Count Leading Sign bits counts the number of leading bits of the source register
that have the same value as the most significant bit of the register, and writes
the result to the destination register. This count does not include the most
significant bit of the source register.

假设我们有一个 32 位的寄存器 X0，其值为
0b00000000_00000000_00001111_11111111。我们希望计算与最高有效位相同的前导位的数量。
CLS X1, X0  // 计算 X0 中与最高有效位相同的前导位的数量，并将结果存储到 X1
在这个例子中，X0 的最高有效位是 0。从最高有效位开始，前 16 位都是 0，所以 CLS
指令会计算出 16 个前导位。

假设我们有一个 32 位的寄存器 X0，其值为
0b11111111_11111111_11110000_00000000。我们希望计算与最高有效位相同的前导位的数量。
CLS X1, X0  // 计算 X0 中与最高有效位相同的前导位的数量，并将结果存储到 X1
在这个例子中，X0 的最高有效位是 1。从最高有效位开始，前 18 位都是 1，所以 CLS
指令会计算出 18 个前导位。
因此，执行 CLS 指令后，X1 的值将是 18。
 */
static uint32_t count_leading_sign_bits(uint8_t sf, uint8_t rn, uint8_t rd);
/**
CLZ
指令用于计算源寄存器中从最高有效位开始连续的 0 的数量，直到遇到第一个 1
为止，并将结果写入目标寄存器。
 */
static uint32_t count_leading_zeros(uint8_t sf, uint8_t rn, uint8_t rd);

/**
CMN (extended register)
Compare Negative (extended register) adds a register value and a sign or
zero-extended register value, followed by an optional left shift amount. The
argument that is extended from the <Rm> register can be a byte, halfword, word,
or doubleword. It updates the condition flags based on the result, and discards
the result.

假设我们有两个 32 位的寄存器 X0 和 X1，并且我们希望将 X0 的值与 X1
的符号扩展值相加，并更新条件标志。
// X0 = 0x00000010  // 16
// X1 = 0xFFFFFFF0  // -16 (符号扩展)
CMN X0, X1, LSL #0  // 将 X0 与 X1 的符号扩展值相加，并更新条件标志
在这个例子中，X1 的值是 0xFFFFFFF0，符号扩展后仍然是 -16。CMN 指令将 X0 的值 16
与 X1 的符号扩展值 -16 相加，结果为 0，并更新条件标志。

 */
static uint32_t compare_negative_extended_register_add(uint8_t sf, uint8_t rm,
                                                       uint8_t option,
                                                       uint8_t imm3,
                                                       uint8_t rn);
/** 同上 */
static uint32_t compare_negative_immediate_add(uint8_t sf, uint8_t sh,
                                               uint8_t imm12, uint8_t rn);
/** 同上 */
static uint32_t compare_negative_shifted_register_add(uint8_t sf, uint8_t shift,
                                                      uint8_t rm, uint8_t imm6,
                                                      uint8_t rn);
/**
CMP
假设我们有两个 32 位的寄存器 X0 和 X1，并且我们希望将 X1 的符号扩展值从 X0
中减去，并更新条件标志。

// X0 = 0x00000020  // 32
// X1 = 0xFFFFFFF0  // -16 (符号扩展)
CMP X0, X1, LSL #0  // 将 X1 的符号扩展值从 X0 中减去，并更新条件标志
在这个例子中，X1 的值是 0xFFFFFFF0，符号扩展后仍然是 -16。CMP 指令将 X1
的符号扩展值 -16 从 X0 的值 32 中减去，结果为 48，并更新条件标志。
 */
static uint32_t compare_negative_extended_register_sub(uint8_t sf, uint8_t rm,
                                                       uint8_t option,
                                                       uint8_t imm3,
                                                       uint8_t rn);
/** 同上 */
static uint32_t compare_negative_immediate_sub(uint8_t sf, uint8_t sh,
                                               uint8_t imm12, uint8_t rn);
/** 同上 */
static uint32_t compare_negative_shifted_register_sub(uint8_t sf, uint8_t shift,
                                                      uint8_t rm, uint8_t imm6,
                                                      uint8_t rn);

/**

CMPP 指令用于从第一个源寄存器中减去第二个源寄存器中持有的 56
位地址，并根据减法结果更新条件标志，但不会保留结果。它是 SUBPS 指令的别名。

// X0 = 0x0000_0000_1234_5678  // 56 位地址
// X1 = 0x0000_0000_0000_1234  // 56 位地址
CMPP X0, X1  // 将 X1 中的地址从 X0 中减去，并更新条件标志
在这个例子中，X0 的值是 0x0000_0000_1234_5678，X1 的值是
0x0000_0000_0000_1234。CMPP 指令将 X1 的地址从 X0 中减去，结果为
0x0000_0000_1234_4444，并更新条件标志。
 */
static uint32_t compare_with_tag_sub(uint8_t xm, uint8_t xn);

/**
CNEG
指令用于在条件为真时，将源寄存器的值取反并返回到目标寄存器；如果条件为假，则返回源寄存器的值。它是
CSNEG 指令的别名。

/ X0 = 5
// 条件为真
CNEG X1, X0, EQ  // 如果条件 EQ 为真，则将 X0 的值取反并存储到 X1，否则将 X0
的值存储到 X1

在这个例子中，假设条件 EQ 为真，那么 X0 的值 5 将被取反，结果为 -5，并存储到
X1。如果条件为假，则 X0 的值 5 将直接存储到 X1。

 */
static uint32_t conditional_negate_returns(uint8_t sf, uint8_t rm, uint8_t cond,
                                           uint8_t rn, uint8_t rd);
/**
CPP
Cache Prefetch Prediction Restriction by Context prevents cache allocation
predictions that predict execution addresses based on information gathered from
earlier execution within a particular execution context.

https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/CPP--Cache-Prefetch-Prediction-Restriction-by-Context--an-alias-of-SYS-?lang=en
 */
static uint32_t cache_prefetch_prediction(uint8_t xt);

/**

CPYFP, CPYFM, 和 CPYFE
指令集用于执行内存复制操作。这些指令按顺序执行，并且在内存中连续出现：首先是
CPYFP，然后是 CPYFM，最后是 CPYFE。

指令说明
CPYFP (Copy Forward Prologue):

进行一些参数的预处理，使其适合使用 CPYFM 指令，并执行一部分内存复制。
CPYFM (Copy Forward Main):

执行主要的内存复制操作。
CPYFE (Copy Forward Epilogue):

执行内存复制的最后部分。


if !HaveFeatMOPS() then UNDEFINED;
if sz != '00' then UNDEFINED;

integer d = UInt(Rd);
integer s = UInt(Rs);
integer n = UInt(Rn);
bits(4) options = op2;

MOPSStage stage;
case op1 of
    when '00' stage = MOPSStage_Prologue;
    when '01' stage = MOPSStage_Main;
    when '10' stage = MOPSStage_Epilogue;
    otherwise SEE "Memory Copy and Memory Set";

if d == s  || s == n  || d == n then UNDEFINED;
if d == 31 || s == 31 || n == 31 then UNDEFINED;

 */
static uint32_t memory_copy_forward(uint8_t sz, uint8_t op1, uint8_t rs,
                                    uint8_t rn, uint8_t rd);

/**
CPYFPN, CPYFMN, CPYFEN
Memory Copy Forward-only, reads and writes non-temporal. These instructions
perform a memory copy. The prologue, main, and epilogue instructions are
expected to be run in succession and to appear consecutively in memory: CPYFPN,
then CPYFMN, and then CPYFEN.

*/
static uint32_t memroy_copy_read_and_write_no_temporal(uint8_t sz, uint8_t op1,
                                                       uint8_t rs, uint8_t rn,
                                                       uint8_t rd);

static uint32_t memroy_copy_read_no_temporal(uint8_t sz, uint8_t op1,
                                             uint8_t rs, uint8_t rn,
                                             uint8_t rd);

static uint32_t memory_copy_read_unprivileged(uint8_t sz, uint8_t op1,
                                              uint8_t rs, uint8_t rn,
                                              uint8_t rd);

static uint32_t memory_copy_read_unprivileged_reads_and_writes_non_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd);
static uint32_t
memory_copy_reads_unprivileged_non_temporal(uint8_t sz, uint8_t op1, uint8_t rs,
                                            uint8_t rn, uint8_t rd);
static uint32_t memory_copy_writes_unprivileged(uint8_t sz, uint8_t op1,
                                                uint8_t rs, uint8_t rn,
                                                uint8_t rd);
static uint32_t memory_copy_writes_unprivileged_reads_and_writes_non_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd);
static uint32_t memory_copy_writes_unprivileged_reads_non_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd);
static uint32_t memory_copy_writes_unprivileged_and_non_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd);

/**
crc计算指令

 */
static uint32_t crc(uint8_t sf, uint8_t rm, uint8_t c, uint8_t sz, uint8_t rn,
                    uint8_t rd);
/**

CSDB

用于控制推测执行和数据值预测。它确保在 CSDB
指令之后按程序顺序出现的指令（除了分支指令）不能使用以下任何结果进行推测执行：
推测执行的主要问题在于安全性漏洞，例如 Spectre 和
Meltdown。这些漏洞利用了推测执行过程中处理器对数据的预测和处理行为，可能导致敏感数据泄露。CSDB
指令的主要目的是防止这些安全性问题，而不是解决程序正确性的问题。
 */
static uint32_t consumption_speculative_data_barrier();

/**
CSEL
指令是条件选择指令。它根据条件的真假，将第一个源寄存器的值或第二个源寄存器的值写入目标寄存器。
如果条件为真，则将第一个源寄存器的值写入目标寄存器；如果条件为假，则将第二个源寄存器的值写入目标寄存器。

 */
static uint32_t conditional_select(uint8_t sf, uint8_t rn, uint8_t rm,
                                   uint8_t cond, uint8_t rd);

/**
CSET 指令用于根据条件设置目标寄存器的值。如果条件为真，则将目标寄存器设置为
1；如果条件为假，则将目标寄存器设置为 0。
 */
static uint32_t conditional_set_alias(uint8_t sf, uint8_t cond, uint8_t rd);

/**
CSET
指令用于根据条件设置目标寄存器的值。如果条件为真，则将目标寄存器所有位设置为1；如果条件为假，则将目标寄存器设置为
0。
 */
static uint32_t conditional_set_mask(uint8_t sf, uint8_t cond, uint8_t rd);

/**
CSINC
指令是条件选择递增指令。它根据条件的真假，将第一个源寄存器的值或第二个源寄存器的值加
1
后的结果写入目标寄存器。如果条件为真，则将第一个源寄存器的值写入目标寄存器；如果条件为假，则将第二个源寄存器的值加
1 后的结果写入目标寄存器。
 */
static uint32_t conditional_select_increment_returns(uint8_t sf, uint8_t rn,
                                                     uint8_t rm, uint8_t cond,
                                                     uint8_t rd);
/**
CSINV
指令是条件选择取反指令。它根据条件的真假，将第一个源寄存器的值或第二个源寄存器的按位取反后的值写入目标寄存器。如果条件为真，
则将第一个源寄存器的值写入目标寄存器；如果条件为假，则将第二个源寄存器的按位取反后的值写入目标寄存器。
 */
static uint32_t condition_select_invert_returns(uint8_t sf, uint8_t rn,
                                                uint8_t rm, uint8_t cond,
                                                uint8_t rd);
/** 同上，不过改变符号 */
static uint32_t condition_select_negation_returns(uint8_t sf, uint8_t rn,
                                                  uint8_t rm, uint8_t cond,
                                                  uint8_t rd);
#endif