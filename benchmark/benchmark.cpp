#include <benchmark/benchmark.h>
#include "big_integer_benchmark.hpp"
#include "big_float_benchmark.hpp"

namespace ut {
using namespace oiak;

//TEMPLATE:
//
//static void BM_SomeFunction(benchmark::State& state) {
//	Perform setup here
//	for (auto _ : state) {
//		This code gets timed
//	}
//}
//Register the function as a benchmark
//BENCHMARK(BM_SomeFunction);

BENCHMARK_MAIN();

} // namespace ut
