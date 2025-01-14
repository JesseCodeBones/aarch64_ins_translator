#ifndef AARCH64CPP_D_HPP
#define AARCH64CPP_D_HPP
#include <cstdint>

/**
DC
data cache操作
DC 指令用于执行数据缓存操作。它是 SYS 指令的别名，具体操作取决于 op0, op1, CRn,
CRm, 和 op2 的值。常见的数据缓存操作包括清除缓存、无效缓存、清除并无效缓存等。

// 清除数据缓存的某个范围
DC CVAU, X0  // 清除以 X0 为基地址的数据缓存

 */
static uint32_t data_cache(uint8_t op1, uint8_t CRm, uint8_t op2, uint8_t rt);

/**
DCPS1 指令用于在调试状态下将处理单元 (PE) 的状态更改为
EL1。当在调试状态下执行时：

如果在 EL0 执行，则将当前异常级别和堆栈指针 (SP) 更改为 EL1，使用 SP_EL1。
否则，如果在 ELx 执行，则选择 SP_ELx。
DCPS1 指令的目标异常级别是：

如果指令在 EL0 执行，则为 EL1。
否则，为指令执行时的异常级别。


 */
static uint32_t debug_change_pe_state_el1(uint16_t imm16);
static uint32_t debug_change_pe_state_el2(uint16_t imm16);
static uint32_t debug_change_pe_state_el3(uint16_t imm16);

/**
DGH
 Data Gathering Hint
// 先前的内存访问操作
LDR X0, [X1]  // 从地址 X1 加载数据到 X0
STR X2, [X3]  // 将数据 X2 存储到地址 X3

// 使用 DGH 指令
DGH

// 后续的内存访问操作
LDR X4, [X5]  // 从地址 X5 加载数据到 X4
STR X6, [X7]  // 将数据 X6 存储到地址 X7

在这个例子中，DGH 指令提示处理器不要将 DGH 指令之前的内存访问（LDR X0, [X1] 和
STR X2, [X3]）与 DGH 指令之后的内存访问（LDR X4, [X5] 和 STR X6,
[X7]）合并为单个内存事务。
 */
static uint32_t data_gathering_hint();

/**
DMB (Data Memory Barrier)
指令是一种内存屏障，确保对内存访问的观察顺序。它用于确保在 DMB
指令之前的所有内存访问在 DMB
指令之后的任何内存访问之前完成。这对于多处理器系统中的内存一致性非常重要。


// 先前的内存访问操作
STR X0, [X1]  // 将数据 X0 存储到地址 X1
STR X2, [X3]  // 将数据 X2 存储到地址 X3

// 使用 DMB 指令确保内存访问顺序
DMB SY

// 后续的内存访问操作
LDR X4, [X5]  // 从地址 X5 加载数据到 X4
LDR X6, [X7]  // 从地址 X7 加载数据到 X6

在这个例子中，DMB SY 指令确保在 DMB 指令之前的所有内存访问（STR X0, [X1] 和 STR
X2, [X3]）在 DMB 指令之后的任何内存访问（LDR X4, [X5] 和 LDR X6,
[X7]）之前完成。
 */
static uint32_t data_memory_barrier(uint8_t CRm);

/**
调试状态下恢复处理器的进程状态。它通常用于从调试状态恢复到正常执行状态。

调试状态
调试状态是处理器进入的一种特殊状态，用于调试和诊断目的。在调试状态下，
处理器可以执行调试指令，访问调试寄存器，并进行各种调试操作。调试状态通常由调试器（如
JTAG 或调试软件）触发，用于检查和修改处理器的状态、内存和寄存器。

进程状态
进程状态是处理器在正常执行程序时的状态。它包括处理器的当前执行级别（如
EL0、EL1、EL2、EL3），以及与当前执行的进程相关的所有寄存器和内存状态。进程状态用于管理和执行用户程序和操作系统内核代码。
*/
static uint32_t debug_restore_process_state();

/**
DSB (Data Synchronization Barrier)
指令是一种内存屏障，确保内存访问的完成。它用于确保在 DSB
指令之前的所有内存访问在 DSB 指令之后的任何内存访问之前完成。
DMB (Data Memory Barrier)


DMB 指令确保在 DMB 指令之前的所有内存访问在 DMB
指令之后的任何内存访问之前被观察到。它确保内存访问的顺序，但不一定确保所有内存访问操作已经完成。这意味着在
DMB 指令之后的内存访问可以开始，但它们必须在 DMB
指令之前的内存访问之后被观察到。

DSB (Data Synchronization Barrier)
DSB 指令确保在 DSB 指令之前的所有内存访问在 DSB
指令之后的任何内存访问之前完成。它不仅确保内存访问的顺序，还确保所有内存访问操作已经完成。这意味着在
DSB 指令之后的任何内存访问都不会开始，直到 DSB
指令之前的所有内存访问都完成为止。
 */
static uint32_t data_synchronization_barrier(uint8_t CRm);
/**
DVP

DVP (Data Value Prediction Restriction by Context)
指令的目的是防止数据值预测，该预测基于特定执行上下文中从先前执行中收集的信息来预测执行地址。它确保在
DVP
指令之后按程序顺序出现的指令不能利用先前执行上下文的数据值预测结果进行推测执行。这主要用于防止推测执行漏洞，例如
Spectre 和 Meltdown，这些漏洞可能导致敏感数据泄露。

// 先前的内存访问操作
LDR X0, [X1]  // 从地址 X1 加载数据到 X0
ADD X2, X0, X3  // 使用加载的数据进行计算

// 使用 DVP 指令限制数据值预测
DVP

// 后续的内存访问操作
STR X2, [X4]  // 将计算结果存储到内存
在这个例子中，LDR 和 ADD
指令可能会被推测执行。攻击者可能会利用这些指令的数据值预测结果来推测执行后续的指令，从而访问和泄露敏感数据。

通过在关键位置使用 DVP 指令，可以防止在 DVP
指令之后按程序顺序出现的指令利用先前执行上下文的数据值预测结果进行推测执行，从而提高程序的安全性。
 */
static uint32_t data_value_prediction(uint8_t rt);

#endif // AARCH64CPP_D_HPP