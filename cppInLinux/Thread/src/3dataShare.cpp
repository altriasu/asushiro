#include <thread>
#include <mutex>
#include <iostream>

int shared_data = 0;
std::mutex mtx;

void func() {
    for (int i = 0; i < 10000; i ++){
        std::unique_lock<std::mutex> lg(mtx); //通过互斥锁实现数据安全
        shared_data++;
    }
}

std::timed_mutex mtx2;
void deferFunc() {
    for (int i = 0; i < 2; i ++){
        std::unique_lock<std::timed_mutex> lg(mtx2, std::defer_lock);
        if (lg.try_lock_for(std::chrono::seconds(2))){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            shared_data++;
        }
    }
}

int main() {
#if 0
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
#else
    std::thread t3(deferFunc);
    std::thread t4(deferFunc);
    t3.join();
    t4.join();
    std::cout << shared_data << std::endl;
#endif

    return 0;
}
