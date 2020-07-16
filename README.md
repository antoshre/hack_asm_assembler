# hack_asm_assembler
Hack assembly assembler

Hack is a toy assembly language created for the [nand2tetris](https://www.nand2tetris.org/project06) course.
This project is based on Project 6 of that course.

Assemblers Hack .asm files into an AST suitable for consumption by another process.

##Hack Assembly Example:
`Add.asm` in `examples/`:
```
//Add R0 to R1 and store in R2
@R0 //A=0
D=M //D=M[0]
@R1 //A=1
A=M //A=M[1]
D=D+A //D=M[0]+M[1]
@R2 //A=2
M=D //M[2]=D
```

AST:
```
AST:
A(R0=0)
C(D=M)
A(R1=1)
C(A=M)
C(D=D+A)
A(R2=2)
C(M=D)
```