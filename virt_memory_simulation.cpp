#include <iostream>
#include <vector>
#include <chrono>
#include <random>

constexpr size_t GB = 1024 * 1024 * 1024;
constexpr size_t MEMORY_SIZE = 2 * GB;
constexpr size_t PAGE_SIZE = 4096;

void sequential_access(char* memory, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < size; i += PAGE_SIZE) {
        memory[i] = static_cast<char>(i % 256);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Sequential access time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

void random_access(char* memory, size_t size) {
    std::vector<size_t> indices(size / PAGE_SIZE);
    for (size_t i = 0; i < indices.size(); ++i) {
        indices[i] = i * PAGE_SIZE;
    }

    std::shuffle(indices.begin(), indices.end(), std::mt19937{std::random_device{}()});

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t idx : indices) {
        memory[idx] = static_cast<char>(idx % 256);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Random access time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

int main() {
    std::cout << "Allocating 2GB memory...\n";
    char* memory = new (std::nothrow) char[MEMORY_SIZE];

    if (!memory) {
        std::cerr << "Memory allocation failed!\n";
        return 1;
    }

    std::cout << "Starting sequential access...\n";
    sequential_access(memory, MEMORY_SIZE);

    std::cout << "Starting random access...\n";
    random_access(memory, MEMORY_SIZE);

    delete[] memory;
    return 0;
}


