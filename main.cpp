#include "transducer/TransducerManager.hpp"
#include "watcher/watcher.hpp"
#include <atomic>
#include <iostream>
#include <ostream>
#include <thread>

using namespace std;
using namespace wtr;

TransducerManager *initializeTransducerManager() {
  return new TransducerManager;
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

      for (const auto &[subject, predicate, object] : result) {
        cout << subject << ", " << predicate << ", " << object.value << endl;
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

  //  TODO: created method to cleanly close the full service. Remove and clean up threads. Remove data structures.
  //  An interprocess signal should be able to cleanly shutdown the service.
  // Stop the watcher and processing thread
  running = false;
  cv.notify_one(); // Notify the processing thread to exit
  processingThread.join();

  delete manager;

  // Close the watcher
  return watcher.close() ? 0 : 1;
}
