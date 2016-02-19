#ifndef SERINE_CONTAINER_HPP
#define SERINE_CONTAINER_HPP

#include <cstdint>
#include <string>

#include <serine/Serializable.hpp>

namespace serine {

/** \class Container
 * @brief Wrapper for data containers.
 * 
 * Generic, implementation-hiding wrapper for containers (arrays, vectors, linked lists, ...).
 * Acts both as a container size modifier and forward iterator.
 */
template<typename T> struct Container {
  virtual ~Container() = default;

  /**
   * Gets the element count of the container.
   */
  virtual size_t size() const = 0;

  /**
   * Resizes the container so it holds the specified amount of *valid* (i.e. readable and writable
   * to) elements.
   * Expected to be a no-op if the desired number of elements == @ref size().
   */
  virtual void resize(size_t) = 0;

  /**
   * Returns a reference to the currently pointed object in the container.
   */
  virtual T& operator*() = 0;

  /**
   * Advances the iterator by one. In other words, seek to the next element.
   */
  virtual bool operator++() = 0;
};

using BoolContainer = Container<bool>;
using UInt8Container = Container<uint8_t>;
using Int8Container = Container<int8_t>;
using UInt16Container = Container<uint16_t>;
using Int16Container = Container<int16_t>;
using UInt32Container = Container<uint32_t>;
using Int32Container = Container<int32_t>;
using UInt64Container = Container<uint64_t>;
using Int64Container = Container<int64_t>;
using FloatContainer = Container<float>;
using DoubleContainer = Container<double>;
using CharContainer = Container<char>;
using Char32Container = Container<char32_t>;
using StringContainer = Container<std::string>;
using String32Container = Container<std::u32string>;
using SerializableContainer = Container<Serializable>;

} /* namespace serine */

#endif /* SERINE_CONTAINER_HPP */
