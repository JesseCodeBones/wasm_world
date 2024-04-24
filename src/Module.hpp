#ifndef _wasm_module_
#define _wasm_module_
#include <any>
#include <cstdint>
#include <functional>
#include <memory>
#include <stdint.h>
#include <vector>
#include "Code.hpp"
#include "CustomSec.hpp"
#include "Data.hpp"
#include "ElemSec.hpp"
#include "ExportSec.hpp"
#include "FunctionSec.hpp"
#include "GlobalSec.hpp"
#include "ImportSec.hpp"
#include "MemSec.hpp"
#include "TableSec.hpp"
#include "TypeSec.hpp"
#include "instruction/Instruction.hpp"
#include "runtime/Runtime.hpp"
class Module {
private:
public:
  uint32_t magic;
  uint32_t version;
  std::vector<CustomSec> customSec;
  std::vector<TypeSec> typeSec;
  std::vector<ImportSec> importSec;
  std::vector<FunctionSec> functionSec;
  std::vector<TableSec> tableSec;
  std::vector<MemSec> memSec;
  std::vector<GlobalSec> globalSec;
  std::vector<ExportSec> exportSec;
  uint32_t startIndex;
  std::vector<ElemSec> elemSec;
  std::vector<Code> codeSec;
  std::vector<Data> dataSec;
  Runtime runtime;
  void dumpInfo();
  void checkImport();
  void execute();
  std::unique_ptr<Instruction> compileInstruction(InstructionType opcode,
                                                  std::vector<uint8_t> &content,
                                                  uint32_t &pos);
  std::unique_ptr<std::vector<std::unique_ptr<Instruction>>>
  compileExpression(std::vector<uint8_t> &content, uint32_t &pos);
  void compileFunction(uint32_t functionIndex);
  std::any runFunction(uint32_t functionIndex);
  // void runExpression(std::vector<uint8_t> &body, uint32_t &position);
  // void runInstruction(std::vector<uint8_t> &body, uint8_t opcode,
  //                     uint32_t &position);

  static std::function<void(Module *)> externalFunSignature;
};
#endif