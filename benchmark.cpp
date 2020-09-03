#include <benchmark/benchmark.h>

#include "minmax_and_dary_heap.hpp"
#include <vector>
#include <random>

#ifdef _MSC_VER
#define SKA_NOINLINE(...) __declspec(noinline) __VA_ARGS__
#else
#define SKA_NOINLINE(...) __VA_ARGS__ __attribute__((noinline))
#endif

template<typename Distribution, typename Randomness>
SKA_NOINLINE(decltype(auto)) no_inline_random_number(Distribution & distribution, Randomness & randomness)
{
    return distribution(randomness);
}

void benchmark_heap_baseline(benchmark::State & state)
{
    int num_items = state.range(0);
    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 randomness(5);
    while (state.KeepRunning())
    {
        for (int i = 0; i < num_items; ++i)
            benchmark::DoNotOptimize(no_inline_random_number(distribution, randomness));
    }
    state.SetItemsProcessed(num_items * state.iterations());
}
BENCHMARK(benchmark_heap_baseline)->Range(4, 1024*1024*16);

void benchmark_push_minmax_heap(benchmark::State & state)
{
    std::vector<int> heap;
    int num_items = state.range(0);
    heap.reserve(num_items);
    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 randomness(5);
    while (state.KeepRunning())
    {
        heap.clear();
        for (int i = 0; i < num_items; ++i)
        {
            heap.push_back(no_inline_random_number(distribution, randomness));
            push_minmax_heap(heap.begin(), heap.end());
        }
        benchmark::DoNotOptimize(heap.back());
    }
    state.SetItemsProcessed(num_items * state.iterations());
}
BENCHMARK(benchmark_push_minmax_heap)->Range(4, 1024*1024*16);

template<int D>
void benchmark_push_dary_heap(benchmark::State & state)
{
    std::vector<int> heap;
    int num_items = state.range(0);
    heap.reserve(num_items);
    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 randomness(5);
    while (state.KeepRunning())
    {
        heap.clear();
        for (int i = 0; i < num_items; ++i)
        {
            heap.push_back(no_inline_random_number(distribution, randomness));
            push_dary_heap<D>(heap.begin(), heap.end());
        }
        benchmark::DoNotOptimize(heap.back());
    }
    state.SetItemsProcessed(num_items * state.iterations());
}
BENCHMARK_TEMPLATE(benchmark_push_dary_heap, 2)->Range(4, 1024*1024*16);
BENCHMARK_TEMPLATE(benchmark_push_dary_heap, 4)->Range(4, 1024*1024*16);

void benchmark_make_minmax_heap(benchmark::State & state)
{
    std::vector<int> heap;
    int num_items = state.range(0);
    heap.reserve(num_items);
    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 randomness(5);
    while (state.KeepRunning())
    {
        heap.clear();
        for (int i = 0; i < num_items; ++i)
            heap.push_back(no_inline_random_number(distribution, randomness));
        make_minmax_heap(heap.begin(), heap.end());
        benchmark::DoNotOptimize(heap.back());
    }
    state.SetItemsProcessed(num_items * state.iterations());
}
BENCHMARK(benchmark_make_minmax_heap)->Range(4, 1024*1024*16);

template<int D>
void benchmark_make_dary_heap(benchmark::State & state)
{
    std::vector<int> heap;
    int num_items = state.range(0);
    heap.reserve(num_items);
    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 randomness(5);
    while (state.KeepRunning())
    {
        heap.clear();
        for (int i = 0; i < num_items; ++i)
            heap.push_back(no_inline_random_number(distribution, randomness));
        make_dary_heap<D>(heap.begin(), heap.end());
        benchmark::DoNotOptimize(heap.back());
    }
    state.SetItemsProcessed(num_items * state.iterations());
}
BENCHMARK_TEMPLATE(benchmark_make_dary_heap, 2)->Range(4, 1024*1024*16);
BENCHMARK_TEMPLATE(benchmark_make_dary_heap, 4)->Range(4, 1024*1024*16);

void benchmark_pop_minmax_heap_min(benchmark::State & state)
{
    std::vector<int> heap;
    int num_items = state.range(0);
    heap.reserve(num_items);
    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 randomness(5);
    while (state.KeepRunning())
    {
        heap.clear();
        for (int i = 0; i < num_items; ++i)
            heap.push_back(no_inline_random_number(distribution, randomness));
        make_minmax_heap(heap.begin(), heap.end());
        for (int i = 0; i < num_items; ++i)
            pop_minmax_heap_min(heap.begin(), heap.end() - i);
        benchmark::DoNotOptimize(heap.back());
    }
    state.SetItemsProcessed(num_items * state.iterations());
}
BENCHMARK(benchmark_pop_minmax_heap_min)->Range(4, 1024*1024*16);

void benchmark_pop_minmax_heap_max(benchmark::State & state)
{
    std::vector<int> heap;
    int num_items = state.range(0);
    heap.reserve(num_items);
    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 randomness(5);
    while (state.KeepRunning())
    {
        heap.clear();
        for (int i = 0; i < num_items; ++i)
            heap.push_back(no_inline_random_number(distribution, randomness));
        make_minmax_heap(heap.begin(), heap.end());
        for (int i = 0; i < num_items; ++i)
            pop_minmax_heap_max(heap.begin(), heap.end() - i);
        benchmark::DoNotOptimize(heap.back());
    }
    state.SetItemsProcessed(num_items * state.iterations());
}
BENCHMARK(benchmark_pop_minmax_heap_max)->Range(4, 1024*1024*16);

template<int D>
void benchmark_pop_dary_heap(benchmark::State & state)
{
    int num_items = state.range(0);
    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 randomness(5);
    std::vector<int> heap;
    heap.reserve(num_items);
    while (state.KeepRunning())
    {
        heap.clear();
        for (int i = 0; i < num_items; ++i)
            heap.push_back(no_inline_random_number(distribution, randomness));
        make_dary_heap<D>(heap.begin(), heap.end());
        for (int i = 0; i < num_items; ++i)
            pop_dary_heap<D>(heap.begin(), heap.end() - i);
        benchmark::DoNotOptimize(heap.back());
    }
    state.SetItemsProcessed(num_items * state.iterations());
}
BENCHMARK_TEMPLATE(benchmark_pop_dary_heap, 2)->Range(4, 1024*1024*16);
BENCHMARK_TEMPLATE(benchmark_pop_dary_heap, 4)->Range(4, 1024*1024*16);



BENCHMARK_MAIN();

