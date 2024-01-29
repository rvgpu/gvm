#include <map>
#include <string>
#include <cstdint>
#include <elf.h>
#include <iostream>

#include "utils/macro.hpp"

#include "metadata.hpp"

namespace cuda {

metadata::metadata(uint64_t addr, uint32_t size) {
    // Descriptor
    Elf64_Nhdr *nhdr = (Elf64_Nhdr *)addr;
    char *name = (char *)addr + sizeof(Elf64_Nhdr);
    char *desc = (char *)addr + sizeof(Elf64_Nhdr) + ALIGN_SIZE_4(nhdr->n_namesz);

    m_name = name;

    llvm::msgpack::Document docs;
    llvm::msgpack::DocNode root;

    docs.clear();
    docs.readFromBlob(desc, false);
    root = docs.getRoot();

    llvm::msgpack::DocNode node = lookup(root, "ss.kernels");
    if (node.isArray()) {
        for (auto klist : node.getArray()) {
            auto fname = lookup(klist, ".name");
            printf("%s", fname.toString().c_str());
        }
    }
}

llvm::msgpack::DocNode metadata::lookup(llvm::msgpack::DocNode &root, const char *key) {
    llvm::msgpack::DocNode ret;
    auto m = root.getMap();
    printf("size: %ld\n", m.size());

    for (auto iter : root.getMap()) {
        printf("%d\n", iter.first.isScalar());
        printf("%s, %s\n", key, iter.first.toString().c_str());
        if (!iter.first.isScalar() || std::string(key) != iter.first.toString()) {
            continue;
        }

        ret = iter.second;
    }

    return ret;
}


} // namespace cuda