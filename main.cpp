#include <stdio.h>
#include <stdlib.h>

// timestamp 17:09

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;

struct CPU{
    
    Word PC; // Program counter
    Word SP; // Stack Pointer

    Byte A, X, Y; // Registers

    // Status Flags set by bits
    Byte C : 1; // Carry
    Byte Z : 1; // Zero
    Byte I : 1; // Interrupt Disable
    Byte D : 1; // Decimal Mode
    Byte B : 1; // Break Command
    Byte V : 1; // Overflow
    Byte N : 1; // Negative

    void Reset( MEM& memory){
        // Reset Vector Address $FFFC
        PC = 0xFFFC;
        SP = 0x0100;
        C = I = Z = D = B = V = N = 0;
        A = X = Y =0;
        memory.Initialise();        
    }
};

struct MEM{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];
    
    void Initialise() {
        for ( u32 i = 0; i < MAX_MEM; i++){
            Data[i] = 0;
        }
    }
};

int main() {
    MEM mem;
    CPU cpu;
    cpu.Reset( mem );
    return 0;
}