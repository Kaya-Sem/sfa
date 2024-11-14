#ifndef TRANSDUCER_HPP
#define TRANSDUCER_HPP

#include <string>
#include <map>

class File {
public:
    std::string path;
};

class Transducer {
public:
    virtual ~Transducer() = default;
    virtual std::map<std::string, std::string> process(const File& file) const = 0;
};

#endif
