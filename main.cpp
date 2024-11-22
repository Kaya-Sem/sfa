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

void printTriple(const Triple &triple) {
  std::cout << triple.subject << ", " << triple.predicate << ", ";

  // Use std::visit to access the variant value in Object
  std::visit(
      [](const auto &v) {
        std::cout << v;
      }, // Lambda to handle all variant types
      triple.object.value);

  std::cout << std::endl;
}

void processQueue(const TransducerManager *manager) {
  while (running) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !eventQueue.empty() || !running; });

    while (!eventQueue.empty()) {
      event e = eventQueue.front();
      eventQueue.pop();

      if (e.effect_type == event::effect_type::destroy) {
        cout << "path " << e.path_name << " destroyed";
      } else {

        // Example: Process the event using the manager and transducer
        auto result = manager->processFile(File(e.path_name));

        for (const auto triple : result) {
          printTriple(triple);
        }

        cout << endl;
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

  //  TODO: created method to cleanly close the full service. Remove and clean
  //  up threads. Remove data structures. An interprocess signal should be able
  //  to cleanly shutdown the service.
  // Stop the watcher and processing thread
  running = false;
  cv.notify_one();         // Notify the processing thread to exit
  processingThread.join(); // TODO: maybe use .detach()?

  delete manager;

  // Close the watcher
  return watcher.close() ? 0 : 1;
}
