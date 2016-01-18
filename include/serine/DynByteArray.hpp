#ifndef SERINE_DYN_BYTE_ARRAY_HPP
#define SERINE_DYN_BYTE_ARRAY_HPP

#include <cstdlib>
#include <cstring>
#include <new>
#include <stdexcept>

namespace serine {

struct DynByteArray {
  uint8_t *data;
  size_t size, cursor;

  DynByteArray(size_t size = 8) :
    data(nullptr),
    size(0),
    cursor(0) {
    fit(size);
  }

  ~DynByteArray() {
    std::free(data);
  }

  void fit(size_t size) {
    if (size > this->size) {
      this->size = size;
      uint8_t *newdata = (uint8_t*)std::realloc(data, size);
      if (newdata == nullptr) {
        throw std::bad_alloc();
      }
      data = newdata;
    }
  }

  void put(size_t sz, void *data) {
    fit(cursor + sz);
    std::memcpy(this->data + cursor, data, sz);
    cursor += sz;
  }

  void extract(size_t sz, void *data) {
    if (cursor + sz > size) {
      throw std::out_of_range("No more data");
    }
    std::memcpy(data, this->data + cursor, sz);
    cursor += sz;
  }

  inline uint8_t operator[](size_t idx) { return data[idx]; }
  inline uint8_t operator[](size_t idx) const { return data[idx]; }
};

} /* namespace serine */

#endif /* SERINE_DYN_BYTE_ARRAY_HPP */
