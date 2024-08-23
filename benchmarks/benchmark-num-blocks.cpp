// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "randp.hpp"

// https://github.com/google/benchmark

#include <benchmark/benchmark.h>
#include <concepts>
#include <functional>

void
BM_rand_buf_1GiB(benchmark::State& state,
                 const std::function<void(uint8_t*, size_t)>& fn)
{
	// Perform setup here

	uint8_t buf[1U << 8];

	for (auto _ : state)
	{
		// This code gets timed

		// (2**30) / (2**8) == 2**22
		for (size_t i = 0; i < (1U << 22); ++i)
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
		prefix = "rand_buf_1GiB:";
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x01,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x01,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x02,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x02,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x03,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x03,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x04,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x04,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x05,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x05,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x06,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x06,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x07,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x07,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x08,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x08,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x09,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x09,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0a,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0b,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0c,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0d,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0e,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0f,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x10,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x11,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x11,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x12,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x12,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x13,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x13,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x14,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x14,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x15,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x15,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x16,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x16,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x17,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x17,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x18,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x18,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x19,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x19,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1a,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1b,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1c,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1d,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1e,1U << 31>)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1f,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x20,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x20,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x21,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x21,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x22,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x22,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x23,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x23,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x24,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x24,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x25,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x25,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x26,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x26,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x27,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x27,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x28,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x28,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x29,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x29,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2a,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2b,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2c,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2d,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2e,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2f,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x30,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x30,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x31,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x31,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x32,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x32,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x33,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x33,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x34,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x34,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x35,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x35,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x36,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x36,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x37,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x37,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x38,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x38,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x39,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x39,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3a,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3b,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3c,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3d,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3e,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3f,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x40,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x40,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x41,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x41,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x42,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x42,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x43,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x43,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x44,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x44,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x45,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x45,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x46,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x46,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x47,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x47,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x48,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x48,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x49,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x49,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4a,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4b,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4c,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4d,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4e,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4f,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x50,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x50,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x51,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x51,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x52,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x52,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x53,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x53,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x54,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x54,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x55,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x55,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x56,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x56,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x57,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x57,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x58,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x58,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x59,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x59,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5a,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5b,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5c,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5d,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5e,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5f,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x60,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x60,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x61,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x61,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x62,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x62,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x63,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x63,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x64,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x64,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x65,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x65,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x66,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x66,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x67,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x67,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x68,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x68,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x69,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x69,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6a,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6b,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6c,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6d,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6e,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6f,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x70,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x70,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x71,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x71,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x72,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x72,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x73,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x73,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x74,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x74,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x75,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x75,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x76,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x76,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x77,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x77,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x78,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x78,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x79,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x79,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7a,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7b,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7c,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7d,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7e,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7f,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x80,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x80,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x81,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x81,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x82,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x82,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x83,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x83,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x84,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x84,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x85,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x85,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x86,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x86,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x87,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x87,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x88,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x88,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x89,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x89,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8a,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8b,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8c,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8d,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8e,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8f,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x90,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x90,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x91,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x91,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x92,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x92,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x93,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x93,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x94,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x94,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x95,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x95,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x96,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x96,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x97,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x97,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x98,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x98,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x99,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x99,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9a,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9b,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9c,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9d,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9e,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9f,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa0,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa1,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa2,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa3,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa4,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa5,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa6,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa7,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa8,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa9,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xaa,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xaa,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xab,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xab,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xac,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xac,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xad,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xad,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xae,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xae,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xaf,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xaf,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb0,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb1,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb2,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb3,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb4,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb5,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb6,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb7,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb8,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb9,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xba,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xba,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbb,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbc,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbc,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbd,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbd,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbe,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbe,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbf,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbf,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc0,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc1,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc2,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc3,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc4,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc5,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc6,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc7,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc8,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc9,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xca,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xca,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xcb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xcb,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xcc,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xcc,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xcd,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xcd,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xce,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xce,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xcf,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xcf,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd0,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd1,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd2,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd3,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd4,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd5,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd6,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd7,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd8,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd9,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xda,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xda,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xdb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xdb,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xdc,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xdc,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xdd,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xdd,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xde,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xde,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xdf,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xdf,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe0,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe1,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe2,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe3,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe4,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe5,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe6,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe7,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe8,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe9,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xea,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xea,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xeb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xeb,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xec,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xec,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xed,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xed,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xee,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xee,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xef,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xef,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf0,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf1,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf2,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf3,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf4,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf5,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf6,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf7,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf8,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf9,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xfa,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xfa,1U << 31>)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xfb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xfb,1U << 31>)->Unit(benchmark::kMillisecond);
	}
	else
	{
		prefix = "rand_buf_1GiB:";
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x01,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x01,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x02,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x02,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x03,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x03,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x04,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x04,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x05,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x05,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x06,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x06,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x07,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x07,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x08,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x08,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x09,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x09,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x0f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x0f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x10,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x10,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x11,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x11,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x12,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x12,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x13,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x13,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x14,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x14,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x15,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x15,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x16,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x16,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x17,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x17,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x18,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x18,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x19,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x19,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		benchmark::RegisterBenchmark(prefix + "randp_bytes<0x1f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x1f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x20,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x20,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x21,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x21,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x22,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x22,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x23,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x23,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x24,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x24,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x25,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x25,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x26,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x26,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x27,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x27,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x28,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x28,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x29,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x29,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x2f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x2f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x30,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x30,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x31,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x31,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x32,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x32,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x33,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x33,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x34,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x34,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x35,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x35,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x36,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x36,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x37,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x37,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x38,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x38,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x39,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x39,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x3f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x3f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x40,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x40,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x41,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x41,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x42,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x42,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x43,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x43,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x44,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x44,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x45,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x45,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x46,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x46,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x47,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x47,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x48,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x48,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x49,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x49,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x4f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x4f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x50,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x50,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x51,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x51,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x52,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x52,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x53,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x53,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x54,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x54,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x55,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x55,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x56,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x56,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x57,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x57,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x58,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x58,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x59,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x59,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x5f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x5f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x60,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x60,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x61,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x61,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x62,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x62,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x63,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x63,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x64,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x64,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x65,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x65,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x66,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x66,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x67,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x67,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x68,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x68,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x69,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x69,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x6f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x6f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x70,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x70,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x71,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x71,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x72,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x72,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x73,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x73,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x74,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x74,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x75,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x75,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x76,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x76,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x77,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x77,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x78,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x78,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x79,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x79,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x7f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x7f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x80,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x80,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x81,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x81,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x82,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x82,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x83,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x83,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x84,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x84,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x85,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x85,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x86,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x86,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x87,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x87,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x88,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x88,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x89,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x89,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x8f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x8f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x90,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x90,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x91,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x91,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x92,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x92,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x93,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x93,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x94,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x94,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x95,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x95,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x96,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x96,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x97,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x97,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x98,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x98,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x99,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x99,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9a,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9a,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9b,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9b,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9c,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9c,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9d,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9d,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9e,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9e,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0x9f,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0x9f,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa0,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa1,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa2,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa3,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa4,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa5,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa6,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa7,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa8,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xa9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xa9,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xaa,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xaa,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xab,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xab,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xac,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xac,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xad,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xad,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xae,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xae,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xaf,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xaf,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb0,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb1,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb2,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb3,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb4,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb5,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb6,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb7,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb8,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xb9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xb9,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xba,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xba,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbb,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbc,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbc,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbd,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbd,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbe,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbe,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xbf,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xbf,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc0,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc1,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc2,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc3,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc4,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc5,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc6,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc7,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc8,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xc9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xc9,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xca,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xca,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xcb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xcb,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xcc,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xcc,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xcd,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xcd,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xce,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xce,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xcf,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xcf,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd0,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd1,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd2,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd3,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd4,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd5,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd6,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd7,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd8,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xd9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xd9,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xda,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xda,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xdb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xdb,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xdc,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xdc,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xdd,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xdd,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xde,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xde,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xdf,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xdf,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe0,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe1,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe2,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe3,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe4,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe5,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe6,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe7,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe8,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xe9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xe9,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xea,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xea,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xeb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xeb,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xec,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xec,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xed,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xed,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xee,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xee,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xef,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xef,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf0,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf0,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf1,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf1,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf2,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf2,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf3,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf3,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf4,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf4,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf5,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf5,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf6,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf6,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf7,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf7,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf8,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf8,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xf9,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xf9,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xfa,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xfa,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
		//benchmark::RegisterBenchmark(prefix + "randp_bytes<0xfb,1U<<31>", BM_rand_buf_1GiB, randp_bytes<0xfb,1U << 31>)->Threads(num_threads)->Unit(benchmark::kMillisecond);
	}

	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();

	// }}}

	return 0;
}
