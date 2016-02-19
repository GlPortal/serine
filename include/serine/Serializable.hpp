#ifndef SERINE_SERIALIZABLE_HPP
#define SERINE_SERIALIZABLE_HPP

#include <serine/Archiver.hpp>

namespace serine {

struct Archiver;

/** \class Serializable
 * @brief Base class for structs/classes that can be directly passed to Archivers.
 */
struct Serializable {
  virtual void serialize(Archiver&) = 0;
};

} /* namespace serine */

#endif /* SERINE_SERIALIZABLE_HPP */
