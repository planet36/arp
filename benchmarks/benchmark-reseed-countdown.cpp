// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "randp.hpp"

// https://github.com/google/benchmark

#include <benchmark/benchmark.h>
#include <concepts>
#include <functional>

void
BM_rand_buf_4GiB(benchmark::State& state,
                 const std::function<void(uint8_t*, size_t)>& fn)
{
	// Perform setup here

	uint8_t buf[1U << 8];

	for (auto _ : state)
	{
		// This code gets timed

		for (size_t i = 0; i < (1UL << 32) / sizeof(buf); ++i)
		{
			fn(buf, sizeof(buf));
		}
	}
}

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <string>
#include <thread>

int
main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	// copied from benchmark.h
	benchmark::Initialize(&argc, argv);

	if (benchmark::ReportUnrecognizedArguments(argc, argv))
		return 1;

	// {{{ determine num_threads

	constexpr unsigned int min_threads = 1;
	const unsigned int max_threads = (std::thread::hardware_concurrency() != 0) ?
	                                 std::thread::hardware_concurrency() :
	                                 min_threads;
	// https://en.wikipedia.org/wiki/Elvis_operator
	//const unsigned int max_threads = std::thread::hardware_concurrency() ?: min_threads;

	unsigned int num_threads;

	try
	{
		num_threads = static_cast<unsigned int>(std::stoi(std::getenv("NUM_THREADS")));
	}
	catch (...)
	{
		num_threads = max_threads;
	}

	num_threads = std::clamp(num_threads, min_threads, max_threads);

	/*
	if (num_threads > min_threads)
		// Don't use all the cores
		--num_threads;
	*/

	// }}}

	// {{{ accuracy testing

	// }}}

	// {{{ speed

	std::string prefix;

	if (num_threads == 1)
	{
		prefix = "rand_buf_4GiB:";
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_1>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  1>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_2>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  2>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_3>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  3>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_4>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  4>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_5>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  5>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_6>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  6>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_7>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  7>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_8>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  8>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_9>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  9>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<10>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 10>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<11>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 11>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<12>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 12>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<13>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 13>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<14>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 14>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<15>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 15>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<16>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 16>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<17>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 17>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<18>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 18>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<19>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 19>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<20>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 20>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<21>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 21>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<22>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 22>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<23>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 23>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<24>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 24>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<25>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 25>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<26>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 26>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<27>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 27>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<28>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 28>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<29>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 29>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<30>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 30>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<31>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 31>)->Unit(benchmark::kMillisecond);
	}
	else
	{
		prefix = "rand_buf_4GiB:";
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_1>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  1>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_2>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  2>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_3>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  3>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_4>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  4>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_5>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  5>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_6>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  6>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_7>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  7>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_8>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  8>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<_9>", BM_rand_buf_4GiB, randp_bytes<0x10,1U <<  9>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<10>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 10>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<11>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 11>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<12>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 12>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<13>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 13>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<14>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 14>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<15>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 15>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<16>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 16>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<17>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 17>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<18>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 18>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<19>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 19>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<20>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 20>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<21>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 21>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<22>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 22>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<23>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 23>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<24>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 24>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<25>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 25>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<26>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 26>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<27>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 27>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<28>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 28>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<29>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 29>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<30>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 30>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<31>", BM_rand_buf_4GiB, randp_bytes<0x10,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
	}

	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();

	// }}}

	return 0;
}
