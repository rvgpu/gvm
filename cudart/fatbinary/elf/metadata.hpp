#include <map>
#include <string>
#include <cstdint>
#include <elf.h>

namespace cuda {

class metadata {
public:
    metadata(uint64_t addr, uint32_t size);
    
private:
};

} // namespace cuda