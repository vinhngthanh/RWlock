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
    writers = 0;
  }

  void readLock(){
    unique_lock<mutex> lock(*mtx);
    while (writers) {
      cv.wait(lock);
    }
    readers++;
  }

  void readUnlock(){
    readers--;
    cv.notify_all();
  }

  void writeLock(){
    unique_lock<mutex> lock(*mtx);
    while (readers > 0 || writers) {
      cv.wait(lock);
    }
    writers = true;
  }

  void writeUnlock(){
    writers = false;
    cv.notify_all();
  }

private:
  unique_ptr<mutex> mtx;
  condition_variable cv;
  atomic<int> readers;
  atomic<bool> writers;
};
