#include "TransducerManager.hpp"
#include "DefaultTransducer.hpp"
#include "Transducer.hpp"

using namespace std;

void TransducerManager::registerTransducer(const string &extension,
                                           unique_ptr<Transducer> transducer) {
  transducers[extension] = std::move(transducer);
}

std::vector<Triple> TransducerManager::processFile(const File &file) const {
  string extension = file.path.substr(file.path.find_last_of('.') + 1);
  vector<Triple> result;

  DefaultTransducer defaultTransducer;
  auto defaultResult = defaultTransducer.process(file);
  result.insert(result.end(), defaultResult.begin(), defaultResult.end());

  auto it = transducers.find(extension);
  if (it != transducers.end()) {
    auto specificResult = it->second->process(file);
    result.insert(result.end(), specificResult.begin(), specificResult.end());
  }

  return result;
}
