
// main.cpp
#include "watcher.hpp"
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;
using namespace wtr;

int main() {
  // Start the event processing thread
  thread processingThread(processQueue);

  // Watch the current directory asynchronously, calling the provided function on each event
  auto watcher = watch("/home/kayasem", queueEvent);

  // Main thread can continue doing other work here
  // (We will just wait for a newline to terminate the program)
  getchar();

  // Stop the watcher and processing thread
  running = false;
  cv.notify_one(); // Notify the processing thread to exit
  processingThread.join();

  // Close the watcher
  return watcher.close() ? 0 : 1;
}
