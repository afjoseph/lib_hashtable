#include "hashtable.hpp"
#include <benchmark/benchmark.h>

using namespace lib_hashtable;

static void
BENCHMARK_HashTable_put(benchmark::State& state)
{
  auto table = HashTable<std::string, std::string, 0xffff>();
  uint64_t i = 0;
  for (auto _ : state) {
    state.PauseTiming();
    auto key = std::to_string(i);
    auto value = std::to_string(i);
    state.ResumeTiming();

    auto err = table.put(key, value);

    state.PauseTiming();
    if (err != ERR_OK) {
      state.SkipWithError(std::to_string((int)err).c_str());
    }
    state.ResumeTiming();
    i++;
  }
}

static void
BENCHMARK_HashTable_get(benchmark::State& state)
{
  auto table = HashTable<std::string, std::string, 0xffff>();
  auto err = table.put("bunnyfoofoo", "bunnyfoofoo");
  if (err != ERR_OK) {
    state.SkipWithError(std::to_string((int)err).c_str());
  }

  std::string value;
  std::string key = "bunnyfoofoo";
  for (auto _ : state) {
    err = table.get(key, value);

    state.PauseTiming();
    if (err != ERR_OK) {
      state.SkipWithError(std::to_string((int)err).c_str());
    }
    state.ResumeTiming();
  }
}

static void
BENCHMARK_HashTable_remove(benchmark::State& state)
{
  auto table = HashTable<std::string, std::string, 0xffff>();
  auto err = table.put("bunnyfoofoo", "bunnyfoofoo");
  if (err != ERR_OK) {
    state.SkipWithError(std::to_string((int)err).c_str());
  }

  for (auto _ : state) {
    err = table.remove("bunnyfoofoo");

    state.PauseTiming();
    if (err != ERR_OK) {
      state.SkipWithError(std::to_string((int)err).c_str());
    }
    // put it back
    err = table.put("bunnyfoofoo", "bunnyfoofoo");
    if (err != ERR_OK) {
      state.SkipWithError(std::to_string((int)err).c_str());
    }
    state.ResumeTiming();
  }
}

BENCHMARK(BENCHMARK_HashTable_put);
BENCHMARK(BENCHMARK_HashTable_get);
BENCHMARK(BENCHMARK_HashTable_remove);
BENCHMARK_MAIN();
