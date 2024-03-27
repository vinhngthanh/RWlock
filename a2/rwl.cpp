#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>

using namespace std;

class ReadWriteLock {
public:
  ReadWriteLock(){
    init();
  }

  void init(){
    mtx = make_unique<mutex>();
    readers.store(0);
    writers.store(false);
  }

  void readLock(){
    unique_lock<mutex> lock(*mtx);
    while (writers.load()) {
      cv.wait(lock);
    }
    readers.fetch_add(1);
  }

  void readUnlock(){
    readers.fetch_sub(1);
    cv.notify_all();
  }

  void writeLock(){
    unique_lock<mutex> lock(*mtx);
    while (readers.load() > 0 || writers.load()) {
      cv.wait(lock);
    }
    writers.store(true);
  }

  void writeUnlock(){
    writers.store(false);
    cv.notify_all();
  }

private:
  unique_ptr<mutex> mtx;
  condition_variable cv;
  atomic<int> readers;
  atomic<bool> writers;
};
