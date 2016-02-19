#ifndef SERINE_DYN_BYTE_ARRAY_HPP
#define SERINE_DYN_BYTE_ARRAY_HPP

#include <cstdlib>
#include <cstring>
#include <new>
#include <stdexcept>

namespace serine {

/** \class DynByteArray
 * @brief Quick implementation of a flexible byte array, because `std::vector<uint8_t>` wasn't enough.
 */
struct DynByteArray {
  /**
   * Actual byte array pointer.
   */
  uint8_t *data;

  /**
   * Size of the currently allocated @ref data memory block.
   */
  size_t size;

  /**
   * Position of the data @ref put / @ref extract cursor. (offset)
   */
  size_t cursor;

  /**
   * Initializes the byte array with an initial size of @p size.
   */
  DynByteArray(size_t size = 8) :
    data(nullptr),
    size(0),
    cursor(0) {
    fit(size);
  }

  ~DynByteArray() {
    std::free(data);
  }

  /**
   * Resizes the buffer if necessary, making sure at least @p size bytes fit in it.
   */
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

  /**
   * Appends @p sz bytes from @p data into the buffer, starting at cursor position.
   */
  void put(size_t sz, void *data) {
    fit(cursor + sz);
    std::memcpy(this->data + cursor, data, sz);
    cursor += sz;
  }

  /**
   * Reads @p sz bytes from the buffer to @p data, starting at cursor position.
   */
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
