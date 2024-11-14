
// main.cpp
#include "watcher/watcher.hpp"
#include <atomic>
#include <iostream>
#include <ostream>
#include <thread>

using namespace std;
using namespace wtr;

/* 1) Event is processed from the queue. This is passed to the relevant
 *    transducer. Transducers are (usually) based on file extension.
 * 2) the transducer gives back a key-value map, that indicate labels and
 * relations.
 * 3) These values are passed to the appropriate file, it's metadata
 * being updated.
 * 4) The node in the graph/database gets updated
 */

void processQueue() {
  while (running) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !eventQueue.empty() || !running; });

    while (!eventQueue.empty()) {
      event e = eventQueue.front();
      eventQueue.pop();
      cout << to<string>(e.effect_type) + ' ' + to<string>(e.path_type) + ' ' +
                  to<string>(e.path_name) +
                  (e.associated ? " -> " + to<string>(e.associated->path_name)
                                : "")
           << endl;
    }
  }
}

int main() {

  const char *homeDir = std::getenv("HOME");
  if (!homeDir) {
    cerr << "Failed to get home directory" << endl;
    return 1;
  }

  // Start the event processing thread
  thread processingThread(processQueue);

  // Watch the user's home directory asynchronously
  auto watcher = watch(homeDir, queueEvent);

  // Main thread can continue doing other work here
  getchar();

  // Stop the watcher and processing thread
  running = false;
  cv.notify_one(); // Notify the processing thread to exit
  processingThread.join();

  // Close the watcher
  return watcher.close() ? 0 : 1;
}