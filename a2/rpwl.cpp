#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>

using namespace std;

class ReadPrioritizedWriteLock {
public:
  ReadPrioritizedWriteLock(){
    init();
  }

  void init(){
    mtx = make_unique<mutex>();
    readers = 0;
    readerRequests = 0;
    writers = false;
  }

  void readLock(){
    unique_lock<mutex> lock(*mtx);
    readerRequests++;
    while (writers) {
      cv.wait(lock);
    }
    readerRequests--;
    readers++;
  }

  void readUnlock(){
    readers--;
    cv.notify_all();
  }

  void writeLock(){
    unique_lock<mutex> lock(*mtx);
    while (readers > 0 || writers || readerRequests > 0) {
      cv.wait(lock);
    }
    writers = true;
  }

  void writeUnlock(){
    lock_guard<mutex> lock(*mtx);
    writers = false;
    cv.notify_all();
  }

private:
  unique_ptr<mutex> mtx;
  condition_variable cv;
  atomic<int> readers;
  atomic<int> readerRequests;
  atomic<bool> writers;
};
