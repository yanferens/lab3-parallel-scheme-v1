
#include <chrono>
#include <iostream>
#include <latch>
#include <syncstream>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif

void f(char x, int i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::osyncstream(std::cout) << "З набору " << x << " виконано дію " << i << ".\n";
}


void run(char x, int first, int last, std::latch& done) {
    for (int i = first; i <= last; ++i) {
        f(x, i);
        done.count_down();
    }
}


void run(char x, int first, int last) {
    for (int i = first; i <= last; ++i)
        f(x, i);
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::osyncstream(std::cout) << "Обчислення розпочато.\n";
    auto start = std::chrono::steady_clock::now();

    std::latch before_eg(6);
    std::latch before_hi(5);
    std::latch before_c(4 + 5);
    std::latch before_k(8);
    std::latch before_d(6);
    std::latch before_f(4 + 8 + 5);

    std::thread t1([&] {
        run('a', 1, 2, before_eg);
        run('b', 5, 5, before_hi);
        before_hi.wait();
        run('h', 1, 1, before_c);
        before_eg.wait();
        run('e', 1, 2, before_k);
        run('i', 1, 1, before_d);
        before_c.wait();
        run('c', 1, 2, before_f);
        before_k.wait();
        run('k', 1, 1, before_f);
        before_d.wait();
        run('d', 1, 1, before_f);
        before_f.wait();
        run('f', 1, 2);
    });
    std::thread t2([&] {
        run('a', 3, 3, before_eg);
        run('b', 1, 1, before_hi);
        before_eg.wait();
        run('g', 1, 1, before_c);
        before_hi.wait();
        run('h', 2, 2, before_c);
        run('e', 3, 4, before_k);
        run('i', 2, 2, before_d);
        before_c.wait();
        run('c', 3, 4, before_f);
        before_d.wait();
        run('d', 2, 2, before_f);
        before_f.wait();
        run('f', 3, 4);
    });
    std::thread t3([&] {
        run('a', 4, 4, before_eg);
        run('b', 2, 2, before_hi);
        before_eg.wait();
        run('g', 2, 2, before_c);
        before_hi.wait();
        run('h', 3, 3, before_c);
        run('e', 5, 6, before_k);
        run('i', 3, 3, before_d);
        before_c.wait();
        run('c', 5, 6, before_f);
        before_d.wait();
        run('d', 3, 3, before_f);
        before_f.wait();
        run('f', 5, 6);
    });
    std::thread t4([&] {
        run('a', 5, 5, before_eg);
        run('b', 3, 3, before_hi);
        before_eg.wait();
        run('g', 3, 3, before_c);
        before_hi.wait();
        run('h', 4, 4, before_c);
        run('e', 7, 7, before_k);
        run('i', 4, 5, before_d);
        before_c.wait();
        run('c', 7, 7, before_f);
        before_k.wait();
        run('k', 2, 2, before_f);
        before_d.wait();
        run('d', 4, 4, before_f);
        before_f.wait();
        run('f', 7, 8);
    });
    std::thread t5([&] {
        run('a', 6, 6, before_eg);
        run('b', 4, 4, before_hi);
        before_eg.wait();
        run('g', 4, 4, before_c);
        before_hi.wait();
        run('h', 5, 5, before_c);
        run('e', 8, 8, before_k);
        run('i', 6, 6, before_d);
        before_c.wait();
        run('c', 8, 8, before_f);
        before_k.wait();
        run('k', 3, 4, before_f);
        before_d.wait();
        run('d', 5, 5, before_f);
        before_f.wait();
        run('f', 9, 9);
    });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    std::osyncstream(std::cout) << "Обчислення завершено. Тривалість обчислення "
                                << elapsed.count() << " секунд.";
}