#ifndef _wasm_module_reader_
#define _wasm_module_reader_
#include <cstdint>
#include <memory>
#include <stdint.h>
#include <vector>
#include "../Module.hpp"
#include "../instruction/Instruction.hpp"
#include "ModuleSection.hpp"
class ModuleReader {
public:
  ModuleReader(std::vector<uint8_t> &&src, Module &_module) : data(src), module(_module) {
  }

  void prepareSections();

private:
  std::vector<uint8_t> data;
  Module &module;
  uint32_t pos = 0U;
  ModuleSection memorySection;
  ModuleSection dataSection;
  ModuleSection importSection;
  ModuleSection typeSec;

  uint32_t readUInt32();
  uint8_t readUInt8(std::vector<uint8_t> &binary, uint32_t &ptr);
  void readSection(uint32_t &secSize, std::vector<uint8_t> &secData);
  uint64_t readUnsignedLEB128(std::vector<uint8_t> &binary, uint32_t &ptr);
  std::unique_ptr<Instruction> readSingleInstructionFromExpression(std::vector<uint8_t> &binary,
                                                                   uint32_t &ptr);
  int64_t readSignedLEB128(std::vector<uint8_t> &binary, uint32_t &ptr);
  void handleMemorySection();
  void handleDataInit();
  void handleImport();
  void handleType();
};
#endif