#include <benchmark/benchmark.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

/// BIG INTEGER CONSTRUCTION

static void Construction_1_BigInteger(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigInteger>(1, BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef"));
    }
}
BENCHMARK(Construction_1_BigInteger);

static void Construction_10_BigInteger(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigInteger>(10, BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef"));
    }
}
BENCHMARK(Construction_10_BigInteger);

static void Construction_100_BigInteger(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigInteger>(100, BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef"));
    }
}
BENCHMARK(Construction_100_BigInteger);

static void Construction_1000_BigInteger(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigInteger>(1000, BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef"));
    }
}
BENCHMARK(Construction_1000_BigInteger);

static void Construction_10000_BigInteger(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigInteger>(10000, BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef"));
    }
}
BENCHMARK(Construction_10000_BigInteger);

static void Construction_100000_BigInteger(benchmark::State& state) {
    for(auto _ : state) {
        auto x = std::vector<BigInteger>(100000, BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef"));
    }
}
BENCHMARK(Construction_100000_BigInteger);

/// BIG INTEGER SUM

static void BigInteger_1_sum(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 1; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigInteger_1_sum);

static void BigInteger_10_sums(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 10; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigInteger_10_sums);

static void BigInteger_100_sums(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 100; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigInteger_100_sums);

static void BigInteger_1000_sums(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 1000; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigInteger_1000_sums);

static void BigInteger_10000_sums(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 10000; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigInteger_10000_sums);

static void BigInteger_100000_sums(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 100000; i++) {
            x + y;
        }
    }
}
BENCHMARK(BigInteger_100000_sums);

/// BIG INTEGER SUBTRACTION

static void BigInteger_1_subtraction(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 1; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigInteger_1_subtraction);

static void BigInteger_10_subtractions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 10; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigInteger_10_subtractions);

static void BigInteger_100_subtractions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 100; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigInteger_100_subtractions);

static void BigInteger_1000_subtractions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 1000; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigInteger_1000_subtractions);

static void BigInteger_10000_subtractions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 10000; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigInteger_10000_subtractions);

static void BigInteger_100000_subtractions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 100000; i++) {
            x - y;
        }
    }
}
BENCHMARK(BigInteger_100000_subtractions);

/// BIG INTEGER MULTIPLYING

static void BigInteger_1_multiplication(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 1; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigInteger_1_multiplication);

static void BigInteger_10_multiplications(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 10; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigInteger_10_multiplications);

static void BigInteger_100_multiplications(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 100; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigInteger_100_multiplications);

static void BigInteger_1000_multiplications(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 1000; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigInteger_1000_multiplications);

static void BigInteger_10000_multiplications(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 10000; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigInteger_10000_multiplications);

static void BigInteger_100000_multiplications(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 100000; i++) {
            x* y;
        }
    }
}
BENCHMARK(BigInteger_100000_multiplications);

/// BIG INTEGER DIVISION

static void BigInteger_1_division(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 1; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigInteger_1_division);

static void BigInteger_10_divisions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 10; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigInteger_10_divisions);

static void BigInteger_100_divisions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 100; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigInteger_100_divisions);

static void BigInteger_1000_divisions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 1000; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigInteger_1000_divisions);

static void BigInteger_10000_divisions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 10000; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigInteger_10000_divisions);

static void BigInteger_100000_divisions(benchmark::State& state) {
    auto x = BigInteger("2340895789234759028347509876457896022987634059023845761902348756908254367abcdef");
    auto y = BigInteger("12048723945f98798999999999999999993465987897987343453485749823475fff3452345fa");
    for(auto _ : state) {
        for(auto i = 0; i < 100000; i++) {
            x / y;
        }
    }
}
BENCHMARK(BigInteger_100000_divisions);

} // namespace ut
