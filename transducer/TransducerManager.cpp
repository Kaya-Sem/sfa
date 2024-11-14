#include "TransducerManager.hpp"

using namespace std;

void TransducerManager::registerTransducer(const std::string& extension, std::unique_ptr<Transducer> transducer) {
    transducers[extension] = std::move(transducer);
}

std::map<std::string, std::string> TransducerManager::processFile(const File& file) const {
    std::string extension = file.path.substr(file.path.find_last_of('.') + 1);

    auto it = transducers.find(extension);
    if (it != transducers.end()) {
        return it->second->process(file);
    } else {
        return {{"type", "unknown"}, {"path", file.path}};
    }
}
