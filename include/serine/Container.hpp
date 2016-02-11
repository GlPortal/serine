#ifndef SERINE_CONTAINER_HPP
#define SERINE_CONTAINER_HPP

#include <cstdint>
#include <string>

#include <serine/Serializable.hpp>

namespace serine {

template<typename T> struct Container {
  virtual ~Container() = default;
  virtual size_t size() const = 0;
  virtual void resize(size_t) = 0;
  virtual T& operator*() = 0;
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
