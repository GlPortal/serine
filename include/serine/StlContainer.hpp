#ifndef SERINE_STL_CONTAINER_HPP
#define SERINE_STL_CONTAINER_HPP

#include <type_traits>

#include <serine/Container.hpp>

namespace serine {

template<class C, typename T = typename C::value_type>
struct StlContainer : public Container<T> {
  C &container;
  typename C::iterator it;
  StlContainer(C &c) : container(c), it(c.begin()) {}
  size_t size() const {
    return container.size();
  }
  void resize(size_t s) {
    if (s > container.size()) {
      container.resize(s);
      it = container.begin();
    }
  }
  T& operator*() {
    return *it;
  }
  bool operator++() {
    return ++it != container.end();
  }
};

template<typename T, typename... U, template<class, typename...> class C>
typename std::enable_if< /* Use only if contained type inherits from Serializable */
  std::is_base_of<Serializable, typename C<T, U...>::value_type>::value,
  StlContainer<C<T, U...>, Serializable>
>::type contain_stl(C<T, U...> &c) {
  return StlContainer<C<T, U...>, Serializable>(c);
}

template<typename T, typename... U, template<typename, typename...> class C>
typename std::enable_if< /* Use only if contained is integral
  (i.e. non-object/struct/pointer/enum) OR is a string */
  std::is_integral<typename C<T, U...>::value_type>::value ||
    std::is_same<typename C<T, U...>::value_type, std::string>::value ||
    std::is_same<typename C<T, U...>::value_type, std::u32string>::value,
  StlContainer<C<T, U...>>
>::type contain_stl(C<T, U...> &c) {
  return StlContainer<C<T, U...>>(c);
}

} /* namespace serine */

#endif /* SERINE_STL_CONTAINER_HPP */
