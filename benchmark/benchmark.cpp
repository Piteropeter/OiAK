#include <benchmark/benchmark.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

static void BM_SomeFunction(benchmark::State& state) {
	// Perform setup here
	for (auto _ : state) {
		// This code gets timed
		std::string test = "XD";
	}
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);
// Run the benchmark
BENCHMARK_MAIN();

} // namespace ut
