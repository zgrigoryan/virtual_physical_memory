// Build: g++ -O2 -std=c++20 fragmentation.cpp -o task3
// Run  : ./task3 > frag.csv   # CSV: step,live_allocs,arena,free,largest_free
//
// Linux-only: uses mallinfo2().  On macOS, compile but largest_free = 0.

#include <iostream>
#include <random>
#include <vector>

#ifdef __linux__
  #include <malloc.h>
#endif

struct Block { char* p; size_t sz; };
int main()
{
    std::mt19937_64 rng(42);
    std::uniform_int_distribution<size_t> size_dist(8, 256);
    std::uniform_int_distribution<int>     op_dist(0, 1);   // 0 = alloc, 1 = free

    std::vector<Block> live;
    live.reserve(100'000);

    std::cout << "step,live_allocs,arena,free,largest_free\n";

    for (int step = 1; step <= 200'000; ++step)
    {
        if (op_dist(rng) == 0 || live.empty()) {            // allocate
            size_t sz = size_dist(rng);
            live.push_back({new char[sz], sz});
        } else {                                            // free random
            size_t idx = rng() % live.size();
            delete[] live[idx].p;
            live[idx] = live.back();
            live.pop_back();
        }

#ifdef __linux__
        struct mallinfo2 mi = mallinfo2();
        std::cout << step << ',' << live.size() << ','
                  << mi.arena   << ',' << mi.fordblks << ','
                  << mi.keepcost << '\n';
#else
        std::cout << step << ',' << live.size() << ",0,0,0\n";
#endif
    }
}
