
#ifndef TEXTFILETRANSDUCER_HPP
#define TEXTFILETRANSDUCER_HPP

#include "Transducer.hpp"

class TextFileTransducer : public Transducer {
public:
    std::map<std::string, std::string> process(const File& file) const override;
};

#endif
