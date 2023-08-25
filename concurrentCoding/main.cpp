#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

void test()
{
    std::cout << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread t(test);
    t.join();
    std::chrono::milliseconds(1);
    return EXIT_SUCCESS;
}