#ifndef SERINE_STL_CONTAINER_HPP
#define SERINE_STL_CONTAINER_HPP

#include <serine/Container.hpp>

namespace serine {

template<class C, typename T = typename C::value_type> struct StlContainer : public Container<T> {
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

/*template<class C> StlContainer<C, Serializable> contain_stl(C &c) {
  return StlContainer<C, Serializable>(c);
}*/

template<class C> StlContainer<C> contain_stl(C &c) {
  return StlContainer<C>(c);
}

} /* namespace serine */

#endif /* SERINE_STL_CONTAINER_HPP */
