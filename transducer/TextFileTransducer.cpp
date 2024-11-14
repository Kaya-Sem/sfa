#include "TextFileTransducer.hpp"

using namespace std;

// TODO: actually implement
map<string, string> TextFileTransducer::process(const File &file) const {
  return {{"type", "text"}, {"path", file.path}};
}
