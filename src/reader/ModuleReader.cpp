
#include "ModuleReader.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <sys/types.h>
#include <vector>
#include "../instruction/I32ConstInstruction.hpp"
#include "../type/ValType.hpp"
void ModuleReader::prepareSections() {

  uint32_t magic = readUInt32();
  uint32_t version = readUInt32();
  assert(magic == 0x6d736100);
  assert(version == 1);
  std::cout << "OK!" << std::endl;
  uint8_t sectionId;
  sectionId = readUInt8(data, pos);
  while (true) {
    switch (sectionId) {
      // fix me: 03 wasm contains many unhandled section
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
      break;
    }
    case 0x4: { // table
      readSection(tableSec.size, tableSec.content);
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
      break;
    }
    case 0x7: // export
    {
      readSection(exportSec.size, exportSec.content);
      break;
    }
    case 0x8: // start
    {
      readSection(startSec.size, startSec.content);
      break;
    }
    case 0x9: // element
    {
      readSection(elementSec.size, elementSec.content);
      break;
    }
    case 0xa: // element
    {
      readSection(codeSec.size, codeSec.content);
      break;
    }
    case 0xb: // data
    {
      readSection(dataSection.size, dataSection.content);
      handleDataInit();
      break;
    }
    default: break;
    }
    if (pos >= data.size()) {
      break;
    } else {
      sectionId = readUInt8(data, pos);
    }
  }
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
  ptr = p - binary.data();
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
  if (Shift < 64 && (Byte & 0x40))
    Value |= (-1ULL) << Shift;
  ptr = p - binary.data();
  return Value;
}

void ModuleReader::handleMemorySection() {

  // 1. read section content

  uint32_t sectionReaderPos = 0;
  uint32_t count = readUnsignedLEB128(memorySection.content, sectionReaderPos);
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

void ModuleReader::handleDataInit() {
  uint32_t sectionReaderPos = 0U;
  uint32_t count = readUnsignedLEB128(dataSection.content, sectionReaderPos);
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
        uint32_t bytesSize =
            readUnsignedLEB128(dataSection.content, sectionReaderPos);
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
    int32_t value = readSignedLEB128(binary, ptr);
    I32ConstInstruction i32Const(value);
    assert(0x0B == readUInt8(binary, ptr)); // 0x0b is the end of the expression
    return std::make_unique<I32ConstInstruction>(i32Const);
  }
  default: {
    throw std::runtime_error("unsupported instruction");
  }
  }
}

void ModuleReader::handleImport() {
  uint32_t importReadPos = 0;
  uint32_t importCount = readUnsignedLEB128(importSec.content, importReadPos);
  while (importCount > 0) {
    // name 1
    uint32_t name1Count = readUnsignedLEB128(importSec.content, importReadPos);
    std::string name1;
    std::copy(importSec.content.cbegin() + importReadPos,
              importSec.content.cbegin() + importReadPos + name1Count,
              std::back_inserter(name1));
    importReadPos += name1Count;

    // name 2
    uint32_t name2Count = readUnsignedLEB128(importSec.content, importReadPos);
    std::string name2;
    std::copy(importSec.content.cbegin() + importReadPos,
              importSec.content.cbegin() + importReadPos + name2Count,
              std::back_inserter(name2));
    importReadPos += name2Count;

    // type
    uint8_t desc = readUInt8(importSec.content, importReadPos);
    switch (desc) {
    case 0x0: { // function
      uint32_t typeIndex = readUnsignedLEB128(importSec.content, importReadPos);
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
  uint32_t typeCount = readUnsignedLEB128(typeSec.content, typeReadPos);
  while (typeCount > 0) {
    assert(readUInt8(typeSec.content, typeReadPos) == 0x60);
    // read parameter vector
    uint32_t parameterCount = readUnsignedLEB128(typeSec.content, typeReadPos);
    std::vector<ValType> parameters;
    while (parameterCount > 0) {
      ValType valueType =
          static_cast<ValType>(readUInt8(typeSec.content, typeReadPos));
      parameters.push_back(valueType);
      parameterCount--;
    }

    // read result vector
    uint32_t resultCount = readUnsignedLEB128(typeSec.content, typeReadPos);
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