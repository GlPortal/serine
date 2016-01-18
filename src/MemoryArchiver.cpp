#include <serine/MemoryArchiver.hpp>

#include <cstring>

namespace serine {

void MemoryArchiver::ar(size_t size, void *val) {
  if (size > 0) {
    if (mode == Saving) {
      data.put(size, val);
    } else {
      data.extract(size, val);
    }
  }
}

} /* namespace serine */