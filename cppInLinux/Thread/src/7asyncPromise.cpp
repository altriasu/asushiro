#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <functional>

int func(int pid) {
    int sum = 0;
    for (int i = 0; i < 20; ++ i){
        sum += i;
        printf("pid: %d, i: %d\n", pid, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return sum;
}

void function1(std::promise<int> &msg, int&& pid) {
    printf("pid: %d, set value\n", pid);
    msg.set_value(1000);
}

void function2(std::promise<int> &msg, int&& pid) {
    printf("pid: %d, wait for value\n", pid);
    int value = msg.get_future().get();
    printf("pid: %d, value: %d\n", pid, value);
}

int main() {
#if 0 //使用async
    //使用async就不需要手动创建多线程了，返回的是future对象，可以用get()获取结果
    std::future<int> f1 = std::async(std::launch::async, func, 1);
    std::future<int> f2 = std::async(std::launch::async, func, 2);

    printf("f1 result: %d\n", f1.get());
    printf("f2 result: %d\n", f2.get());
#elseif 0 //使用packaged_task
    std::packaged_task<int()> task1(std::bind(func, 1)); //可以手动控制任务的执行而不是由async直接执行
    std::packaged_task<int()> task2(std::bind(func, 2));
    auto future_res1 = task1.get_future();
    auto future_res2 = task2.get_future();

    std::thread t1(std::move(task1));
    std::thread t2(std::move(task2));
    
    t1.join();
    t2.join();
    printf("t1 result: %d\n", future_res1.get());
    printf("t2 result: %d\n", future_res2.get());
#else //async和promise
    std::promise<int> msg;
    std::thread t2(function2, std::ref(msg), 2);
    std::thread t1(function1, std::ref(msg), 1);
    t2.join();
    t1.join();
#endif
    return 0;
}