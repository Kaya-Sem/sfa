#ifndef TRANSDUCER_HPP
#define TRANSDUCER_HPP

#include <map>
#include <string>

using namespace std;

class File {
public:
  explicit File(string path) : path(std::move(path)) {}
  string path;
};

class Transducer {
public:
  virtual ~Transducer() = default;
  virtual map<string, string> process(const File &file) const = 0;
};

#endif
