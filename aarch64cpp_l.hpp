#ifndef AARCH64CPP_L_HPP
#define AARCH64CPP_L_HPP
#include <cstdint>

/**
 * LD64B
 * 你提到的LD64B是 ARM 架构中的一条原子加载指令，主要用于 64 字节数据的原子性加载操作
 *
 *  指令全称与核心功能
    全称：Single-copy Atomic 64-byte Load（单拷贝原子 64 字节加载）。
    核心功能：从内存中原子性地加载 8 个 64 位双字（共 64 字节），并将其写入连续的通用寄存器（Xt到X(t+7)）。
 */
static uint32_t atomic_single_copy_64_bytes(uint8_t Rn, uint8_t Rt);


/**
 * LDADD、LDADDA、LDADDAL 和 LDADDL
 *
 *
    从内存中原子性地加载一个 32 位字（Word）或 64 位双字（Doubleword）。
    将加载的值与寄存器中的值相加。
    将结果写回内存。
    将最初从内存加载的值返回到目标寄存器。

    32-bit LDADD (size == 10 && A == 0 && R == 0)
    LDADD <Ws>, <Wt>, [<Xn|SP>]
    32-bit LDADDA (size == 10 && A == 1 && R == 0)
    LDADDA <Ws>, <Wt>, [<Xn|SP>]
    32-bit LDADDAL (size == 10 && A == 1 && R == 1)
    LDADDAL <Ws>, <Wt>, [<Xn|SP>]
    32-bit LDADDL (size == 10 && A == 0 && R == 1)
    LDADDL <Ws>, <Wt>, [<Xn|SP>]
    64-bit LDADD (size == 11 && A == 0 && R == 0)
    LDADD <Xs>, <Xt>, [<Xn|SP>]
    64-bit LDADDA (size == 11 && A == 1 && R == 0)
    LDADDA <Xs>, <Xt>, [<Xn|SP>]
    64-bit LDADDAL (size == 11 && A == 1 && R == 1)
    LDADDAL <Xs>, <Xt>, [<Xn|SP>]
    64-bit LDADDL (size == 11 && A == 0 && R == 1)
    LDADDL <Xs>, <Xt>, [<Xn|SP>]
 */

static uint32_t atomic_load_add(uint8_t size, uint8_t flag_A, uint8_t flag_R, uint8_t Rs, uint8_t Rn, uint8_t Rt);

#endif
