#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>
#include "myMutex.cpp"

using namespace std;

class ReadWriteLock {
public:
  ReadWriteLock(){
    init();
  }

  void init(){
    mtx.init();
    rmtx.init();
    readers.store(0);
  }

  void readLock(){
    rmtx.lock();
    if(readers.load() == 0){
        mtx.lock();
    }
    readers.fetch_add(1);
    rmtx.unlock();
  }

  void readUnlock(){
    rmtx.lock();
    readers.fetch_sub(1);
    if(readers.load() == 0){
        mtx.unlock();
    }
    rmtx.unlock();
  }

  void writeLock(){
    mtx.lock();
  }

  void writeUnlock(){
    mtx.unlock();
  }

private:
    MyMutex mtx;
    MyMutex rmtx;
    atomic<int> readers;
};
