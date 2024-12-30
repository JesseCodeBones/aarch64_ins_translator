#include <stdint.h>
class Aarch64CPP{
public:

    // https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADC--Add-with-Carry-

    /**
        @param setFlags 0 32bit, 1 64bit


        integer d = UInt(Rd);
        integer n = UInt(Rn);
        integer m = UInt(Rm);
        integer datasize = if sf == '1' then 64 else 32;
        boolean sub_op = (op == '1');
        boolean setflags = (S == '1');

        bits(datasize) result;
        bits(datasize) operand1 = X[n, datasize];
        bits(datasize) operand2 = X[m, datasize];
        bits(4) nzcv;
        if sub_op then
            operand2 = NOT(operand2);
        (result, nzcv) = AddWithCarry(operand1, operand2, PSTATE.C);
        if setflags then
            PSTATE.<N,Z,C,V> = nzcv;

        X[d, datasize] = result;
     */
    static uint32_t adc(uint8_t sf, uint8_t subop, uint8_t setflags, uint8_t d, uint8_t n, uint8_t m);
        
    // {
    //     return 42U;
    // }
    
};