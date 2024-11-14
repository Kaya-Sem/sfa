
// watcher.cpp
#include "watcher.hpp"

using namespace std;
using namespace wtr;

// Initialize global variables
queue<event> eventQueue;
atomic<bool> running(true);
mutex mtx;
condition_variable cv;

vector<string> blacklistedPaths = {};

bool isBlacklisted(const string& path) {
  for (const auto& blacklistedPath : blacklistedPaths) {
    if (path.find(blacklistedPath) != string::npos) {
      return true;
    }
  }
  return false;
}

void queueEvent(event e) {
  if (isBlacklisted(e.path_name)) {
    return;
  }

  lock_guard<mutex> lock(mtx);
  eventQueue.push(e);
  cv.notify_one();
}



queue<event>& getFileSystemEventQueue() {
  return eventQueue;
}
