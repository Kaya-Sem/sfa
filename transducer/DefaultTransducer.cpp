#include "DefaultTransducer.hpp"
#include "Transducer.hpp"
#include <ctime>
#include <sys/stat.h>
#include <vector>

using namespace std;

/* DefaultTransducer is called upon every event, before any other transducer. It
 * gives back the default metadata for files.
 *
 * https://linux.die.net/man/2/stat
 *
 * If the processed "file" is a directory, the size it gives back is the entry
 * itself, not the total size of files within the directory.
 */
vector<Triple> DefaultTransducer::process(const File &file) const {
  vector<Triple> result;

  struct stat fileStat;

  if (stat(file.path.c_str(), &fileStat) == -1) {
    perror("stat");
    return result;
  }

  result.emplace_back(file.path, "st-uid", /* user ID of owner */
                      Object(true, (unsigned long int)fileStat.st_uid));
  result.emplace_back(file.path, "st-atime", /* time of last acces */
                      Object(true, (unsigned long int)fileStat.st_atim.tv_sec));

  result.emplace_back(file.path, "st_mtime", /* time of last modification */
                      Object(true, (unsigned long int)fileStat.st_mtim.tv_sec));

  result.emplace_back(file.path, "st_ctime", /* time of last status change */
                      Object(true, (unsigned long int)fileStat.st_ctim.tv_sec));

  result.emplace_back(
      file.path, "st_size", /* total size, in bytes */
      Object(true,
             (unsigned long int)fileStat.st_size)); // may not need to be long

  return result;
}
