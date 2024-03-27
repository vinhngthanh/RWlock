#include <atomic>

using namespace std;

class MyMutex {
public:
    MyMutex() {
        init();
    }

    void init(){
        locked.store(false);
    }

    void lock() {
        while (locked.exchange(true)) {
        }
    }

    void unlock() {
        locked.store(false);
    }

private:
    atomic<bool> locked;
};