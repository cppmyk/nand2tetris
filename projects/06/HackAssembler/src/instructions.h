#include <stdbool.h>
#include <stdio.h>

#include "hash_table.h"

#ifndef HACKASSEMBLER__INSTRUCTIONS_H_
#define HACKASSEMBLER__INSTRUCTIONS_H_

struct CInstructionFixed {
  // first 2 fixed bits (==1) + '\0'
  char binary[3];
};

struct CInstructionDest {
  // d1 d2 d3 bits + '\0'
  bool ram;
  bool a_register;
  bool d_register;
  char binary[4];
};

enum CompOperation {
  Zero,
  One,
  MinusOne,
  DRegister,
  ARegister,
  NotDRegister,
  NotARegister,
  MinusDRegister,
  MinusARegister,
  DRegisterPlusOne,
  ARegisterPlusOne,
  DRegisterMinusOne,
  ARegisterMinusOne,
  DRegisterPlusARegister,
  DRegisterMinusARegister,
  ARegisterMinusDRegister,
  DRegisterAndARegister,
  DRegisterOrARegister,
  RAM,
  NotRAM,
  MinusRAM,
  RAMPlusOne,
  RAMMinusOne,
  DRegisterPlusRAM,
  DRegisterMinusRAM,
  RAMMinusDRegister,
  DRegisterAndRAM,
  DRegisterOrRAM,
};

struct CInstructionComp {
  // a c1 c2 c3 c4 c5 c6 bits + '\0'
  enum CompOperation operation;
  char binary[8];
};

struct CInstructionJump {
  // j1 j2 j3 bits + '\0'
  bool greater;
  bool equal;
  bool lower;
  char binary[4];
};

struct CInstruction {
  // dest = comp ; jump
  char instruction_bit;
  struct CInstructionFixed fixed;
  struct CInstructionComp comp;
  struct CInstructionDest dest;
  struct CInstructionJump jump;
};

struct AInstruction {
  char instruction_bit;
  int value;              // 10-base value
  char binary_value[16];  // 15 bits + '\0'
};

struct AInstruction create_a_instruction(ht_value_t value);
struct CInstruction create_c_instruction(struct CInstructionComp comp,
                                         struct CInstructionDest dest,
                                         struct CInstructionJump jump);

struct CInstructionComp create_c_instruction_comp(
    const char* asm_comp_instruction);
struct CInstructionJump create_c_instruction_jump(
    const char* asm_jump_instruction);
struct CInstructionDest create_c_instruction_dest(
    const char* asm_dest_instruction);

void fprint_a_instruction(FILE* stream, const struct AInstruction* instruction);
void fprint_c_instruction(FILE* stream, const struct CInstruction* instruction);
#endif  // HACKASSEMBLER__INSTRUCTIONS_H_
