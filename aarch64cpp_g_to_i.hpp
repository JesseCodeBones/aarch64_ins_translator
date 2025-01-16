#ifndef AARCH64CPP_G_TO_I_HPP
#define AARCH64CPP_G_TO_I_HPP
#include <cstdint>

/**
GMI
Tag Mask Insert inserts the tag in the first source register into the excluded
set specified in the second source register, writing the new excluded set to the
destination register.
MTE 的工作原理
标签存储：MTE 在内存地址的高位存储标签。每个内存块（通常是 16
字节）都有一个关联的标签。
标签检查：在内存访问时，处理器会检查内存地址中的标签是否与存储在内存中的标签匹配。如果标签不匹配，则会触发错误。


详细解释
标签的存储：

标签是附加在物理内存地址上的元数据，通常每 16 字节的内存块有一个 4-bit 的标签。
标签存储在处理器的标签存储器中，而不是在普通的内存地址空间中。
标签的使用：

当处理器访问内存时，它会检查内存地址中的标签是否与存储在标签存储器中的标签匹配。
如果标签不匹配，处理器会触发一个错误（例如，标签错误异常）。
虚拟内存与物理内存：

虚拟内存地址空间是由操作系统管理的，用于提供进程隔离和内存保护。
标签是在物理内存层面进行标记的，因此虚拟内存地址空间中看不到这些标签。
当虚拟地址被转换为物理地址时，处理器会使用物理地址中的标签进行检查。

 */
static uint32_t tag_mask_insert(uint8_t xm, uint8_t xn, uint8_t xd);

/**
HLT (Halt) 指令是一种停止指令，用于生成一个 Halt Instruction
调试事件，从而导致进入调试状态。该指令通常用于调试目的，以便在特定点暂停程序执行并进入调试模式。
 */
static uint32_t halt_instruction(uint16_t imm16);

/**
Hypervisor Call causes an exception to EL2. Software executing at EL1 can use
this instruction to call the hypervisor to request a service.

The HVC instruction is undefined:

When EL3 is implemented and SCR_EL3.HCE is set to 0.
When EL3 is not implemented and HCR_EL2.HCD is set to 1.
When EL2 is not implemented.
At EL1 if EL2 is not enabled in the current Security state.
At EL0.
 */
static uint32_t hypervisor_call(uint16_t imm16);

static uint32_t instruction_cache(uint8_t op1, uint8_t CRm, uint8_t op2,
                                  uint8_t Rt);
/**
IRG
Insert Random Tag inserts a random Logical Address Tag into the address in the
first source register, and writes the result to the destination register. Any
tags specified in the optional second source register or in GCR_EL1.Exclude are
excluded from the selection of the random Logical Address Tag.
memory tag related
 */

/**
ISB (Instruction Synchronization Barrier) 指令用于刷新处理单元 (PE)
的流水线，并作为上下文同步事件。它确保在 ISB
指令之前的所有指令都已执行完毕，并且其效果对 ISB
指令之后的指令可见。这对于确保指令序列的正确性和一致性非常重要，尤其是在修改系统控制寄存器或执行自修改代码时
 */
static uint32_t instruction_synchronization_barrier(uint8_t CRm);
#endif