#ifndef _wasm_module_
#define _wasm_module_
#include <stdint.h>
#include <vector>
#include "CustomSec.hpp"
#include "TypeSec.hpp"
#include "ImportSec.hpp"
#include "FunctionSec.hpp"
#include "TableSec.hpp"
#include "MemSec.hpp"
#include "GlobalSec.hpp"
#include "ExportSec.hpp"
#include "ElemSec.hpp"
#include "Code.hpp"
#include "Data.hpp"  
class Module
{
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

};
#endif