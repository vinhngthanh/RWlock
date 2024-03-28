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
    mtx.init();
    rmtx.init();
    readers.store(0);
    readerRequest.store(0);
  }

  void readLock(){
    rmtx.lock();
    readerRequest.fetch_add(1);
    if(readers.load() == 0){
        mtx.lock();
    }
    readerRequest.fetch_sub(1);
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
    while(readerRequest.load() > 0){}
    mtx.lock();
  }

  void writeUnlock(){
    mtx.unlock();
  }

private:
    MyMutex mtx;
    MyMutex rmtx;
    atomic<int> readers;
    atomic<int> readerRequest;
};
