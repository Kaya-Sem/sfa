
// watcher.hpp
#ifndef WATCHER_HPP
#define WATCHER_HPP

#include <iostream>
#include <string>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "wtr/watcher.hpp"

using namespace std;
using namespace wtr;

// Declare the event queue and related synchronization mechanisms
extern queue<event> eventQueue;
extern atomic<bool> running;
extern mutex mtx;
extern condition_variable cv;

// Blacklisted paths to be ignored
extern vector<string> blacklistedPaths;

// Function to check if the path is blacklisted
bool isBlacklisted(const string& path);

// Function to queue an event if it's not blacklisted
void queueEvent(event e);

// Function to process the event queue in a separate thread
//void processQueue();

// Function to get the event queue
queue<event>& getFileSystemEventQueue();

#endif // WATCHER_HPP
