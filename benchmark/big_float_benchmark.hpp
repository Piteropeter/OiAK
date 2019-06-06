#include <benchmark/benchmark.h>
#include "BigFloat.h"

namespace ut {
using namespace oiak;

/// BIG FLOAT CONSTRUCTION

static void Construction_1_BigFloat(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigFloat>(1, BigFloat("23678542342.678678678678435632378789923456789ffff"));
    }
}
BENCHMARK(Construction_1_BigFloat);

static void Construction_10_BigFloat(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigFloat>(10, BigFloat("23678542342.678678678678435632378789923456789ffff"));
    }
}
BENCHMARK(Construction_10_BigFloat);

static void Construction_100_BigFloat(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigFloat>(100, BigFloat("23678542342.678678678678435632378789923456789ffff"));
    }
}
BENCHMARK(Construction_100_BigFloat);

static void Construction_1000_BigFloat(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigFloat>(1000, BigFloat("23678542342.678678678678435632378789923456789ffff"));
    }
}
BENCHMARK(Construction_1000_BigFloat);

static void Construction_10000_BigFloat(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigFloat>(10000, BigFloat("23678542342.678678678678435632378789923456789ffff"));
    }
}
BENCHMARK(Construction_10000_BigFloat);

static void Construction_100000_BigFloat(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigFloat>(100000, BigFloat("23678542342.678678678678435632378789923456789ffff"));
    }
}
BENCHMARK(Construction_100000_BigFloat);

/// BIG FLOAT SUM

static void BigFloat_1_sum(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 1; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigFloat_1_sum);

static void BigFloat_10_sums(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 10; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigFloat_10_sums);

static void BigFloat_100_sums(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 100; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigFloat_100_sums);

static void BigFloat_1000_sums(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 1000; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigFloat_1000_sums);

static void BigFloat_10000_sums(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 10000; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigFloat_10000_sums);

static void BigFloat_100000_sums(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 100000; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigFloat_100000_sums);

/// BIG FLOAT SUBTRACTION

static void BigFloat_1_subtraction(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 1; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigFloat_1_subtraction);

static void BigFloat_10_subtractions(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 10; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigFloat_10_subtractions);

static void BigFloat_100_subtractions(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 100; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigFloat_100_subtractions);

static void BigFloat_1000_subtractions(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 1000; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigFloat_1000_subtractions);

static void BigFloat_10000_subtractions(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 10000; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigFloat_10000_subtractions);

static void BigFloat_100000_subtractions(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 100000; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigFloat_100000_subtractions);

/// BIG FLOAT MULTIPLYING

static void BigFloat_1_multiplication(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 1; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigFloat_1_multiplication);

static void BigFloat_10_multiplications(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 10; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigFloat_10_multiplications);

static void BigFloat_100_multiplications(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 100; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigFloat_100_multiplications);

static void BigFloat_1000_multiplications(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 1000; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigFloat_1000_multiplications);

static void BigFloat_10000_multiplications(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 10000; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigFloat_10000_multiplications);

static void BigFloat_100000_multiplications(benchmark::State& state) {
    auto x = BigFloat("23678542342.678678678678435632378789923456789ffff");
    auto y = BigFloat("34561209890908.594899999999999fffffff234432");
    for(auto _ : state) {
        for(auto i = 0; i < 100000; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigFloat_100000_multiplications);

/// BIG FLOAT DIVISION

static void BigFloat_1_division(benchmark::State& state) {
    auto x = BigFloat("23642.ff");
    auto y = BigFloat("34.52");
    for(auto _ : state) {
        for(auto i = 0; i < 1; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigFloat_1_division);

static void BigFloat_10_divisions(benchmark::State& state) {
    auto x = BigFloat("23642.ff");
    auto y = BigFloat("34.52");
    for(auto _ : state) {
        for(auto i = 0; i < 10; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigFloat_10_divisions);

static void BigFloat_100_divisions(benchmark::State& state) {
    auto x = BigFloat("23642.ff");
    auto y = BigFloat("34.52");
    for(auto _ : state) {
        for(auto i = 0; i < 100; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigFloat_100_divisions);

static void BigFloat_1000_divisions(benchmark::State& state) {
    auto x = BigFloat("23642.ff");
    auto y = BigFloat("34.52");
    for(auto _ : state) {
        for(auto i = 0; i < 1000; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigFloat_1000_divisions);

static void BigFloat_10000_divisions(benchmark::State& state) {
    auto x = BigFloat("23642.ff");
    auto y = BigFloat("34.52");
    for(auto _ : state) {
        for(auto i = 0; i < 10000; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigFloat_10000_divisions);

static void BigFloat_100000_divisions(benchmark::State& state) {
    auto x = BigFloat("23642.ff");
    auto y = BigFloat("34.52");
    for(auto _ : state) {
        for(auto i = 0; i < 100000; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigFloat_100000_divisions);

} // namespace ut
