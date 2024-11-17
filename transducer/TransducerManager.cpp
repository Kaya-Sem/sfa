#include "TransducerManager.hpp"
#include "Transducer.hpp"

using namespace std;

void TransducerManager::registerTransducer(const string &extension,
                                           unique_ptr<Transducer> transducer) {
  transducers[extension] = std::move(transducer);
}

std::vector<Triple> TransducerManager::processFile(const File &file) const {
  string extension = file.path.substr(file.path.find_last_of('.') + 1);
  vector<Triple> result;

  auto it = transducers.find(extension);
  if (it != transducers.end()) {
    return it->second->process(file); // transducer found
  } else {
    // default transducer  TODO: create good default transducer
    result.push_back(
        *new Triple(file.path, "hasExtension", *new Object(true, extension)));
    return result;
  }
}
