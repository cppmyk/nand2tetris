# Build a Modern Computer from First Principles: From Nand to Tetris
Nand2Tetris is a project-centered course that explains how to build a modern computer system, from the ground up. I have implemented all the projects, starting with logic chips, memory and CPU implementation, ending with Assembler and complete PC architecture in hardware-description language.
## Content
### [Project 1: Boolean Logic](nand2tetris/tree/master/Hardware/Basic/Logic)
> A typical computer architecture is based on a set of elementary logic gates like And, Or, Mux, etc., as well as their bit-wise versions And16, Or16, Mux16, etc. (assuming a 16-bit machine). This project engages you in the construction of a typical set of basic logic gates. 

### [Project 2: Boolean Arithmetic](nand2tetris/tree/master/Hardware/Basic/Arithmetic)
> The centerpiece of the computer's architecture is the CPU, or Central Processing Unit, and the centerpiece of the CPU is the ALU, or Arithmetic-Logic Unit. In this project you will gradually build a set of chips, culminating in the construction of the ALU chip of the Hack computer. All the chips built in this project are standard, except for the ALU itself, which differs from one computer architecture to another.

### [Project 3: Memory](nand2tetris/tree/master/Hardware/Basic/Memory)
> The computer's main memory, also called Random Access Memory, or RAM, is an addressable sequence of n-bit registers, each designed to hold an n-bit value. In this project you will gradually build a RAM unit. This involves two main issues: (i) how to use gate logic to store bits persistently, over time, and (ii) how to use gate logic to locate ("address") the memory register on which we wish to operate.

### [Project 4: Machine Language Programming](nand2tetris/tree/master/Assembler/Specification/examples)
> Every hardware platform is designed to execute commands in a certain machine language, expressed using agreed-upon binary codes. Writing programs directly in binary code is a possible, yet unnecessary. Instead, we can write such programs using a low-level symbolic language, called assembly, and have them translated into binary code by a program called assembler. In this project you will write some low-level assembly programs, and will be forever thankful for high-level languages like Java and Python.

### [Project 5: Computer Architecture](nand2tetris/tree/master/Hardware)
> In previous projects we've built the computer's basic processing and storage devices (ALU and RAM, respectively). In this project we will put everything together, yielding the complete Hack Hardware Platform. The result will be a general-purpose computer that can run programs written in the Hack machine language.

### [Project 6: The Assembler](nand2tetris/tree/master/Assembler)
> Low-level machine programs are rarely written by humans. Typically, they are generated by compilers. One of the key players in this translation process is the assembler - a program designed to translate code written in a symbolic machine language into code written in binary machine language.

