#include <assert.h>
#include <string>
#include <iostream>

#include <serine/MemoryArchiver.hpp>
#include <serine/Serializable.hpp>

#include <serine/StlContainer.hpp>

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

struct MyLittleStruct : public serine::Serializable {
  int a, b, c;
  MyLittleStruct() {}
  MyLittleStruct(int a, int b, int c) : a(a), b(b), c(c) {}
  void serialize(serine::Archiver &ar) {
    std::cout << '[' << this << "]: imma " << (ar.isSaving() ? "saving" : "loading") << '!' << std::endl;
    ar("a", a);
    ar("b", b);
    ar("c", c);
  }
};

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;

  serine::MemoryArchiver ar(serine::MemoryArchiver::Saving);
  {
    MyContainingObject co; MyObject &obj = co.obj;
    obj.errupt = -42;
    obj.papers = 1337;
    obj.text = "bla bla hello I'm error!";
    co.number = 164025573;
    co.serialize(ar);

    std::vector<int> numberwang { 1, 2, 3, 4 };
    ar("numberwang", serine::contain_stl(numberwang));

    std::vector<std::string> strings = {
      "HO-CH2-CH(NH2)-COOH",
      "HO-CH2-CH(NH3)-COO",
      "C3H7NO3"
    };
    ar("strings", serine::contain_stl(strings));

    std::vector<MyLittleStruct> strukts;
    strukts.emplace_back(100, 200, 300);
    strukts.emplace_back(400, 500, 600);
    ar("strukts", serine::contain_stl(strukts));
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

    std::vector<int> numberwang;
    ar("numberwang", serine::contain_stl(numberwang));
    for (int i = 0; i < 4; ++i) {
      assert(numberwang[i] == i + 1);
    }

    std::vector<std::string> strings;
    ar("strings", serine::contain_stl(strings));
    assert(strings[0] == "HO-CH2-CH(NH2)-COOH");
    assert(strings[1] == "HO-CH2-CH(NH3)-COO");
    assert(strings[2] == "C3H7NO3");

    std::vector<MyLittleStruct> strukts;
    ar("strukts", serine::contain_stl(strukts));
    assert(strukts[0].a == 100 && strukts[0].b == 200 && strukts[0].c == 300);
    assert(strukts[1].a == 400 && strukts[1].b == 500 && strukts[1].c == 600);
  }
  std::cout << "Aye cap'tain, 'tis all fine! We retrieved the same bottle we sent!" << std::endl;
  return 0;
}