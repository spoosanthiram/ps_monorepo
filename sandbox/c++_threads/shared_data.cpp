#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

std::shared_ptr<int> shared_int;
std::once_flag int_flag;

void init_int()
{
    shared_int = std::make_shared<int>(10);
    std::cout << "Initialized!\n";
}

void use_int()
{
    std::call_once(int_flag, init_int);
    std::cout << "*shared_int: " << *shared_int << '\n';
}

int main()
{
    std::jthread t0{use_int};
    std::jthread t1{use_int};

    return 0;
}
