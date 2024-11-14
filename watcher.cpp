
// watcher.cpp
#include "watcher.hpp"

using namespace std;
using namespace wtr;

// Initialize global variables
queue<event> eventQueue;
atomic<bool> running(true);
mutex mtx;
condition_variable cv;

vector<string> blacklistedPaths = {"/home/kayasem/.cache"};

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

void processQueue() {
  while (running) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []{ return !eventQueue.empty() || !running; });

    while (!eventQueue.empty()) {
      event e = eventQueue.front();
      eventQueue.pop();
      cout << to<string>(e.effect_type) + ' '
           + to<string>(e.path_type)   + ' '
           + to<string>(e.path_name)
           + (e.associated ? " -> " + to<string>(e.associated->path_name) : "")
           << endl;
    }
  }
}

queue<event>& getFileSystemEventQueue() {
  return eventQueue;
}
