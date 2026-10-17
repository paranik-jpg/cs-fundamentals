# CS Fundamentals Revision via Implementation

Hands-on, empirical experiments and code implementations verifying core Computer Science concepts across Operating Systems, Concurrency, Computer Architecture, Networking, and Database Internals.

---

## Experiment Catalog

### 1. Operating Systems & Process Management
- **Preemptive CPU Scheduling Emulation** ([`preemptive_CPU_scheduling_emulation.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/preemptive_CPU_scheduling_emulation.cpp))  
  Simulates process scheduling algorithms (e.g., Round Robin, SRTF) calculating Arrival Time (AT), Burst Time (BT), Completion Time (CT), Turnaround Time (TAT), Waiting Time (WT), and Response Time (RT).
- **Process Cloning & Zombie Generation** ([`process_cloning_and_zombie_generation.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/process_cloning_and_zombie_generation.cpp))  
  Demonstrates `fork()`, parent-child lifecycle dynamics, and how un-reaped terminated children become zombie processes in the OS process table.
- **Syscall Context Switch Overhead** ([`syscall_context_switch_tax/`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/syscall_context_switch_tax/))  
  Benchmarks the execution time cost between direct raw system calls (`write()`) and user-space buffered I/O (`fwrite()` / `std::ofstream`).
- **Banker's Algorithm Safety Audit** ([`bankers_algorithm_safety_audit.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/bankers_algorithm_safety_audit.cpp))  
  Implements the classic Banker's algorithm to analyze allocation matrices and determine whether the system is in a deadlock-free safe state.
- **Elevator (SCAN) Algorithm** ([`elevator_algorithm.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/elevator_algorithm.cpp))  
  Simulates disk head scheduling using the elevator algorithm to minimize seek latency across track requests.
- **Unix Inode File Size Limits** ([`Unix_inode_file_size_limits.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/Unix_inode_file_size_limits.cpp))  
  Calculates maximum addressable file sizes based on direct, single, double, and triple indirect block pointers.

---

### 2. Concurrency & Multithreading
- **Mutex Ownership vs. Semaphore Signaling** ([`mutex_ownership_vs_semaphore_signaling.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/mutex_ownership_vs_semaphore_signaling.cpp))  
  Highlights the fundamental distinction between a mutex (which requires ownership: only the locking thread may unlock) and a counting semaphore (an inter-thread signaling mechanism).
- **Circular Wait & GDB Backtracking** ([`circular_wait_and_gdb_backtracking.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/circular_wait_and_gdb_backtracking.cpp))  
  Reproduces circular wait deadlocks between threads acquiring locks out of order; designed to be inspected via GDB thread stack traces.
- **ThreadSanitizer & Data Race Detection** ([`threadsanitizer_and_the_data_race.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/threadsanitizer_and_the_data_race.cpp))  
  Demonstrates non-atomic read-modify-write data races on shared memory, configured to trigger Clang/GCC ThreadSanitizer (`-fsanitize=thread`).

---

### 3. Memory & Computer Architecture
- **Belady's Anomaly Simulator** ([`beladys_anomaly_simulator.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/beladys_anomaly_simulator.cpp))  
  Demonstrates Belady's Anomaly where increasing the number of page frames leads to *more* page faults under FIFO page replacement.
- **TLB & Effective Memory Access Time (EMAT)** ([`TLB_and_EMAT.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/TLB_and_EMAT.cpp))  
  Models Translation Lookaside Buffer (TLB) hit ratios and calculates Effective Memory Access Time based on multi-level page table walk penalties.
- **Structure Padding & Greedy Alignment** ([`struct_padding_and_greedy_alignment.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/struct_padding_and_greedy_alignment.cpp))  
  Measures structure padding, memory alignment boundaries, and shows how greedy field ordering minimizes struct footprint using `offsetof`.
- **Binary Executable Segments** ([`binary_executable_segments.c`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/binary_executable_segments.c))  
  Explores ELF binary layout: mapping variables to `.text`, `.rodata`, `.data`, `.bss`, stack, and heap.
- **Virtual Pointer (vptr) Hijacking** ([`dynamic_polymorphism_and_vptr_hijacking.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/dynamic_polymorphism_and_vptr_hijacking.cpp))  
  Inspects the vtable pointer layout in C++ polymorphic objects and bypasses access restrictions via pointer manipulation.
- **Shallow vs. Deep Copy** ([`shallow_vs_deep_copy.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/shallow_vs_deep_copy.cpp))  
  Illustrates double-free errors and heap pointer aliasing caused by default shallow copy semantics versus customized deep copy constructors.

---

### 4. Networking
- **Raw Sockets & `SO_REUSEPORT`** ([`raw_sockets_and_SO_REUSEPORT.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/raw_sockets_and_SO_REUSEPORT.cpp))  
  Demonstrates port binding behavior and socket load balancing across multiple processes using `SO_REUSEPORT`.
- **Backlog Queue Overflow** ([`backlog_queue_overflow.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/backlog_queue_overflow.cpp))  
  Investigates TCP `listen(backlog)` queue saturation and connection dropping behavior under bursty incoming connection traffic.
- **HTTP Parsing and Framing** ([`HTTP_parsing_and_framing.cpp`](file:///home/para_nik/cs_fundamentals_revision_via_implementation/HTTP_parsing_and_framing.cpp))  
  Low-level socket HTTP request/response parsing and stream framing.

---

### 5. Database Systems (SQLite Internals)
- **B+ Tree Index Optimization** (`B+tree_index_optimization/`)  
  Evaluates query performance differences between full table scans and index scans on B+ tree structures.
- **Write-Ahead Logging (WAL) Inspection** (`WAL_inspection/`)  
  Explores SQLite write-ahead log operations, `-wal` and `-shm` shared memory coordination during concurrent reads and writes.
- **Dirty Reads & Lock Contention** (`dirty_read_and_lock_contention/`)  
  Experiments with database transactions, lock modes, and isolation guarantees.
- **Correlated Subqueries vs. CTEs** (`correlated_subqueries_and_CTEs/`)  
  Compares execution plans and performance between correlated subqueries and Common Table Expressions (CTEs).
- **Join Multiplication** (`join_multiplication/`)  
  Demonstrates cardinality explosions and query cost implications in Cartesian and unindexed relational joins.
- **Materialized Views & Stale Cache** (`materialized_view_stale_cache/`)  
  Explores cache invalidation, refresh strategies, and stale data reads.

---

## Building and Running

Compile individual C++ experiments using standard `g++` or `clang++`:

```bash
# Standard compilation
g++ -O2 -std=c++20 <experiment_name>.cpp -o <experiment_name>

# Concurrency with ThreadSanitizer
g++ -O1 -g -std=c++20 -fsanitize=thread -pthread threadsanitizer_and_the_data_race.cpp -o threadsanitizer_and_the_data_race

# Inspecting assembly / symbols
objdump -t binary_executable_segments.o
size binary_executable_segments.o
```

