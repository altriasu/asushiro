#include <iostream>
#include <thread>
#include <memory>

std::thread t2;
void foo(int& x){
    for (int i = 1; i <= 100; i ++){
        if (i % 2 == 0){
            x ++;
        }
    }
}

void error2(){
    int a2 = 0;
    t2 = std::thread(foo, std::ref(a2)); //不能将局部变量添加到线程中，否则当同步函数执行完释放掉内存后，异步函数仍在访问这个内存
}

class A{
public:
    void foo(){
        std::cout<< "A::foo()" << std::endl;
    }
private:
    friend void thread_bar();
    void bar(){
        std::cout<< "A::bar()" << std::endl;
    }
};

void thread_bar(){
    std::shared_ptr<A> a = std::make_shared<A>();
    std::thread t4(&A::bar, a);
    t4.join();
}

int main(){
#if 0 //error1 and error2 局部变量提前销毁，访问错误的内存地址
    int a1 = 0;//将变量复制到一个持久对象中
    std::thread t1(foo, std::ref(a1));//将变量的引用传递给线程
    t1.join();
    error2();
    t2.join();
#elseif 0 //访问类中的函数，使用智能指针，防止类的示例提前释放
    std::shared_ptr<A> a = std::make_shared<A>();
    std::thread t3(&A::foo, a);
    t3.join();
#else //访问类中的私有函数
    thread_bar();
#endif
    return 0;
}