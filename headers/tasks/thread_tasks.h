#include <mutex>

using namespace std;

class thread_tasks {

    /*mutex lock*/
    mutex mtx;
    /*the shared buffer*/
    char *buffer;
    /*extra condition for extra safety*/
    bool ready_to_read = false;

public:

    void thread1_task();
    void thread2_task();
};