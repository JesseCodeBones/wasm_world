
#include "ModuleReader.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <utility>
#include <vector>
#include "../instruction/NumericInstruction.hpp"
#include "../type/ValType.hpp"

void ModuleReader::handleAfterPrepareModuleBeforeRun() {
  // 1. prepare memory
  if (!module.memSec.empty()) {
    module.runtime.linkMemory(std::move(module.memSec.front().memory));
  }

  // 2. prepare table
  if (!module.tableSec.empty()) {
    std::vector<uint32_t> table;
    table.resize(module.tableSec.front().getLimitType().max);
    std::fill(table.begin(), table.end(), static_cast<uint32_t>(-1));
    module.runtime.linkTable(std::move(table));
  }
  // fixme 3. prepare element
  if (!module.elemSec.empty()) {
    for (auto &elem : module.elemSec) {
      module.runtime.getTable()[elem.getIndex()] = elem.getValue();
    }
  }
}

void ModuleReader::prepareModule() {

  uint32_t magic = readUInt32();
  uint32_t version = readUInt32();
  assert(magic == 0x6d736100);
  assert(version == 1);
  uint8_t sectionId;
  sectionId = readUInt8(data, pos);
  while (true) {
    switch (sectionId) {
    case 0x0: { // custom
      readSection(customSection.size, customSection.content);
      break;
    }
    case 0x1: { // type
      readSection(typeSec.size, typeSec.content);
      handleType(); // extract import info at the beginning
      break;
    }
    case 0x2: { // import
      readSection(importSec.size, importSec.content);
      handleImport();
      break;
    }
    case 0x3: { // function
      readSection(functionSec.size, functionSec.content);
      handleFunction();
      break;
    }
    case 0x4: { // table
      readSection(tableSec.size, tableSec.content);
      handleTable();
      break;
    }
    case 0x5: // memory
    {
      readSection(memorySection.size, memorySection.content);
      handleMemorySection(); // handle memory initialize in the beginning
      break;
    }
    case 0x6: // global
    {
      readSection(globalSec.size, globalSec.content);
      handleGlobal();
      break;
    }
    case 0x7: // export
    {
      readSection(exportSec.size, exportSec.content);
      handleExport();
      break;
    }
    case 0x8: // start
    {
      readSection(startSec.size, startSec.content);
      handleStart();
      break;
    }
    case 0x9: // element
    {
      readSection(elementSec.size, elementSec.content);
      handleElement();
      break;
    }
    case 0xa: // code
    {
      readSection(codeSec.size, codeSec.content);
      handleCode();
      break;
    }
    case 0xb: // data
    {
      readSection(dataSection.size, dataSection.content);
      handleDataInit();
      break;
    }
    case 0xc: // data count
    {
      readSection(dataCountSection.size, dataCountSection.content);
      break;
    }
    default: {
      throw std::runtime_error("unsupported section" +
                               std::to_string(sectionId));
    }
    }
    if (pos >= data.size()) {
      break;
    } else {
      sectionId = readUInt8(data, pos);
    }
  }

  // post init sections
  handleAfterPrepareModuleBeforeRun();
}

uint32_t ModuleReader::readUInt32() {
  void *ptr = data.data() + pos;
  uint32_t value = *((uint32_t *)ptr);
  pos += 4;
  return value;
}

uint8_t ModuleReader::readUInt8(std::vector<uint8_t> &binary, uint32_t &ptr) {
  void *p = binary.data() + ptr;
  uint8_t value = *((uint8_t *)p);
  ptr += 1;
  return value;
}

void ModuleReader::readSection(uint32_t &secSize,
                               std::vector<uint8_t> &secData) {
  secSize = static_cast<uint32_t>(readUnsignedLEB128(data, pos));
  std::copy(data.cbegin() + pos, data.cbegin() + pos + secSize,
            std::back_inserter(secData));
  pos += secSize;
}

uint64_t ModuleReader::readUnsignedLEB128(std::vector<uint8_t> &binary,
                                          uint32_t &ptr) {
  const uint8_t *p = binary.data() + ptr;
  uint64_t Value = 0;
  unsigned Shift = 0;
  do {
    if (ptr == binary.size()) {
      throw std::runtime_error(
          "read leb128 failed because it comes to the end of the file");
    }
    uint64_t Slice = *p & 0x7f;
    if (Shift >= 64 || Slice << Shift >> Shift != Slice) {
      return 0;
    }
    Value += uint64_t(*p & 0x7f) << Shift;
    Shift += 7;
  } while (*p++ >= 128);
  ptr = static_cast<uint32_t>(p - binary.data());
  return Value;
}

int64_t ModuleReader::readSignedLEB128(std::vector<uint8_t> &binary,
                                       uint32_t &ptr) {
  const uint8_t *p = binary.data() + ptr;
  int64_t Value = 0;
  unsigned Shift = 0;
  uint8_t Byte;
  do {
    if (ptr == binary.size()) {
      throw std::runtime_error(
          "read leb128 failed because it comes to the end of the file");
    }
    Byte = *p++;
    Value |= (uint64_t(Byte & 0x7f) << Shift);
    Shift += 7;
  } while (Byte >= 128);
  if (Shift < 64 && (Byte & 0x40)) {
    Value |= (UINT64_MAX) << Shift;
  }
  ptr = static_cast<uint32_t>(p - binary.data());
  return Value;
}

void ModuleReader::handleMemorySection() {

  // 1. read section content

  uint32_t sectionReaderPos = 0;
  uint32_t count = static_cast<uint32_t>(
      readUnsignedLEB128(memorySection.content, sectionReaderPos));
  while (count > 0) {
    LimitType limit;
    uint8_t tag = readUInt8(memorySection.content, sectionReaderPos);
    uint8_t min = readUInt8(memorySection.content, sectionReaderPos);
    limit.tag = tag;
    limit.min = min;
    if (tag == 1) {
      uint8_t max = readUInt8(memorySection.content, sectionReaderPos);
      limit.max = max;
    }
    module.memSec.emplace_back(std::move(limit));
    count--;
  }
}

void ModuleReader::handleGlobal() {
  uint32_t ptr = 0;
  uint32_t globalCount =
      static_cast<uint32_t>(readUnsignedLEB128(globalSec.content, ptr));
  while (globalCount > 0) {
    ValType globalType =
        static_cast<ValType>(readUInt8(globalSec.content, ptr));
    ValItem global = {.type = globalType};
    uint8_t mul = readUInt8(globalSec.content, ptr);
    if (mul == 0x00) {
      global.multable = false;
    } else {
      global.multable = true;
    }
    std::unique_ptr<Instruction> instruction =
        readSingleInstructionFromExpression(globalSec.content, ptr);
    switch (instruction->type) {
    case InstructionType::I32CONST: {
      int32_t i32Const =
          instruction->castRightRef<I32ConstInstruction>().getValue();
      StackItemValue value = {.i32 = i32Const};
      global.value = value;
      break;
    }
    case InstructionType::I64CONST: {
      int64_t i64Const =
          instruction->castRightRef<I64ConstInstruction>().getValue();
      StackItemValue value = {.i64 = i64Const};
      global.value = value;
      break;
    }
    case InstructionType::F32CONST: {
      float f32Const =
          instruction->castRightRef<F32ConstInstruction>().getValue();
      StackItemValue value = {.f32 = f32Const};
      global.value = value;
      break;
    }
    case InstructionType::F64CONST: {
      double f64Const =
          instruction->castRightRef<F64ConstInstruction>().getValue();
      StackItemValue value = {.f64 = f64Const};
      global.value = value;
      break;
    }
    default: {
      throw std::runtime_error("unsupported global set instruction");
    }
    }
    module.runtime.addGlobal(std::move(global));
    globalCount--;
  }
}

void ModuleReader::handleDataInit() {
  uint32_t sectionReaderPos = 0U;
  uint32_t count = static_cast<uint32_t>(
      readUnsignedLEB128(dataSection.content, sectionReaderPos));
  while (count > 0) {
    uint8_t tag = readUInt8(dataSection.content, sectionReaderPos);
    switch (tag) {
    case 0: { // expr
      std::unique_ptr<Instruction> instruction =
          readSingleInstructionFromExpression(dataSection.content,
                                              sectionReaderPos);
      switch (instruction->type) {
      case InstructionType::I32CONST: {
        uint32_t valuePos =
            instruction->castRightRef<I32ConstInstruction>().getValue();
        uint32_t bytesSize = static_cast<uint32_t>(
            readUnsignedLEB128(dataSection.content, sectionReaderPos));
        std::vector<uint8_t> bytesContent;
        std::copy(dataSection.content.cbegin() + sectionReaderPos,
                  dataSection.content.cbegin() + sectionReaderPos + bytesSize,
                  std::back_inserter(bytesContent));
        sectionReaderPos += bytesSize;
        if (module.memSec.size() == 0) {
          throw std::runtime_error("invalid memory setting for module");
        }
        module.memSec.front().setMemory(valuePos, bytesContent, 0, bytesSize);
        break;
      }
      default: {
        throw std::runtime_error("invalid data expression");
        break;
      }
      }
      break;
    }
    case 1: { // passive TODO
      throw std::runtime_error("not implemented");
      break;
    }
    case 2: { // expr with memory index TODO
      throw std::runtime_error("not implemented");
      break;
    }
    default: throw std::runtime_error("invalid data tag");
    }
    count--;
  }
}

std::unique_ptr<Instruction>
ModuleReader::readSingleInstructionFromExpression(std::vector<uint8_t> &binary,
                                                  uint32_t &ptr) {
  uint8_t opCode = readUInt8(binary, ptr);
  switch (opCode) {
  case static_cast<int>(InstructionType::I32CONST): {
    int32_t value = static_cast<int32_t>(readSignedLEB128(binary, ptr));
    I32ConstInstruction i32Const(value);
    uint8_t endFlag = readUInt8(binary, ptr);
    assert(0x0B == endFlag); // 0x0b is the end of the expression
    return std::make_unique<I32ConstInstruction>(i32Const);
  }
  case static_cast<int>(InstructionType::I64CONST): {
    int64_t value = readSignedLEB128(binary, ptr);
    I64ConstInstruction i64Const(value);
    uint8_t endFlag = readUInt8(binary, ptr);
    assert(0x0B == endFlag); // 0x0b is the end of the expression
    return std::make_unique<I64ConstInstruction>(i64Const);
  }
  case static_cast<int>(InstructionType::F32CONST): {
    float value =
        ModuleReader::bit_cast<float>(read4BytesLittleEndian(binary, ptr));
    F32ConstInstruction f32Const(value);
    uint8_t endFlag = readUInt8(binary, ptr);
    assert(0x0B == endFlag); // 0x0b is the end of the expression
    return std::make_unique<F32ConstInstruction>(f32Const);
  }
  case static_cast<int>(InstructionType::F64CONST): {
    double value =
        ModuleReader::bit_cast<double>(read8BytesLittleEndian(binary, ptr));
    F64ConstInstruction f64Const(value);
    uint8_t endFlag = readUInt8(binary, ptr);
    assert(0x0B == endFlag); // 0x0b is the end of the expression
    return std::make_unique<F64ConstInstruction>(f64Const);
  }
  default: {
    std::stringstream ss;
    ss << "unsupported instruction: " << std::hex << std::to_string(opCode);
    // throw std::runtime_error(ss.str());
    return nullptr;
  }
  }
}

void ModuleReader::handleImport() {
  uint32_t importReadPos = 0;
  uint32_t importCount = static_cast<uint32_t>(
      readUnsignedLEB128(importSec.content, importReadPos));
  while (importCount > 0) {
    // name 1
    uint32_t name1Count = static_cast<uint32_t>(
        readUnsignedLEB128(importSec.content, importReadPos));
    std::string name1;
    std::copy(importSec.content.cbegin() + importReadPos,
              importSec.content.cbegin() + importReadPos + name1Count,
              std::back_inserter(name1));
    importReadPos += name1Count;

    // name 2
    uint32_t name2Count = static_cast<uint32_t>(
        readUnsignedLEB128(importSec.content, importReadPos));
    std::string name2;
    std::copy(importSec.content.cbegin() + importReadPos,
              importSec.content.cbegin() + importReadPos + name2Count,
              std::back_inserter(name2));
    importReadPos += name2Count;

    // type
    uint8_t desc = readUInt8(importSec.content, importReadPos);
    switch (desc) {
    case 0x0: { // function
      uint32_t typeIndex = static_cast<uint32_t>(
          readUnsignedLEB128(importSec.content, importReadPos));
      ImportSec importItem(std::move(name1), std::move(name2),
                           ImportDType::FUNC);
      importItem.setFunctionIndex(typeIndex);
      module.importSec.push_back(std::move(importItem));
      break;
    }
    case 0x1: { // table TODO
      throw std::runtime_error("not implemented");
      break;
    }
    case 0x2: { // mem TODO
      throw std::runtime_error("not implemented");
      break;
    }
    case 0x3: { // global TODO
      throw std::runtime_error("not implemented");
      break;
    }
    default: {
      throw std::runtime_error("in correct import desc");
    }
    }

    importCount--;
  }
  module.checkImport();
}
void ModuleReader::handleType() {
  uint32_t typeReadPos = 0;
  uint32_t typeCount =
      static_cast<uint32_t>(readUnsignedLEB128(typeSec.content, typeReadPos));
  while (typeCount > 0) {
    uint8_t functionType = readUInt8(typeSec.content, typeReadPos);
    assert(functionType == 0x60);
    // read parameter vector
    uint32_t parameterCount =
        static_cast<uint32_t>(readUnsignedLEB128(typeSec.content, typeReadPos));
    std::vector<ValType> parameters;
    while (parameterCount > 0) {
      ValType valueType =
          static_cast<ValType>(readUInt8(typeSec.content, typeReadPos));
      parameters.push_back(valueType);
      parameterCount--;
    }

    // read result vector
    uint32_t resultCount =
        static_cast<uint32_t>(readUnsignedLEB128(typeSec.content, typeReadPos));
    assert(resultCount == 0 || resultCount == 1); // only support single return
    std::vector<ValType> results;
    while (resultCount > 0) {
      ValType valueType =
          static_cast<ValType>(readUInt8(typeSec.content, typeReadPos));
      results.push_back(valueType);
      resultCount--;
    }
    module.typeSec.push_back({std::move(parameters), std::move(results)});
    typeCount--;
  }
}

void ModuleReader::handleExport() {
  uint32_t exportPos = 0;
  uint32_t exportCount =
      static_cast<uint32_t>(readUnsignedLEB128(exportSec.content, exportPos));
  while (exportCount > 0) {
    uint32_t nameCount =
        static_cast<uint32_t>(readUnsignedLEB128(exportSec.content, exportPos));
    std::string name;
    std::copy(exportSec.content.cbegin() + exportPos,
              exportSec.content.cbegin() + exportPos + nameCount,
              std::back_inserter(name));
    exportPos += nameCount;
    uint8_t desc = readUInt8(exportSec.content, exportPos);
    switch (desc) {
      // only handle _start function index
    case 0x0: { // function
      uint32_t index = static_cast<uint32_t>(
          readUnsignedLEB128(exportSec.content, exportPos));
      if (name == "_start") {
        module._startFunctionIndex = index;
      }
      break;
    }
    case 0x1: { // table
      uint32_t index = static_cast<uint32_t>(
          readUnsignedLEB128(exportSec.content, exportPos));
      break;
    }
    case 0x2: { // mem
      uint32_t index = static_cast<uint32_t>(
          readUnsignedLEB128(exportSec.content, exportPos));
      break;
    }
    case 0x3: { // global
      uint32_t index = static_cast<uint32_t>(
          readUnsignedLEB128(exportSec.content, exportPos));
      break;
    }
    default: {
      throw std::runtime_error("invalid export desc");
    }
    }
    exportCount--;
  }
}

void ModuleReader::handleStart() {
  uint32_t startPos = 0;
  module.startIndex =
      static_cast<uint32_t>(readUnsignedLEB128(startSec.content, startPos));
}

void ModuleReader::handleElement() {
  uint32_t elementPos = 0;
  uint32_t elementCount =
      static_cast<uint32_t>(readUnsignedLEB128(elementSec.content, elementPos));
  while (elementCount > 0) {
    uint32_t index = static_cast<uint32_t>(
        readUnsignedLEB128(elementSec.content, elementPos));
    assert(index == 0U);
    auto instruction =
        readSingleInstructionFromExpression(elementSec.content, elementPos);
    if (instruction->type != InstructionType::I32CONST) {
      throw std::runtime_error("invalid element init expression");
    }
    uint32_t offset =
        instruction->castRightRef<I32ConstInstruction>().getValue();
    uint32_t valueCount = static_cast<uint32_t>(
        readUnsignedLEB128(elementSec.content, elementPos));
    while (valueCount > 0) {
      uint32_t value = static_cast<uint32_t>(
          readUnsignedLEB128(elementSec.content, elementPos));
      module.elemSec.push_back({offset, value});
      offset++;
      valueCount--;
    }
    elementCount--;
  }
}

void ModuleReader::handleCode() {

  uint32_t codePos = 0;
  uint32_t codeCount =
      static_cast<uint32_t>(readUnsignedLEB128(codeSec.content, codePos));
  uint32_t index = 0;
  while (codeCount > 0) {
    uint32_t size =
        static_cast<uint32_t>(readUnsignedLEB128(codeSec.content, codePos));
    assert(module.functionSec.at(index).localsAndExpression.size() ==
           0); // no duplicated function
    std::copy(
        codeSec.content.cbegin() + codePos,
        codeSec.content.cbegin() + codePos + size,
        std::back_inserter(module.functionSec.at(index).localsAndExpression));
    codePos += size;
    index++;
    codeCount--;
  }
}

void ModuleReader::handleFunction() {
  uint32_t functionPos = 0;
  uint32_t functionCount = static_cast<uint32_t>(
      readUnsignedLEB128(functionSec.content, functionPos));
  while (functionCount > 0) {
    uint32_t typeIndex = static_cast<uint32_t>(
        readUnsignedLEB128(functionSec.content, functionPos));
    FunctionSec function;
    function.type = module.typeSec.at(typeIndex);
    module.functionSec.push_back(std::move(function));
    functionCount--;
  }
}

uint32_t ModuleReader::read4BytesLittleEndian(std::vector<uint8_t> &binary,
                                              uint32_t &ptr) {
  uint8_t b1 = readUInt8(binary, ptr);
  uint8_t b2 = readUInt8(binary, ptr);
  uint8_t b3 = readUInt8(binary, ptr);
  uint8_t b4 = readUInt8(binary, ptr);
  return b1 | (b2 << 8) | (b3 << (8 * 2)) | (b4 << (8 * 3));
}

uint64_t ModuleReader::read8BytesLittleEndian(std::vector<uint8_t> &binary,
                                              uint32_t &ptr) {
  uint64_t result = uint64_t(read4BytesLittleEndian(binary, ptr));
  result |= uint64_t(read4BytesLittleEndian(binary, ptr)) << 32;
  return result;
}

void ModuleReader::handleTable() {
  uint32_t tablePos = 0;
  uint32_t tableCount =
      static_cast<uint32_t>(readUnsignedLEB128(tableSec.content, tablePos));
  while (tableCount > 0) {
    uint8_t elementType = readUInt8(tableSec.content, tablePos);
    assert(elementType == 0x70 ||
           elementType == 0x6f); // only support functionRef | externalRef
    RefType refType = static_cast<RefType>(elementType);
    LimitType limit;
    uint8_t tag = readUInt8(tableSec.content, tablePos);
    uint8_t min = readUInt8(tableSec.content, tablePos);
    limit.tag = tag;
    limit.min = min;
    if (tag == 1) {
      uint8_t max = readUInt8(tableSec.content, tablePos);
      limit.max = max;
    }
    module.tableSec.emplace_back(std::move(refType), std::move(limit));
    tableCount--;
  }
}
