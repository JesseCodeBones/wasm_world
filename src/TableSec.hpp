#ifndef _wasm_table_sec_
#define _wasm_table_sec_
#include "RefType.hpp"
#include "type/LimitType.hpp"
class TableSec {
private:
  /* data */
  RefType refType;
  LimitType limitType;

public:
  TableSec(RefType &&refType, LimitType &&limitType)
      : refType(refType), limitType(limitType) {
  }

  RefType getRefType() {
    return refType;
  }
  LimitType getLimitType() {
    return limitType;
  }
  void setRefType(RefType refType) {
    this->refType = refType;
  }
  void setLimitType(LimitType limitType) {
    this->limitType = limitType;
  }
};

#endif