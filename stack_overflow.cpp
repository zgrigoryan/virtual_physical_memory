// Build with protection:   g++ -O0 -g -fstack-protector-all stack_overflow.cpp -o task4
// ASan (best):             clang++ -fsanitize=address -g stack_overflow.cpp -o task4_asan
// Run: ./task4 crash

#include <cstring>
#include <iostream>

void crash()
{
    char buf[16];
    std::cout << "Copying 32 bytes into 16‑byte stack buffer…\n";
    std::memset(buf, 'A', 32);          // overflow!
}

void safe()
{
    char buf[16];
    std::memset(buf, 'A', sizeof(buf)); // stays inside bounds
    std::cout << "Safe copy succeeded.\n";
}

int main(int argc, char* argv[])
{
    if (argc != 2) { std::cout << "usage: ./task4 <crash|safe>\n"; return 1; }
    (std::string(argv[1]) == "crash") ? crash() : safe();
}
