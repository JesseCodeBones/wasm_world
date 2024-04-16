
#include "ModuleReader.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>
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
    case 0x5: // memory
    {
      readSection(memorySection.size, memorySection.content);
      handleMemorySection(); // handle memory initialize in the begining
      break;
    }
    case 0xb: // data
    {
      readSection(dataSection.size, dataSection.content);
      break;
    }
    default:
      break;
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
  std::copy(data.begin() + pos, data.begin() + pos + secSize,
            std::back_inserter(secData));
  pos+=secSize;
}

uint64_t ModuleReader::readUnsignedLEB128(std::vector<uint8_t> &binary, uint32_t &ptr) {
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

int64_t ModuleReader::readSignedLEB128() {
  // TODO fix it
  return 0;
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
    count --;
  }
}