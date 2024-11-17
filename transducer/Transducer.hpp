#ifndef TRANSDUCER_HPP
#define TRANSDUCER_HPP

#include <set>
#include <string>

using namespace std;

/* A transducer for a file gives back triples. These triples
 * are used for the Triplestore.
 * See https://en.wikipedia.org/wiki/Triplestore
 * A triple is a data entity composed of subject-predicate-object, like "Bob is
 * 35"
 */

class Object {
public:
  bool isLiteral;
  string value;
  Object(bool isLiteral, string value) : isLiteral(isLiteral), value(value) {}
};

//  TODO: make subject and object classes / enums of their own
class Triple {
public:
  string subject;
  string predicate;
  Object object;
  Triple(string subject, string predicate, Object object)
      : subject(subject), predicate(predicate), object(object) {}
};

class File {
public:
  explicit File(string path) : path(std::move(path)) {}
  string path;
};

/* A transducer takes in a file, and gives back a collection of Triple objects.
 * These are to be used in the semantic graph and triplestore
 */
class Transducer {
public:
  virtual ~Transducer() = default;
  virtual set<Triple> process(const File &file) const = 0;
};

#endif
