#include <chrono>
#include <iostream>
#include <thread>

void hello(std::string& name)
{
    std::cout << "thread id: " << std::this_thread::get_id() << '\n';
    name = "Saravanan";
}

int main()
{
    std::string name{"World"};

    std::thread t{hello, std::ref(name)};
    t.join();

    std::cout << "Hello " << name << "!\n";

    std::cout << "main thread id: " << std::this_thread::get_id() << '\n';

    std::thread t2;
    std::cout << "t2 thread id: " << t2.get_id() << '\n';

    return 0;
}
