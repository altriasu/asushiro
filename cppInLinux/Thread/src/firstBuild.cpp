#include <thread>

void printHello(std::string name){
    printf("Hello, %s!\n", name.c_str());
    return;
}

int main(){
    std::thread t1(printHello, "World");
#if true
    bool isJoin = t1.joinable(); 
    if (isJoin){
        t1.join();//主线程等待子线程执行完，阻塞等待
    }
#else
    t1.detach(); //主线程不会等待子线程结束，主线程退出后子线程仍能够执行，且不报错
#endif
    return 0;
}