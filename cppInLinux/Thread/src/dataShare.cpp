#include <thread>
#include <mutex>
#include <iostream>

int shared_data = 0;
std::mutex mtx;

void func() {
    for (int i = 0; i < 10000; i ++){
        std::unique_lock<std::mutex> lg(mtx);
        shared_data++;
    }
}

void deferFunc() {
    for (int i = 0; i < 10000; i ++){
        std::unique_lock<std::mutex> lg(mtx, std::defer_lock);
        
    }
}

int main() {
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
    std::cout << shared_data << std::endl;

    return 0;
}
