# 🖥️ Virtual vs Physical Memory — Experiments

Four bite‑sized C++ programs that make the OS and allocator show their hands:
paging delays, leaks, fragmentation, and stack overflows.

| Task | File | One‑liner |
|------|------|-----------|
| **1  Virtual‑memory simulation** | `virt_memory_simulation.cpp` | `g++ -O2 -std=c++20 virt_memory_simulation.cpp -o task1 && ./task1` |
| **2  Leak + fix** | `leak_demo.cpp` | `clang++ -g -fsanitize=address leak_demo.cpp -o task2 && ./task2 leak` |
| **3  Fragmentation graph** | `fragmentation.cpp` | `g++ -O2 -std=c++20 fragmentation.cpp -o task3 && ./task3 > frag.csv` |
| **4  Stack overflow** | `stack_overflow.cpp` | `g++ -O0 -g -fstack-protector-all stack_overflow.cpp -o task4 && ./task4 crash` |

---

## 1  Virtual‑memory simulation

* Allocates **2 GiB** (may exceed RAM).  
* Touches every page **sequentially**, then **randomly**.  
* Measure time and watch **`top` / `htop` / `vmstat 1`**:  
  random walk thrashes the TLB & pre‑fetcher → slower.

---

## 2  Memory‑leak demo 

```bash
clang++ -g -fsanitize=address task2_leak_demo.cpp -o task2
./task2 leak   # ASan prints leaked 38 MiB
./task2 fix    # "All heap blocks were freed"
``` 
## 3  Fragmentation harness 
Randomly allocs/frees 8‑256 B blocks 200 k times.

CSV columns (Linux):
step,live_allocs,arena,free,largest_free.

Plot largest_free vs step → it steadily shrinks while total arena grows,
visualising external fragmentation.

## 4  Buffer overflow 
```bash
# With stack protector
g++ -O0 -g -fstack-protector-all task4_stack_overflow.cpp -o task4
./task4 crash     # "*** stack smashing detected ***"

# With AddressSanitizer
clang++ -g -fsanitize=address task4_stack_overflow.cpp -o task4_asan
./task4_asan crash  # ASan highlights the 16‑byte over‑write
```
Enjoy breaking (and then fixing) memory! 🔧