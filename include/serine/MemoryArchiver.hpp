#ifndef SERINE_MEMORY_ARCHIVER_HPP
#define SERINE_MEMORY_ARCHIVER_HPP

#include "RawArchiver.hpp"
#include "DynByteArray.hpp"

namespace serine {

struct MemoryArchiver : public RawArchiver {
  DynByteArray data;
  enum Mode : bool {
    Saving = true,
    Reading = false
  } mode;

  MemoryArchiver(Mode m) : mode(m) {
  }

  void ar(size_t, void*) final override;
  bool isSaving() const override {
    return mode == Saving;
  }
};

} /* namespace serine */

#endif /* SERINE_MEMORY_ARCHIVER_HPP */
