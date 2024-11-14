#include "transducer/TextFileTransducer.hpp"
#include "transducer/TransducerManager.hpp"
#include "watcher/watcher.hpp"
#include <atomic>
#include <iostream>
#include <memory>
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
 * 4) The node in the triplestore gets updated
 */

TransducerManager *initializeTransducerManager() {

  TransducerManager *m = new TransducerManager;
  m->registerTransducer("txt", make_unique<TextFileTransducer>());

  return m;
}

void processQueue(TransducerManager *manager) {
  while (running) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !eventQueue.empty() || !running; });

    while (!eventQueue.empty()) {
      event e = eventQueue.front();
      eventQueue.pop();

      // Example: Process the event using the manager and transducer
      cout << "trying to process " << e.path_name << endl;
      auto result = manager->processFile(File(e.path_name));

      for (const auto &[key, value] : result) {
        cout << key << ": " << value << endl;
      }
    }
  }
}

int main() {

  const char *homeDir = std::getenv("HOME");
  if (!homeDir) {
    cerr << "Failed to get home directory" << endl;
    return 1;
  }

  TransducerManager *manager = initializeTransducerManager();

  // Start the event processing thread with the manager
  thread processingThread([manager]() { processQueue(manager); });

  // Watch the user's home directory asynchronously
  auto watcher = watch(homeDir, queueEvent);

  // Main thread can continue doing other work here
  getchar();

  // Stop the watcher and processing thread
  running = false;
  cv.notify_one(); // Notify the processing thread to exit
  processingThread.join();

  delete manager;

  // Close the watcher
  return watcher.close() ? 0 : 1;
}
