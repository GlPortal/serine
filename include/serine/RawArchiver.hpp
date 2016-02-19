#ifndef SERINE_RAW_ARCHIVER_HPP
#define SERINE_RAW_ARCHIVER_HPP

#include <vector>

#include <serine/Archiver.hpp>

namespace serine {

/** \class RawArchiver
 * @brief Base class for Archivers using raw I/O with unnamed entries.
 */
struct RawArchiver : public Archiver {
  /**
   * Method used to read or write @ref sz bytes from/to @ref data.
   */
  virtual void ar(size_t sz, void *data) = 0;
  /**
   * Method used to (un)serialize data in the given container @ref c.
   * Calls @ref ar() to load/store the container size and data.
   */
  template<typename T> void iter(Container<T> &c) {
    uint32_t len = c.size();
    ar(sizeof(len), &len);
    c.resize(len);
    if (len <= 0) {
      return;
    }
    do {
      ar(sizeof(T), &*c);
    } while(++c);
  }

  virtual void operator()(EntryName, bool &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, BoolContainer &&c) { iter(c); }

  virtual void operator()(EntryName, uint8_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, UInt8Container &&c) { iter(c); }
  virtual void operator()(EntryName,  int8_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName,  Int8Container &&c) { iter(c); }

  virtual void operator()(EntryName, uint16_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, UInt16Container &&c) { iter(c); }
  virtual void operator()(EntryName,  int16_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName,  Int16Container &&c) { iter(c); }

  virtual void operator()(EntryName, uint32_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, UInt32Container &&c) { iter(c); }
  virtual void operator()(EntryName,  int32_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName,  Int32Container &&c) { iter(c); }

  virtual void operator()(EntryName, uint64_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, UInt64Container &&c) { iter(c); }
  virtual void operator()(EntryName,  int64_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName,  Int64Container &&c) { iter(c); }

  virtual void operator()(EntryName, float &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, FloatContainer &&c) { iter(c); }
  virtual void operator()(EntryName, double &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, DoubleContainer &&c) { iter(c); }

  virtual void operator()(EntryName, char &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, CharContainer &&c) { iter(c); }
  virtual void operator()(EntryName, char32_t &v) { ar(sizeof(v), &v); }
  virtual void operator()(EntryName, Char32Container &&c) { iter(c); }

  virtual void operator()(EntryName, std::string &v) {
    size_t sz = v.size();
    ar(sizeof(sz), &sz);
    v.resize(sz);
    ar(sizeof(std::remove_reference<decltype(v)>::type::value_type)*sz, &v.front());
  }
  virtual void operator()(EntryName, StringContainer &&c) {
    uint32_t len = c.size();
    ar(sizeof(len), &len);
    c.resize(len);
    if (len <= 0) {
      return;
    }
    do {
      auto &v = *c;
      size_t sz = v.size();
      ar(sizeof(sz), &sz);
      v.resize(sz);
      ar(sizeof(std::remove_reference<decltype(v)>::type::value_type)*sz, &v.front());
    } while(++c);
  }

  virtual void operator()(EntryName, std::u32string &v) {
    size_t sz = v.size();
    ar(sizeof(sz), &sz);
    v.resize(sz);
    ar(sizeof(std::remove_reference<decltype(v)>::type::value_type)*sz, &v.front());
  }
  virtual void operator()(EntryName, String32Container &&c) {
    uint32_t len = c.size(); 
    ar(sizeof(len), &len);
    c.resize(len);
    if (len <= 0) {
      return;
    }
    do {
      auto &v = *c;
      size_t sz = v.size();
      ar(sizeof(sz), &sz);
      v.resize(sz);
      ar(sizeof(std::remove_reference<decltype(v)>::type::value_type)*sz, &v.front());
    } while(++c);
  }

  virtual void operator()(EntryName, Serializable &v) {
    v.serialize(*this);
  }
  virtual void operator()(EntryName, SerializableContainer &&c) {
    uint32_t len = c.size();
    ar(sizeof(len), &len);
    c.resize(len);
    if (len <= 0) {
      return;
    }
    do {
      (*c).serialize(*this);
    } while(++c);
  }
};

} /* namespace serine */

#endif /* SERINE_RAW_ARCHIVER_HPP */
