#include <stdio.h>
#include <stdlib.h>

// timestamp 17:09

using Byte = unsigned char; // 8 bits
using Word = unsigned short; // 16 bits
using u32 = unsigned int; // workaround for memory intialise function

struct MEM{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte data[MAX_MEM];

    void initialise() {
        for ( u32 i = 0; i < MAX_MEM; i++){
            data[i] = 0;
        }
    }

	// get a byte out of memory (hacky, needs fix)
	Byte operator[] ( u32 Address ) const {
		return data[Address];
	}
};

struct CPU{

	//http://www.obelisk.me.uk/6502/registers.html
    Word PC; // Program counter
    Word SP; // Stack Pointer

    Byte A, X, Y; // Registers

    // Processor status flags set by bits
	// set up as Bitfields
    Byte C : 1; // Carry
    Byte Z : 1; // Zero
    Byte I : 1; // Interrupt Disable
    Byte D : 1; // Decimal Mode
    Byte B : 1; // Break Command
    Byte V : 1; // Overflow
    Byte N : 1; // Negative

    void reset( MEM& memory){
		// c64-wiki.com/wiki/Reset_(Process)
        // Reset Vector Address $FFFC
        PC = 0xFFFC;
        SP = 0x0100; // starts off in zero page at $00FF but moves to top of stack at $0100
        C = I = Z = D = B = V = N = 0;
        A = X = Y =0;
        memory.initialise();
    }

	Byte getByte(u32& clockCycles, MEM& memory){
		Byte data = memory[PC]; // read program counter
		PC++;
		clockCycles--; // clock tends towards zero so instruction can finish for now
		return data;
	}

	static constexpr Byte
		OP_LDA_IM = 0xA9; // Load Accumulator in immediate mode setting zero and negative flags as appropriate

	void execute( u32 clockCycles, MEM& memory){
		while(clockCycles > 0){

			Byte instruction = getByte(clockCycles, memory);
			switch(instruction){
				case OP_LDA_IM:{
					Byte Value = getByte(clockCycles, memory);
					A = Value;
					Z = (A==0); // if A is 0
					N = (A & 0b1000000) > 0; // if bit 7 of A is set
				} break;
			}
		}
	}
};


int main() {
    MEM mem;
    CPU cpu;
    cpu.reset( mem );
	cpu.execute( 2, mem ); // 2 cycles needed for accumulator http://www.obelisk.me.uk/6502/reference.html#LDA
    return 0;
}
