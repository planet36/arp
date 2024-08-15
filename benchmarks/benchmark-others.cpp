// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

// {{{ copied from rdrand.h
// https://github.com/planet36/dotfiles/blob/main/link/.local/include/rdrand.h

#include <immintrin.h>

// _rd{rand,seed}{16,32,64}_step returns 0 if a random value was NOT generated

#if defined(__RDRND__)
static unsigned short
rdrand16()
{
	unsigned short ret = 0;
	static_assert(sizeof(ret) * 8 == 16);
	while (_rdrand16_step(&ret) == 0)
	{}
	return ret;
}

static unsigned int
rdrand32()
{
	unsigned int ret = 0;
	static_assert(sizeof(ret) * 8 == 32);
	while (_rdrand32_step(&ret) == 0)
	{}
	return ret;
}

static unsigned long long
rdrand64()
{
	unsigned long long ret = 0;
	static_assert(sizeof(ret) * 8 == 64);
	while (_rdrand64_step(&ret) == 0)
	{}
	return ret;
}
#else
#warning "__RDRND__ not defined"
#endif

#if defined(__RDSEED__)
static unsigned short
rdseed16()
{
	unsigned short ret = 0;
	static_assert(sizeof(ret) * 8 == 16);
	while (_rdseed16_step(&ret) == 0)
	{}
	return ret;
}

static unsigned int
rdseed32()
{
	unsigned int ret = 0;
	static_assert(sizeof(ret) * 8 == 32);
	while (_rdseed32_step(&ret) == 0)
	{}
	return ret;
}

static unsigned long long
rdseed64()
{
	unsigned long long ret = 0;
	static_assert(sizeof(ret) * 8 == 64);
	while (_rdseed64_step(&ret) == 0)
	{}
	return ret;
}
#else
#warning "__RDSEED__ not defined"
#endif

// }}}

#include "../arp.h"

// https://github.com/google/benchmark

#include <benchmark/benchmark.h>
#include <concepts>
#include <functional>

template <std::unsigned_integral T>
void
BM_rand_uint(benchmark::State& state, const std::function<T()>& fn)
{
	// Perform setup here

	for (auto _ : state)
	{
		// This code gets timed

		benchmark::DoNotOptimize(fn());
	}
}

template <std::unsigned_integral T>
void
BM_rand_lt_one(benchmark::State& state, const std::function<T(const T)>& fn)
{
	// Perform setup here

	// a reasonable upper bound
	constexpr unsigned int upper_bound = 0x100000;

	for (auto _ : state)
	{
		// This code gets timed

		benchmark::DoNotOptimize(fn(upper_bound));
	}
}

template <std::unsigned_integral T>
void
BM_rand_lt_many(benchmark::State& state, const std::function<T(const T)>& fn)
{
	// Perform setup here

	// a reasonable maximum bound
	constexpr unsigned int max_bound = 0x100000;

	for (auto _ : state)
	{
		// This code gets timed

		// Do not test s = 0
		for (T s = 1; s <= max_bound; ++s)
		{
			benchmark::DoNotOptimize(fn(s));
		}
	}

	state.SetItemsProcessed(state.iterations() * max_bound);
}

void
BM_rand_buf(benchmark::State& state,
            const std::function<void(uint8_t*, size_t)>& fn,
            const size_t buf_size)
{
	// Perform setup here

	uint8_t* buf = new uint8_t[buf_size];

	for (auto _ : state)
	{
		// This code gets timed

		fn(buf, buf_size);
	}

	delete[] buf;

	state.SetBytesProcessed(state.iterations() * buf_size);
}

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <string>
#include <thread>

//#include <fmt/core.h>

//#define nl (void)std::putchar('\n')

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
	size_t buf_size;

	if (num_threads == 1)
	{
		prefix = "rand_uint:8b:";
		benchmark::RegisterBenchmark(prefix + "arp_u8", BM_rand_uint<uint8_t>, arp_u8);

		prefix = "rand_uint:16b:";
#if defined(__RDRND__)
		benchmark::RegisterBenchmark(prefix + "rdrand16", BM_rand_uint<uint16_t>, rdrand16);
#endif
#if defined(__RDSEED__)
		benchmark::RegisterBenchmark(prefix + "rdseed16", BM_rand_uint<uint16_t>, rdseed16);
#endif
		benchmark::RegisterBenchmark(prefix + "arp_u16", BM_rand_uint<uint16_t>, arp_u16);

		prefix = "rand_uint:32b:";
		benchmark::RegisterBenchmark(prefix + "arc4random", BM_rand_uint<uint32_t>, arc4random);
#if defined(__RDRND__)
		benchmark::RegisterBenchmark(prefix + "rdrand32", BM_rand_uint<uint32_t>, rdrand32);
#endif
#if defined(__RDSEED__)
		benchmark::RegisterBenchmark(prefix + "rdseed32", BM_rand_uint<uint32_t>, rdseed32);
#endif
		benchmark::RegisterBenchmark(prefix + "arp_u32", BM_rand_uint<uint32_t>, arp_u32);

		prefix = "rand_uint:64b:";
#if defined(__RDRND__)
		benchmark::RegisterBenchmark(prefix + "rdrand64", BM_rand_uint<uint64_t>, rdrand64);
#endif
#if defined(__RDSEED__)
		benchmark::RegisterBenchmark(prefix + "rdseed64", BM_rand_uint<uint64_t>, rdseed64);
#endif
		benchmark::RegisterBenchmark(prefix + "arp_u64", BM_rand_uint<uint64_t>, arp_u64);

		prefix = "rand_lt-one:32b:";
		benchmark::RegisterBenchmark(prefix + "arc4random_uniform", BM_rand_lt_one<uint32_t>, arc4random_uniform);
		benchmark::RegisterBenchmark(prefix + "arp_lt_u32", BM_rand_lt_one<uint32_t>, arp_lt_u32);

		prefix = "rand_lt-many:32b:";
		benchmark::RegisterBenchmark(prefix + "arc4random_uniform", BM_rand_lt_many<uint32_t>, arc4random_uniform);
		benchmark::RegisterBenchmark(prefix + "arp_lt_u32", BM_rand_lt_many<uint32_t>, arp_lt_u32);

		//for (size_t i = 16; i <= 256; i *= 2)
		for (size_t i = 1; i <= 256; i *= 2)
		{
			buf_size = i;
			prefix = "rand_buf:" + std::to_string(i) + "B:";
			benchmark::RegisterBenchmark(prefix + "getentropy", BM_rand_buf, getentropy, buf_size);
			benchmark::RegisterBenchmark(prefix + "arc4random_buf", BM_rand_buf, arc4random_buf, buf_size);
			benchmark::RegisterBenchmark(prefix + "arp_copy_to", BM_rand_buf, arp_copy_to, buf_size);
		}

		//for (size_t i = 1; i <= 8; ++i)
		for (size_t i = 1; i <= 1; ++i)
		{
			buf_size = 4096 * i;
			prefix = "rand_buf:" + std::to_string(i) + "pg:";
			benchmark::RegisterBenchmark(prefix + "arc4random_buf", BM_rand_buf, arc4random_buf, buf_size);
			benchmark::RegisterBenchmark(prefix + "arp_copy_to", BM_rand_buf, arp_copy_to, buf_size);
		}
	}
	else
	{
		prefix = "rand_uint:8b:";
		benchmark::RegisterBenchmark(prefix + "arp_u8", BM_rand_uint<uint8_t>, arp_u8)->Threads(num_threads);

		prefix = "rand_uint:16b:";
#if defined(__RDRND__)
		benchmark::RegisterBenchmark(prefix + "rdrand16", BM_rand_uint<uint16_t>, rdrand16)->Threads(num_threads);
#endif
#if defined(__RDSEED__)
		benchmark::RegisterBenchmark(prefix + "rdseed16", BM_rand_uint<uint16_t>, rdseed16)->Threads(num_threads);
#endif
		benchmark::RegisterBenchmark(prefix + "arp_u16", BM_rand_uint<uint16_t>, arp_u16)->Threads(num_threads);

		prefix = "rand_uint:32b:";
		benchmark::RegisterBenchmark(prefix + "arc4random", BM_rand_uint<uint32_t>, arc4random)->Threads(num_threads);
#if defined(__RDRND__)
		benchmark::RegisterBenchmark(prefix + "rdrand32", BM_rand_uint<uint32_t>, rdrand32)->Threads(num_threads);
#endif
#if defined(__RDSEED__)
		benchmark::RegisterBenchmark(prefix + "rdseed32", BM_rand_uint<uint32_t>, rdseed32)->Threads(num_threads);
#endif
		benchmark::RegisterBenchmark(prefix + "arp_u32", BM_rand_uint<uint32_t>, arp_u32)->Threads(num_threads);

		prefix = "rand_uint:64b:";
#if defined(__RDRND__)
		benchmark::RegisterBenchmark(prefix + "rdrand64", BM_rand_uint<uint64_t>, rdrand64)->Threads(num_threads);
#endif
#if defined(__RDSEED__)
		benchmark::RegisterBenchmark(prefix + "rdseed64", BM_rand_uint<uint64_t>, rdseed64)->Threads(num_threads);
#endif
		benchmark::RegisterBenchmark(prefix + "arp_u64", BM_rand_uint<uint64_t>, arp_u64)->Threads(num_threads);

		prefix = "rand_lt-one:32b:";
		benchmark::RegisterBenchmark(prefix + "arc4random_uniform", BM_rand_lt_one<uint32_t>, arc4random_uniform)->Threads(num_threads);
		benchmark::RegisterBenchmark(prefix + "arp_lt_u32", BM_rand_lt_one<uint32_t>, arp_lt_u32)->Threads(num_threads);

		prefix = "rand_lt-many:32b:";
		benchmark::RegisterBenchmark(prefix + "arc4random_uniform", BM_rand_lt_many<uint32_t>, arc4random_uniform)->Threads(num_threads);
		benchmark::RegisterBenchmark(prefix + "arp_lt_u32", BM_rand_lt_many<uint32_t>, arp_lt_u32)->Threads(num_threads);

		//for (size_t i = 16; i <= 256; i *= 2)
		for (size_t i = 1; i <= 256; i *= 2)
		{
			buf_size = i;
			prefix = "rand_buf:" + std::to_string(i) + "B:";
			benchmark::RegisterBenchmark(prefix + "getentropy", BM_rand_buf, getentropy, buf_size)->Threads(num_threads);
			benchmark::RegisterBenchmark(prefix + "arc4random_buf", BM_rand_buf, arc4random_buf, buf_size)->Threads(num_threads);
			benchmark::RegisterBenchmark(prefix + "arp_copy_to", BM_rand_buf, arp_copy_to, buf_size)->Threads(num_threads);
		}

		//for (size_t i = 1; i <= 8; ++i)
		for (size_t i = 1; i <= 1; ++i)
		{
			buf_size = 4096 * i;
			prefix = "rand_buf:" + std::to_string(i) + "pg:";
			benchmark::RegisterBenchmark(prefix + "arc4random_buf", BM_rand_buf, arc4random_buf, buf_size)->Threads(num_threads);
			benchmark::RegisterBenchmark(prefix + "arp_copy_to", BM_rand_buf, arp_copy_to, buf_size)->Threads(num_threads);
		}
	}

	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();

	// }}}

	return 0;
}
