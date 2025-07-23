// Build (ASan): clang++ -g -fsanitize=address leak_demo.cpp -o task2
// Leak:   ./task2 leak
// Fixed : ./task2 fix
// Linux valgrind: valgrind --leak-check=full ./task2 leak

#include <vector>
#include <iostream>
#include <cstdlib>

void leak()
{
    for (int i = 0; i < 1'000'000; ++i)
        new int[100];                         // never freed
}

void fixed()
{
    std::vector<int*> ptrs;
    ptrs.reserve(1'000'000);
    for (int i = 0; i < 1'000'000; ++i)
        ptrs.push_back(new int[100]);
    for (auto p : ptrs) delete[] p;
}

int main(int argc, char* argv[])
{
    if (argc != 2) { std::cout << "usage: ./task2 <leak|fix>\n"; return 1; }
    if (std::string(argv[1]) == "leak") leak();
    else if (std::string(argv[1]) == "fix") fixed();
}
