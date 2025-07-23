// Build: g++ -O2 -std=c++20 virt_memory_simulation.cpp -o task1
// Run  : ./task1    (watch top/htop/vmstat in another window)

#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <new>

constexpr size_t GiB = 1ull << 30;
constexpr size_t MEMORY_SIZE = 2 * GiB;
constexpr size_t PAGE_SIZE   = 4096;

void touch(char* mem, const std::vector<size_t>& order, const char* tag)
{
    const auto t0 = std::chrono::high_resolution_clock::now();
    for (size_t idx : order) mem[idx] = static_cast<char>(idx);
    const auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << tag << " access: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << " ms\n";
}

int main()
{
    std::cout << "Allocating 2 GiB (may exceed RAM)…\n";
    char* mem = new (std::nothrow) char[MEMORY_SIZE];
    if (!mem) { std::cerr << "Allocation failed\n"; return 1; }

    std::vector<size_t> sequential(MEMORY_SIZE / PAGE_SIZE);
    for (size_t i = 0; i < sequential.size(); ++i) sequential[i] = i * PAGE_SIZE;

    std::vector<size_t> random = sequential;
    std::shuffle(random.begin(), random.end(), std::mt19937{std::random_device{}()});

    std::cout << "→ Watch your system monitor now (top/htop)…\n";
    touch(mem, sequential, "Sequential");
    touch(mem, random,     "Random"    );

    delete[] mem;
}