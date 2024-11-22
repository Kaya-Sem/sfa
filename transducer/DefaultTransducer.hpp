#ifndef DEFAULTTRANSDUCER_HPP
#define DEFAULTTRANSDUCER_HPP

#include "Transducer.hpp"

class DefaultTransducer : public Transducer {
public:
  std::vector<Triple> process(const File &file) const override;
};

#endif
