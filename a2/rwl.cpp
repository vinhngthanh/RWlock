#include <mutex>
#include <condition_variable>
#include <memory>

using namespace std;

class ReadWriteLock {
public:
  ReadWriteLock(){
    
  }

  void readLock() {
    unique_lock<mutex> lock(*mtx);
    while (writers > 0) {
      cv.wait(lock, [&] { return writers == 0; });
    }
    readers++;
  }

  void readUnlock() {
    lock_guard<mutex> lock(*mtx);
    readers--;
    cv.notify_all();
  }

  void writeLock() {
    unique_lock<mutex> lock(*mtx);
    while (readers > 0 || writers > 0) {
      cv.wait(lock, [&] { return writers == 0 && readers == 0; });
    }
    writers++;
  }

  void writeUnlock() {
    lock_guard<mutex> lock(*mtx);
    writers--;
    cv.notify_all();
  }

private:
  unique_ptr<mutex> mtx = make_unique<mutex>();
  condition_variable cv;
  int readers = 0;
  int writers = 0;
};
