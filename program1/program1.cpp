

#include <thread>

/*custom headers*/

#include "../headers/tasks/thread_tasks.h"


using namespace std;


int main() {
    
    thread_tasks main_tasks_ob;


    thread th1(&thread_tasks::thread1_task, ref(main_tasks_ob));
    this_thread::sleep_for(chrono::milliseconds(10));
    thread th2(&thread_tasks::thread2_task, ref(main_tasks_ob));


    th1.join();
    th2.join();


    return 0;
}
