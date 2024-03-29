# 6502 emulation

## Purpose of project
The main purpose of this project is to learn c++, emulation and the fundamentals of CPU architecture, the 6502 is the cpu of the most popular 8-bit home micro computers and games consoles of the past like the Commodore 64, the first computer I have had experience with, unfortunately I never had the opportunity to delve too deep with the machine as I was very young and the most I could do was load games from disk and write some very basic BASIC.

## Architecture
8 bit CPU with 3 registers addressing at most 64kb of memory via a 16 bit address bus, little endian expecting addresses to be stored in memory least significant byte first.

### Zero Page
The first 256 byte page of memory ($0000 -> $00FF). Most significant byte is always zero making the instruction shorter by one byte and one less memory cycle(fetch) during execution).

### Stack
The second page of memory ($0100 -> $01FF) is the system stack and cannot be relocated.256 byte stack memory.

### Reserved
The last 6 bytes of memory ($FFFA -> $FFFF)
	- non-maskable interrupt handler ($FFFA/B)
	- power on reset location ($FFFC/D)
	- BRK/interrupt handler ($FFFE/F)

## Goals
- Emulation of C64, Apple 2 and NES.

## Compilation

```sh
g++ main.cpp -o 6502

```

Output from r2 from pdf @main:

```
            ; DATA XREF from entry0 @ 0x105d
			┌ 70: int main (int argc, char **argv, char **envp);
			│           ; var int64_t var_10008h @ rbp-0x10008
			│           ; var int64_t var_10000h @ rbp-0x10000
			│           0x00001125      55             push rbp
			│           0x00001126      4889e5         mov rbp, rsp
			│           0x00001129      4881ec100001.  sub rsp, 0x10010
			│           0x00001130      488d950000ff.  lea rdx, [var_10000h]
			│           0x00001137      488d85f8fffe.  lea rax, [var_10008h]
			│           0x0000113e      4889d6         mov rsi, rdx
			│           0x00001141      4889c7         mov rdi, rax
			│           0x00001144      e867000000     call method CPU::reset(MEM&) ; method.CPU.reset_MEM_
			│           0x00001149      488d950000ff.  lea rdx, [var_10000h]
			│           0x00001150      488d85f8fffe.  lea rax, [var_10008h]
			│           0x00001157      be02000000     mov esi, 2
			│           0x0000115c      4889c7         mov rdi, rax
			│           0x0000115f      e8ea010000     call method CPU::execute(unsigned int, MEM&) ; method.CPU.execute_unsigned_int__MEM_
			│           0x00001164      b800000000     mov eax, 0
			│           0x00001169      c9             leave
			└           0x0000116a      c3             ret

```
