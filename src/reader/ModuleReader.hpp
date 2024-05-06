#ifndef _wasm_module_reader_
#define _wasm_module_reader_
#include <cstdint>
#include <cstring>
#include <memory>
#include <stdint.h>
#include <vector>
#include "../Module.hpp"
#include "../instruction/Instruction.hpp"
#include "ModuleSection.hpp"
class ModuleReader {
public:
  ModuleReader(std::vector<uint8_t> &&src, Module &_module)
      : data(src), module(_module) {
  }

  void prepareModule();

  static uint8_t readUInt8(std::vector<uint8_t> &binary, uint32_t &ptr);
  static uint64_t readUnsignedLEB128(std::vector<uint8_t> &binary,
                                     uint32_t &ptr);
  static std::unique_ptr<Instruction>
  readSingleInstructionFromExpression(std::vector<uint8_t> &binary,
                                      uint32_t &ptr);
  static int64_t readSignedLEB128(std::vector<uint8_t> &binary, uint32_t &ptr);
  static uint32_t read4BytesLittleEndian(std::vector<uint8_t> &binary,
                                         uint32_t &ptr);
  static uint64_t read8BytesLittleEndian(std::vector<uint8_t> &binary,
                                         uint32_t &ptr);
  template <class Destination, class Source>
  static Destination bit_cast(const Source &source) {
    static_assert(sizeof(Destination) == sizeof(Source),
                  "bit_cast needs to be between types of the same size");
    static_assert(std::is_trivial_v<Destination> &&
                      std::is_standard_layout_v<Destination>,
                  "non-POD bit_cast undefined");
    static_assert(std::is_trivial_v<Source> &&
                      std::is_standard_layout_v<Source>,
                  "non-POD bit_cast undefined");
    Destination destination;
    std::memcpy(&destination, &source, sizeof(destination));
    return destination;
  }

private:
  std::vector<uint8_t> data;
  Module &module;
  uint32_t pos = 0U;
  ModuleSection memorySection;
  ModuleSection dataSection;
  ModuleSection importSection;
  ModuleSection typeSec;
  ModuleSection importSec;
  ModuleSection functionSec;
  ModuleSection tableSec;
  ModuleSection globalSec;
  ModuleSection exportSec;
  ModuleSection startSec;
  ModuleSection elementSec;
  ModuleSection codeSec;
  uint32_t readUInt32();
  void readSection(uint32_t &secSize, std::vector<uint8_t> &secData);
  void handleMemorySection();
  void handleDataInit();
  void handleImport();
  void handleType();
  void handleStart();
  void handleCode();
  void handleFunction();
  void handleGlobal();
};
#endif