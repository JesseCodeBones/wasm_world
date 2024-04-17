#ifndef _wasm_instruction_
#define _wasm_instruction_

#include <cstdint>
enum class InstructionType : uint8_t {

    NOP = 0x01,

    I32CONST = 0x41,
    I64CONST = 0x42,
    F32CONST = 0x43,
    F64CONST = 0x44
};

class Instruction {
public:
    InstructionType type = InstructionType::NOP;
};

#endif