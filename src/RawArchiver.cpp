#include <serine/RawArchiver.hpp>
#include <serine/Serializable.hpp>

namespace serine {

void RawArchiver::operator()(EntryName, Serializable &v) {
  v.serialize(*this);
}

} /* namespace serine */