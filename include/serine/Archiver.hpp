#ifndef SERINE_ARCHIVER_HPP
#define SERINE_ARCHIVER_HPP

#include <cstdint>
#include <string>

#include <serine/Container.hpp>
#include <serine/Serializable.hpp>

namespace serine {

struct Serializable;

/** \class Archiver
 * @brief Base class of all archive reading and writing implementations.
 */
struct Archiver {
  using EntryName = const char*;

  /**
   * 
   */
  uint64_t version = 0;

  /**
   * Determines whether the Archiver loads or saves the data passed to it.
   * @returns `true` if saving, `false` otherwise;
   */
  virtual bool isSaving() const = 0;
  inline bool isLoading() const {
    return !isSaving();
  }

  virtual void operator()(EntryName, bool&) = 0;
  virtual void operator()(EntryName, BoolContainer&&) = 0;

  virtual void operator()(EntryName, uint8_t&) = 0;
  virtual void operator()(EntryName, UInt8Container&&) = 0;
  virtual void operator()(EntryName,  int8_t&) = 0;
  virtual void operator()(EntryName,  Int8Container&&) = 0;

  virtual void operator()(EntryName, uint16_t&) = 0;
  virtual void operator()(EntryName, UInt16Container&&) = 0;
  virtual void operator()(EntryName,  int16_t&) = 0;
  virtual void operator()(EntryName,  Int16Container&&) = 0;

  virtual void operator()(EntryName, uint32_t&) = 0;
  virtual void operator()(EntryName, UInt32Container&&) = 0;
  virtual void operator()(EntryName,  int32_t&) = 0;
  virtual void operator()(EntryName,  Int32Container&&) = 0;

  virtual void operator()(EntryName, uint64_t&) = 0;
  virtual void operator()(EntryName, UInt64Container&&) = 0;
  virtual void operator()(EntryName,  int64_t&) = 0;
  virtual void operator()(EntryName,  Int64Container&&) = 0;

  virtual void operator()(EntryName, float&) = 0;
  virtual void operator()(EntryName, FloatContainer&&) = 0;
  virtual void operator()(EntryName, double&) = 0;
  virtual void operator()(EntryName, DoubleContainer&&) = 0;

  virtual void operator()(EntryName, char&) = 0;
  virtual void operator()(EntryName, CharContainer&&) = 0;
  virtual void operator()(EntryName, char32_t&) = 0;
  virtual void operator()(EntryName, Char32Container&&) = 0;

  virtual void operator()(EntryName, std::string&) = 0;
  virtual void operator()(EntryName, StringContainer&&) = 0;
  virtual void operator()(EntryName, std::u32string&) = 0;
  virtual void operator()(EntryName, String32Container&&) = 0;

  virtual void operator()(EntryName, Serializable&) = 0;
  virtual void operator()(EntryName, SerializableContainer&&) = 0;
};

} /* namespace serine */

#endif /* SERINE_SERIALIZABLE_HPP */
