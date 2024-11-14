#ifndef TRANSDUCERMANAGER_HPP
#define TRANSDUCERMANAGER_HPP

#include "Transducer.hpp"
#include <memory>
#include <unordered_map>

using namespace std;

class TransducerManager {
private:
  unordered_map<string, unique_ptr<Transducer>> transducers;

public:
  void registerTransducer(const string &extension,
                          unique_ptr<Transducer> transducer);
  map<string, string> processFile(const File &file) const;
};

#endif
