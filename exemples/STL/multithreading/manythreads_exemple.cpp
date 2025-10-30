#include <thread>
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::thread> threads; threads.reserve(10);
    for (int i=0; i<10; ++i) {
        threads.emplace_back([&](int i) { std::cout << "Hello from " << i
                                                    << "th thread" << std::endl; }, i+1);
    }

    for (int i=0; i<10; ++i)
        threads[i].join();

    return EXIT_SUCCESS;
}
