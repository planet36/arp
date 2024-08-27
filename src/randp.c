// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// LibRandomPool (randp)
/**
\file
\author Steven Ward
Inspired by \c arc4random.
\sa https://github.com/openbsd/src/blob/master/lib/libc/crypt/arc4random.c
\sa https://man7.org/linux/man-pages/man3/arc4random.3.html
*/

#include "../randp.h"

#include "aes128_prng.h"
#include "allocate.h"
#include "nearlydivisionless.h"
#include "randp-defaults.h"

#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/user.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/// How many blocks compose the pool of random bytes
/**
* The size of each block is \c sizeof(__m128i) (i.e. \c 16).
*/
#if !defined(RANDP_NUM_BLOCKS)
#define RANDP_NUM_BLOCKS DEFAULT_RANDP_NUM_BLOCKS
#endif

static_assert(RANDP_NUM_BLOCKS >= 1, "randp must have at least 1 block");

#define RANDP_NUM_BYTES (RANDP_NUM_BLOCKS * sizeof(__m128i))

/// How many times the pool is regenerated before the PRNG is reseeded
/**
* This value is also used as the modulus to calculate a jitter.
*/
#if !defined(RANDP_RESEED_COUNTDOWN_MIN)
#define RANDP_RESEED_COUNTDOWN_MIN DEFAULT_RANDP_RESEED_COUNTDOWN_MIN
#endif

static_assert(
    __builtin_popcount(RANDP_RESEED_COUNTDOWN_MIN) == 1,
    "randp reseed countdown must be a power of 2 to prevent modulo bias");

/// A pool of random bytes
struct randp
{
	aes128_prng prng;
	size_t reseed_countdown;     // The PRNG is reseeded when this is 0.
	size_t rand_bytes_remaining; // The pool is regenerated when this is 0.
	uint8_t pool[RANDP_NUM_BYTES];
};

typedef struct randp randp;

static_assert(sizeof(randp) <= PAGE_SIZE, "randp must fit in one page");

static thread_local randp* this_ = nullptr;

static void
randp_regen()
{
	if (this_->reseed_countdown == 0)
	{
		aes128_prng_reseed(&this_->prng);
		this_->reseed_countdown = RANDP_RESEED_COUNTDOWN_MIN;
		this_->reseed_countdown +=
		    (__builtin_ia32_rdtsc() % RANDP_RESEED_COUNTDOWN_MIN) / 2;
	}

	__m128i* blocks = (__m128i*)(&this_->pool[0]);

	for (size_t i = 0; i < RANDP_NUM_BLOCKS; ++i)
	{
		blocks[i] = aes128_prng_enc_next(&this_->prng);
	}

	this_->rand_bytes_remaining = RANDP_NUM_BYTES;
	--this_->reseed_countdown;
}

void
randp_bytes(void* buf, size_t n)
{
	if (this_ == nullptr)
#ifdef __cplusplus
		this_ = (decltype(this_))allocate(sizeof(*this_));
#else
		this_ = (typeof(this_))allocate(sizeof(*this_));
#endif

	uint8_t* dst = (uint8_t*)buf;

	while (n > 0)
	{
		if (this_->rand_bytes_remaining == 0)
			randp_regen();

		uint8_t* src =
		    &this_->pool[RANDP_NUM_BYTES - this_->rand_bytes_remaining];

		const size_t m = MIN(n, this_->rand_bytes_remaining);

		(void)memcpy(dst, src, m);
#if defined(memset_explicit)
		(void)memset_explicit(src, 0, m);
#elif defined(explicit_bzero)
		explicit_bzero(src, m);
#else
		(void)memset(src, 0, m);
#endif

		dst += m;
		this_->rand_bytes_remaining -= m;
		n -= m;
	}
}

uint8_t
randp_u8()
{
	uint8_t result = 0;
	randp_bytes(&result, sizeof(result));
	return result;
}

uint16_t
randp_u16()
{
	uint16_t result = 0;
	randp_bytes(&result, sizeof(result));
	return result;
}

uint32_t
randp_u32()
{
	uint32_t result = 0;
	randp_bytes(&result, sizeof(result));
	return result;
}

uint64_t
randp_u64()
{
	uint64_t result = 0;
	randp_bytes(&result, sizeof(result));
	return result;
}

uint32_t
randp_lt_u32(uint32_t upper_bound)
{
	if (upper_bound == 0)
		return randp_u32();
	return random_bounded_nearlydivisionless32(upper_bound, randp_u32);
}

#ifdef __cplusplus
}
#endif
