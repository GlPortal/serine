#ifndef SERINE_MEMORY_ARCHIVER_HPP
#define SERINE_MEMORY_ARCHIVER_HPP

#include <serine/RawArchiver.hpp>
#include <serine/DynByteArray.hpp>

namespace serine {

/** \class MemoryArchiver
 * @brief Simple implementation of an Archiver reading/writing from/to memory.
 */
struct MemoryArchiver : public RawArchiver {
  DynByteArray data;
  enum Mode : bool {
    Saving = true,
    Reading = false
  } mode;

  MemoryArchiver(Mode m) : mode(m) {
  }

  void ar(size_t size, void *val) final override {
    if (size > 0) {
      if (mode == Saving) {
        data.put(size, val);
      } else {
        data.extract(size, val);
      }
    }
  }

  bool isSaving() const override {
    return mode == Saving;
  }
};

} /* namespace serine */

#endif /* SERINE_MEMORY_ARCHIVER_HPP */
