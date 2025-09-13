#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <queue>
#include <functional>
#include <condition_variable>
#include <future>   // 必须加

class ThreadPool {
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;

    std::mutex mtx;
    std::condition_variable cv;
    bool _stop = false;

    ThreadPool(int numThreads) {
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([this]{
                while (true) {
                    std::unique_lock<std::mutex> lck(mtx);
                    cv.wait(lck, [this]{ return _stop || !tasks.empty(); });
                    if (_stop && tasks.empty()) return;
                    auto task = std::move(tasks.front());
                    tasks.pop();
                    lck.unlock();
                    task();
                }
            });
        }
    }

public:
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using ReturnType = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<ReturnType> res = task->get_future();
        {
            std::unique_lock<std::mutex> lck(mtx);
            tasks.emplace([task](){ (*task)(); });
        }
        cv.notify_one();
        return res;
    }

    static ThreadPool& getThreadPool(int numThreads = 4) {
        static ThreadPool instance(numThreads);  // 自动析构
        return instance;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lck(mtx);
            _stop = true;
        }
        cv.notify_all();
        for (auto& t : threads) {
            t.join();
        }
    }
};


int main() {
    ThreadPool &tp = ThreadPool::getThreadPool(3);
    int a = 1, b = 2;
    tp.enqueue([](){std::cout << "hello world!" << std::endl;});
    tp.enqueue([=](){std::cout << a + b << std::endl;}); //必须使用=传值，否则等主程序退出，a, b被释放会出现野指针
    auto f = tp.enqueue([=](){return a*2 + b*2;});
    std::cout << "res: " << f.get() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}