#include <iostream>
#include <thread>
#include <mutex>

static std::once_flag once;

class Log {
private:
    Log() {};
public:
    Log(const Log& log) = delete;
    Log& operator=(const Log& log) = delete;

    static void Init(Log* log) {
        if (!log) log = new Log();
    }

    static Log& GetInstance() {
#if 0
        static Log instance;
        return instance;
#else
        static Log *log = nullptr;
        std::call_once(once, Log::Init, log); //初始化函数只会被执行一次
        return *log;
#endif
    }

    void PrintLog(std::string msg){
        std::cout << __TIME__ << " INFO: " << msg << std::endl;
    }
};

void printLog(std::string msg) {
    Log::GetInstance().PrintLog(msg);
}

int main() {
    std::thread t1(printLog, "Thread 1 call!");
    std::thread t2(printLog, "Thread 2 call!");
    t1.join();
    t2.join();
    return 0;
}

