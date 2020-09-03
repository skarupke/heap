# C++ Implementation of Min-Max heap and D-ary heap

See the blog post at
https://probablydance.com/2020/08/31/on-modern-hardware-the-min-max-heap-beats-a-binary-heap/

The benchmarks require google benchmark to run. On Ubuntu you can "apt install libbenchmark-dev"
Otherwise you can find it here:
https://github.com/google/benchmark


The benchmark results are as follows:  
To calculate the time to push an item take  
*time(benchmark_push_minmax_heap) - time(benchmark_heap_baseline)*  
To calculate the time to make the heap take  
*time(benchmark_make_minmax_heap) - time(benchmark_heap_baseline)*  
To calculate the time to pop an item take  
*time(benchmark_pop_minmax_heap_min) - time(benchmark_make_minmax_heap)* or  
*time(benchmark_pop_minmax_heap_max) - time(benchmark_make_minmax_heap)*  

Meaning make sure to always subtract the baseline or the time to make the heap.

