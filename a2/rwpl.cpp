#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>

using namespace std;

class ReadWritePrioritizedLock {
public:
    ReadWritePrioritizedLock(){
        init();
    }

    void init(){
        mtx = make_unique<mutex>();
        readers.store(0);
        writers.store(false);
        writerRequests.store(0);
    }

    void readLock(){
        unique_lock<mutex> lock(*mtx);
        while (writerRequests.load() > 0 || writers.load()) {
            cv.wait(lock);
        }
        readers.fetch_add(1);
    }

    void readUnlock(){
        lock_guard<mutex> lock(*mtx);
        readers.fetch_sub(1);
        cv.notify_all();
    }

    void writeLock(){
        unique_lock<mutex> lock(*mtx);
        writerRequests.fetch_add(1);
        while (readers.load() > 0 || writers.load()) {
            cv.wait(lock);
        }
        writerRequests.fetch_sub(1);
        writers.store(true);
    }

    void writeUnlock(){
        lock_guard<mutex> lock(*mtx);
        writers.store(false);
        cv.notify_all();
    }

private:
    unique_ptr<mutex> mtx;
    condition_variable cv;
    atomic<int> readers;
    atomic<bool> writers;
    atomic<int> writerRequests;
};
