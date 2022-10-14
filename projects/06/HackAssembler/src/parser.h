#ifndef HACKASSEMBLER__PARSER_H_
#define HACKASSEMBLER__PARSER_H_

char* divide_c_instruction_dest(const char* asm_instruction);

char* divide_c_instruction_jump(const char* asm_instruction);

char* divide_c_instruction_comp(const char* asm_instruction);

#endif  // HACKASSEMBLER__PARSER_H_
