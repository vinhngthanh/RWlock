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
        readers = 0;
        writers = false;
        writerRequests = 0;
    }

    void readLock(){
        unique_lock<mutex> lock(*mtx);
        while (writerRequests > 0 || writers) {
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
        writerRequests++;
        while (readers > 0 || writers) {
            cv.wait(lock);
        }
        writerRequests--;
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
    atomic<bool> writers;
    atomic<int> writerRequests;
};
