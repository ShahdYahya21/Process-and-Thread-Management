## Matrix Multiplication Performance Evaluation

### Task Overview
This programming task involves implementing and analyzing different approaches to **matrix multiplication**. The matrices are of size **100 × 100**, and they are filled as follows:

- **Matrix A**: Filled with the student's ID repeated throughout.
- **Matrix B**: Filled with the product of the student's ID and birth year, repeated throughout.

### Approaches Implemented

#### 1. **Naïve Approach**
   - Element-wise multiplication with summation for row-column dot products.
   - **Slowest** method due to lack of parallelism.
   - **Execution Time**: 0.0026034 seconds.
   - **Throughput**: 384.113.

#### 2. **Multiprocessing Approach**
   - Utilizes multiple processes for parallel execution.
   - Performance improves with more processes but plateaus beyond 6 processes.
   - **Best Execution Time** (6 processes): 0.001588 seconds.
   - **Best Throughput**: 629.723.

#### 3. **Multithreading (Joinable) Approach**
   - Uses multiple threads with explicit joining for synchronization.
   - Best performing approach in terms of execution time.
   - **Best Execution Time** (10 threads): 0.0006934 seconds.
   - **Best Throughput**: 1442.169.

#### 4. **Multithreading (Detached) Approach**
   - Threads run independently without synchronization with the main program.
   - Execution time measurement is challenging due to lack of synchronization.

### Conclusion

| Approach            | Best Execution Time (seconds) | Best Throughput |
|---------------------|-----------------------------|----------------|
| **Naïve**           | 0.0026034                    | 384.113        |
| **Multiprocessing** | 0.001588                      | 629.723        |
| **Multithreading (Joinable)** | **0.0006934**        | **1442.169**   |
| **Multithreading (Detached)** | N/A                 | N/A            |

- The **joinable multithreading approach** provides the best performance.
- **Multiprocessing** is also efficient but introduces process management overhead.
- **Detached threads** pose difficulties in execution time measurement.

This analysis highlights the impact of parallel computing on matrix multiplication efficiency.
