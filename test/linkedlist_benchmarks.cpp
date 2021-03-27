#include "linkedlist.hpp"
#include <benchmark/benchmark.h>

using namespace lib_hashtable;

static void
BENCHMARK_LinkedList_insert_at_head(benchmark::State& state)
{
  auto list = LinkedList<std::string>();
  uint64_t i = 0;
  for (auto _ : state) {
    state.PauseTiming();
    auto value = std::to_string(i);
    state.ResumeTiming();

    auto err = list.insert_at_head(value);

    state.PauseTiming();
    if (err != ERR_OK) {
      state.SkipWithError(std::to_string((int)err).c_str());
    }
    state.ResumeTiming();
    i++;
  }
}

static void
BENCHMARK_LinkedList_remove_head(benchmark::State& state)
{
  auto list = LinkedList<std::string>();
  auto err = list.insert_at_head("bunnyfoofoo");
  if (err != ERR_OK) {
    state.SkipWithError(std::to_string((int)err).c_str());
  }

  for (auto _ : state) {
    err = list.remove_head();

    state.PauseTiming();
    if (err != ERR_OK) {
      state.SkipWithError(std::to_string((int)err).c_str());
    }
    // insert_at_head it back
    err = list.insert_at_head("bunnyfoofoo");
    if (err != ERR_OK) {
      state.SkipWithError(std::to_string((int)err).c_str());
    }
    state.ResumeTiming();
  }
}

BENCHMARK(BENCHMARK_LinkedList_insert_at_head);
BENCHMARK(BENCHMARK_LinkedList_remove_head);
BENCHMARK_MAIN();
