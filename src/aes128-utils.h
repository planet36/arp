// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// AES-128 utilities
/**
\file
\author Steven Ward
*/

#pragma once

#include <immintrin.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Do \c _mm_aesenc_si128 on data \a a with \a Nk keys \a keys \a Nr times for each key
/**
\pre \a Nk must be at least \c 1.
\pre \a Nr must be at least \c 1.
\param a the data
\param keys the keys
\param Nk the number of \a keys
\param Nr the number of rounds of encryption to perform for each key
*/
static __m128i
aes128_enc(__m128i a,
           const __m128i* keys,
           const unsigned int Nk,
           const unsigned int Nr)
{
	for (unsigned int k = 0; k < Nk; ++k)
	{
		for (unsigned int r = 0; r < Nr; ++r)
		{
			a = _mm_aesenc_si128(a, keys[k]);
		}
	}
	return a;
}

/// Do \c _mm_aesdec_si128 on data \a a with \a Nk keys \a keys \a Nr times for each key
/**
\pre \a Nk must be at least \c 1.
\pre \a Nr must be at least \c 1.
\param a the data
\param keys the keys
\param Nk the number of \a keys
\param Nr the number of rounds of decryption to perform for each key
*/
static __m128i
aes128_dec(__m128i a,
           const __m128i* keys,
           const unsigned int Nk,
           const unsigned int Nr)
{
	for (unsigned int k = 0; k < Nk; ++k)
	{
		for (unsigned int r = 0; r < Nr; ++r)
		{
			a = _mm_aesdec_si128(a, keys[k]);
		}
	}
	return a;
}

/// Davies-Meyer single-block-length compression function that uses AES as the block cipher
/**
\sa https://en.wikipedia.org/wiki/One-way_compression_function#Davies%E2%80%93Meyer
\pre \a Nr must be at least \c 1.
\param H the previous hash value
\param m the block of the message
\param Nr the number of rounds of encryption to perform
\return the next hash value
*/
static inline __m128i
aes128_enc_davies_meyer(const __m128i H, const __m128i m, const unsigned int Nr)
{
	return _mm_xor_si128(H, aes128_enc(H, &m, 1, Nr));
}

/// Davies-Meyer single-block-length compression function that uses AES as the block cipher
/**
\sa https://en.wikipedia.org/wiki/One-way_compression_function#Davies%E2%80%93Meyer
\pre \a Nr must be at least \c 1.
\param H the previous hash value
\param m the block of the message
\param Nr the number of rounds of decryption to perform
\return the next hash value
*/
static inline __m128i
aes128_dec_davies_meyer(const __m128i H, const __m128i m, const unsigned int Nr)
{
	return _mm_xor_si128(H, aes128_dec(H, &m, 1, Nr));
}

/// Make the packed unsigned 8-bit integers odd.
static inline __m128i
mm_make_odd_epu8(const __m128i a)
{
	return _mm_or_si128(a, _mm_set_epi8(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
}

/// Make the packed unsigned 16-bit integers odd.
static inline __m128i
mm_make_odd_epu16(const __m128i a)
{
	return _mm_or_si128(a, _mm_set_epi16(1, 1, 1, 1, 1, 1, 1, 1));
}

/// Make the packed unsigned 32-bit integers odd.
static inline __m128i
mm_make_odd_epu32(const __m128i a)
{
	return _mm_or_si128(a, _mm_set_epi32(1, 1, 1, 1));
}

/// Make the packed unsigned 64-bit integers odd.
static inline __m128i
mm_make_odd_epu64(const __m128i a)
{
	return _mm_or_si128(a, _mm_set_epi64x(1, 1));
}

#ifdef __cplusplus
}
#endif
