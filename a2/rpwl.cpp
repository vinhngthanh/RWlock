#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>
#include "myMutex.cpp"

using namespace std;

class ReadPrioritizedWriteLock {
public:
  ReadPrioritizedWriteLock(){
    init();
  }

  void init(){
    mtx = make_unique<mutex>();
    myMtx.init();
    readers.store(0);
    readerRequests.store(0);
    writers.store(false);
  }

  void readLock(){
    unique_lock<mutex> lock(*mtx);
    readerRequests.fetch_add(1);
    while (writers.load()) {
      cv.wait(lock);
    }
    readerRequests.fetch_sub(1);
    readers.fetch_add(1);
  }

  void readUnlock(){
    readers.fetch_sub(1);
    cv.notify_all();
  }

  void writeLock(){
    unique_lock<mutex> lock(*mtx);
    while (readers.load() > 0 || writers.load() || readerRequests.load() > 0) {
      cv.wait(lock);
    }
    writers.store(true);
  }

  void writeUnlock(){
    // lock_guard<mutex> lock(*mtx);
    myMtx.lock();
    writers.store(false);
    cv.notify_all();
    myMtx.unlock();
  }

private:
  unique_ptr<mutex> mtx;
  condition_variable cv;
  MyMutex myMtx;
  atomic<int> readers;
  atomic<int> readerRequests;
  atomic<bool> writers;
};
