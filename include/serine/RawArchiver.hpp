#ifndef SERINE_RAW_ARCHIVER_HPP
#define SERINE_RAW_ARCHIVER_HPP

#include "Archiver.hpp"

#include <vector>

namespace serine {

struct RawArchiver : public Archiver {
  virtual void ar(size_t, void*) = 0;

  virtual void operator()(EntryName, bool &v) { ar(sizeof(v), &v); }

  virtual void operator()(EntryName, uint8_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName,  int8_t &v) { ar(sizeof(v), &v); }

  virtual void operator()(EntryName, uint16_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName,  int16_t &v) { ar(sizeof(v), &v); }

  virtual void operator()(EntryName, uint32_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName,  int32_t &v) { ar(sizeof(v), &v); }

  virtual void operator()(EntryName, uint64_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName,  int64_t &v) { ar(sizeof(v), &v); }

  virtual void operator()(EntryName, float &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, double &v) { ar(sizeof(v), &v); }

  virtual void operator()(EntryName, char &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, char32_t &v) { ar(sizeof(v), &v); }

  virtual void operator()(EntryName, std::string &v) {
    size_t sz = v.size();
    ar(sizeof(sz), &sz);
    v.resize(sz);
    ar(sizeof(std::string::value_type)*sz, &v[0]);
  }
  virtual void operator()(EntryName, std::u32string &v) {
    size_t sz = v.size();
    ar(sizeof(sz), &sz);
    v.resize(sz);
    ar(sizeof(std::u32string::value_type), &v[0]);
  }

  virtual void operator()(EntryName, Serializable&);
};

} /* namespace serine */

#endif /* SERINE_RAW_ARCHIVER_HPP */
