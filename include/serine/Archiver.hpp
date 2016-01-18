#ifndef SERINE_ARCHIVER_HPP
#define SERINE_ARCHIVER_HPP

#include <cstdint>
#include <string>

namespace serine {

class Serializable;

struct Archiver {
  using EntryName = const char*;

  virtual bool isSaving() const = 0;
  bool isLoading() const {
    return !isSaving();
  }

  virtual void operator()(EntryName, bool&) = 0;

  virtual void operator()(EntryName, uint8_t&) = 0;
  virtual void operator()(EntryName,  int8_t&) = 0;

  virtual void operator()(EntryName, uint16_t&) = 0;
  virtual void operator()(EntryName,  int16_t&) = 0;

  virtual void operator()(EntryName, uint32_t&) = 0;
  virtual void operator()(EntryName,  int32_t&) = 0;

  virtual void operator()(EntryName, uint64_t&) = 0;
  virtual void operator()(EntryName,  int64_t&) = 0;

  virtual void operator()(EntryName, float&) = 0;
  virtual void operator()(EntryName, double&) = 0;

  virtual void operator()(EntryName, char&) = 0;
  virtual void operator()(EntryName, char32_t&) = 0;

  virtual void operator()(EntryName, std::string&) = 0;
  virtual void operator()(EntryName, std::u32string&) = 0;

  virtual void operator()(EntryName, Serializable&) = 0;
};

} /* namespace serine */

#endif /* SERINE_SERIALIZABLE_HPP */
