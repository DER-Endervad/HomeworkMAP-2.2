#include <iostream>
#include <thread>
#include <Windows.h>
#include <mutex>

void flow();
void print_flow(int i, HANDLE console);
void print_flow2(int y, HANDLE console, int x);
void gotoxy(int x, int y);

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    flow();
    gotoxy(0, 6);
    system("Pause");
}

std::atomic<int> counter = 1;
std::mutex m;

void flow() {
    auto start = std::chrono::steady_clock::now();
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 15);
    gotoxy(0, 0); std::cout << "#";
    gotoxy(3, 0); std::cout << "id";
    gotoxy(25, 0); std::cout << "Progress Bar";
    gotoxy(40, 0); std::cout << "Time";

    int size_t = 5;
    std::thread* t = new std::thread[size_t];
    for (int i = 0; i < size_t; i++) {
        t[i] = std::thread(print_flow, i, console);
    }
    for (int i = 0; i < size_t; i++) {
        t[i].join();
    }
}

void print_flow(int y, HANDLE console) {
    auto start = std::chrono::steady_clock::now();
    m.lock();
    gotoxy(0, y+1); 
    std::cout << y;
    m.unlock();

    m.lock();
    gotoxy(3, y + 1);
    std::cout << std::this_thread::get_id << std::endl;
    m.unlock();

    m.lock();
    for (int i = 0; i < 9; i++) {
        gotoxy(26+i, y + 1);
        SetConsoleTextAttribute(console, 10);
        printf("-");
    }
    SetConsoleTextAttribute(console, 15);
    m.unlock();
    Sleep(500);

    print_flow2(y, console, 0);
    print_flow2(y, console, 1);
    print_flow2(y, console, 2);
    print_flow2(y, console, 3);
    print_flow2(y, console, 4);
    print_flow2(y, console, 5);
    print_flow2(y, console, 6);
    print_flow2(y, console, 7);
    print_flow2(y, console, 8);
    m.lock();
    SetConsoleTextAttribute(console, 15);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    gotoxy(40, 1+y); std::cout << time.count();
    m.unlock();
}

void print_flow2(int y, HANDLE console, int x) {
    m.lock();
    gotoxy(26 + x, y + 1);
    SetConsoleTextAttribute(console, 12);
    std::cout << "-";
    Sleep(200);
    m.unlock();
}

void gotoxy(int x, int y)
{
    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(hConsole, position);
}