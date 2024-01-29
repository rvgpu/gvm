#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <elf.h>

#include <llvm/BinaryFormat/MsgPackDocument.h>

namespace cuda {

class metadata {
public:
    metadata(uint64_t addr, uint32_t size);
    
private:
    char *m_name;

    llvm::msgpack::DocNode lookup(llvm::msgpack::DocNode &root, const char *key);
};

} // namespace cuda