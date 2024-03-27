#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>
#include "myMutex.cpp"

using namespace std;

class ReadWritePrioritizedLock {
public:
  ReadWritePrioritizedLock(){
    init();
  }

  void init(){
    mtx.init();
    rmtx.init();
    readers.store(0);
    writerRequest.store(0);
  }

  void readLock(){
    while(writerRequest.load() > 0){}
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
    writerRequest.fetch_add(1);
    mtx.lock();
    writerRequest.fetch_sub(1);
  }

  void writeUnlock(){
    mtx.unlock();
  }

private:
    MyMutex mtx;
    MyMutex rmtx;
    atomic<int> readers;
    atomic<int> writerRequest;
};
