#include <mutex>
#include <condition_variable>
#include <memory>

using namespace std;

class ReadPrioritizedWriteLock {
public:
  ReadPrioritizedWriteLock(){}

  void init(){
    mtx = make_unique<mutex>();
    readers = 0;
    writers = 0;
  }

  void readLock(){
    unique_lock<mutex> lock(*mtx);
    while (writers > 0) {
      cv.wait(lock);
    }
    readers++;
  }

  void readUnlock(){
    lock_guard<mutex> lock(*mtx);
    readers--;
    cv.notify_all();
  }

  void writeLock(){
    unique_lock<mutex> lock(*mtx);
    while (readers > 0 || writers > 0) {
      cv.wait(lock);
    }
    writers++;
  }

  void writeUnlock(){
    writers--;
    cv.notify_all();
  }

private:
  unique_ptr<mutex> mtx;
  condition_variable cv;
  int readers;
  int writers;
};
