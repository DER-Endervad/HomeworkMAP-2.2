#include <iostream>
#include <thread>
#include <Windows.h>
#include <mutex>

void flow();
void print_flow();

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::thread t1(print_flow); t1.join(); std::cout << "\n" << std::endl;
    std::thread t2(print_flow); t2.join(); std::cout << "\n" << std::endl;
    std::thread t3(print_flow); t3.join(); std::cout << "\n" << std::endl;
    std::thread t4(print_flow); t4.join(); std::cout << "\n" << std::endl;
}

std::atomic<int> counter = 1;
std::mutex m;

void print_flow() {
    //m.lock();
    auto start = std::chrono::steady_clock::now();
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 15);
    std::cout << "Номер поток: " << counter.exchange(counter + 1) << std::endl;
    std::cout << "Идентификатор потока: " << std::this_thread::get_id << std::endl;
    for (int a = 1, b = 9; a < 11; a++, b--) {
        printf("\r");
        for (int i = 0; i < a; i++) {
            SetConsoleTextAttribute(console, 10);
            printf("-");
        }
        for (int j = 0; j < b; j++) {
            SetConsoleTextAttribute(console, 12);
            printf("-");
        }
        printf("\r");
        Sleep(500);
    }
    printf("----------\n");
    SetConsoleTextAttribute(console, 15);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << "Время затраченное при обработке потока: " << time.count() << std::endl;
    //m.unlock();
}