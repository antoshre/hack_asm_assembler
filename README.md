# hack_asm_assembler
Hack assembly assembler.

Hack is a toy assembly language created for the [nand2tetris](https://www.nand2tetris.org/project06) course.
This project is based on Project 6 of that course.

Assemblers Hack .asm files into an AST suitable for consumption by another process.

Status: Functionally complete.  Correctly assembles all 28,375 lines of `examples/Pong.asm`.  Could use a good refactor.

## Installation

```
git clone https://github.com/antoshre/hack_asm_assembler.git
cd hack_asm_assmbler
mkdir build
cd build
cmake ..
cmake --build .
```

## Requirements 

Requires C++20 for CTRE support.

## Usage

`examples\print_ast.cpp`:

```
std::ifstream file("Add.asm", std::ios::in);
if (!file) {
    std::cerr << "Failed to open file.";
    return -1;
}
AST ast{AsmFile(file)};
std::cout << ast;

auto binary = ast.to_binary();
for(const auto& line : binary) {
    std::cout  << line << '\n';
}
```
produces:
```
AST:
    A(R0=0)
    C(D=M)
    A(R1=1)
    C(A=M)
    C(D=D+A)
    A(R2=2)
    C(M=D)

Symbol Table:
Labels:
Symbols:

0000000000000000
1111110000010000
0000000000000001
1111110000100000
1110000010010000
0000000000000010
1110001100001000
```