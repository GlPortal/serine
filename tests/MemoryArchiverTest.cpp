#include <assert.h>
#include <string>

#include <serine/MemoryArchiver.hpp>
#include <serine/Serializable.hpp>

class MyObject : public serine::Serializable {
public:
  int errupt;
  unsigned papers;
  std::string text;

  void serialize(serine::Archiver &ar) {
    ar("errupt", errupt);
    ar("papers", papers);
    ar("text", text);
  }
};

class MyContainingObject : public serine::Serializable {
public:
  int number;
  MyObject obj;

  void serialize(serine::Archiver &ar) {
    ar("number", number);
    ar("obj", obj);
  }
};

int main(int argc, char **argv) {
  serine::MemoryArchiver ar(serine::MemoryArchiver::Saving);
  {
    MyContainingObject co; MyObject &obj = co.obj;
    obj.errupt = -42;
    obj.papers = 1337;
    obj.text = "bla bla hello I'm error!";
    co.number = 164025573;
    co.serialize(ar);
  }
  // Scroll the archiver back
  ar.data.cursor = 0;
  ar.mode = serine::MemoryArchiver::Reading;
  {
    MyContainingObject co; MyObject &obj = co.obj;
    co.serialize(ar);
    assert(obj.errupt == -42);
    assert(obj.papers == 1337);
    assert(obj.text == "bla bla hello I'm error!");
    assert(co.number == 164025573);
  }
  return 0;
}