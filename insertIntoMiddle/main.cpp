#include <iostream>
#include <thread>
#include <future>  
#include "FineGrainedQueue.h"

int main() {
    FineGrainedQueue FGQ;

    // однопоточный запуск
    std::cout << "----Single-threaded startup----\n\n";
    FGQ.pushback(1);
    FGQ.pushback(2);
    FGQ.pushback(3);
    FGQ.pushback(4);
    std::cout << "FULL DATA: ";
    FGQ.print();
    FGQ.insertIntoMiddle(444, 2);
    FGQ.insertIntoMiddle(555, 30);

    std::cout << "FULL DATA 2: ";
    FGQ.print();
    std::cout << "\n\n";

    // многопоточный запуск
    std::cout << "----Multithreaded startup----\n\n";
    std::future<void> f1 = std::async(std::launch::async, [&FGQ]() { FGQ.pushback(5); });
    std::future<void> f3 = std::async(std::launch::async, [&FGQ]() { FGQ.print(); });
    std::future<void> f2 = std::async(std::launch::async, [&FGQ]() { FGQ.pushback(6); });
    std::future<void> f4 = std::async(std::launch::async, [&FGQ]() { FGQ.print(); });

    f1.wait();
    f2.wait(); 
    f3.wait();   
    f4.wait();

    std::cout << "FULL DATA: ";
    FGQ.print();
    std::cout << std::endl;

    std::future<void> f5 = std::async(std::launch::async, [&FGQ]() { FGQ.insertIntoMiddle(10, 1); });
    std::future<void> f6 = std::async(std::launch::async, [&FGQ]() { FGQ.insertIntoMiddle(11, 1); });
    std::future<void> f7 = std::async(std::launch::async, [&FGQ]() { FGQ.insertIntoMiddle(12, 1); });
    std::future<void> f10 = std::async(std::launch::async, [&FGQ]() { FGQ.print(); });
    std::future<void> f8 = std::async(std::launch::async, [&FGQ]() { FGQ.insertIntoMiddle(13, 1); });
    std::future<void> f9 = std::async(std::launch::async, [&FGQ]() { FGQ.insertIntoMiddle(14, 50); });

    f5.wait();
    f6.wait();
    f7.wait();
    f8.wait();
    f9.wait();
    f10.wait();

    std::cout << "FULL DATA 2: ";
    FGQ.print();
    return 0;
}
