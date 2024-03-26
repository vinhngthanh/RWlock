#include <atomic>

using namespace std;

class MyMutex {
public:
    MyMutex() {
        locked = false;
    }

    void lock() {
        while (locked.exchange(true, memory_order_acquire)) {
        }
    }

    void unlock() {
        locked.store(false, memory_order_release);
    }

private:
    atomic<bool> locked;
};