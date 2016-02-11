#include <serine/RawArchiver.hpp>
#include <serine/Serializable.hpp>

namespace serine {

void RawArchiver::operator()(EntryName, Serializable &v) {
  v.serialize(*this);
}

void RawArchiver::operator()(EntryName, SerializableContainer &&c) {
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

} /* namespace serine */