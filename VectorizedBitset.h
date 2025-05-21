#pragma once
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2,bmi,popcnt,fma")

#include <cstdint>
#include <immintrin.h>
#include <bitset>

template <size_t T>
void bitset_and(std::bitset<T> &dst, const std::bitset<T> &src1, const std::bitset<T> &src2)
{
    static_assert(T % 256 == 0, "T must be a multiple of 256");
    const int avx2_elements = 4;
    const int num_blocks = T / 64 / avx2_elements;

    for (int block = 0; block < num_blocks; ++block)
    {
        const size_t offset = block * avx2_elements;
        __m256i vec1 = _mm256_loadu_si256((__m256i *)(((unsigned long long *)&src1) + offset));
        __m256i vec2 = _mm256_loadu_si256((__m256i *)(((unsigned long long *)&src2) + offset));

        __m256i result = _mm256_and_si256(vec1, vec2);

        _mm256_storeu_si256((__m256i *)(((unsigned long long *)&dst) + offset), result);
    }
}

template <size_t T>
int bitset_count(const std::bitset<T> &src)
{
    static_assert(T % 256 == 0, "T must be a multiple of 256");

    const __m256i lookup = _mm256_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
    const __m256i low_mask = _mm256_set1_epi8(0x0f);

    __m256i t = _mm256_setzero_si256();

    int k = 0;

    for (k = 0; k + 15 < T / 32; k += 16)
    {
        __m256i s = _mm256_setzero_si256();

        for (int i = 0; i < 15; i += 8)
        {
            __m256i x = _mm256_loadu_si256((__m256i *)(((int *)&src) + k + i));

            __m256i l = _mm256_and_si256(x, low_mask);
            __m256i h = _mm256_and_si256(_mm256_srli_epi16(x, 4), low_mask);

            __m256i pl = _mm256_shuffle_epi8(lookup, l);
            __m256i ph = _mm256_shuffle_epi8(lookup, h);

            s = _mm256_add_epi8(s, pl);
            s = _mm256_add_epi8(s, ph);
        }

        t = _mm256_add_epi64(t, _mm256_sad_epu8(s, _mm256_setzero_si256()));
    }

    int res = 0;

    for (; k + 1 < T / 32; k += 2)
        res += __builtin_popcountll(*((long long *)(((int *)&src) + k)));

    __m128i l = _mm256_extracti128_si256(t, 0);
    __m128i h = _mm256_extracti128_si256(t, 1);
    l = _mm_add_epi32(l, h);
    l = _mm_hadd_epi32(l, l);
    return _mm_extract_epi32(l, 0) + _mm_extract_epi32(l, 1) + res;
}

template <size_t T>
int bitset_and_count(const std::bitset<T> &src1, const std::bitset<T> &src2)
{
    static_assert(T % 256 == 0, "T must be a multiple of 256");

    const __m256i lookup = _mm256_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
    const __m256i low_mask = _mm256_set1_epi8(0x0f);

    __m256i t = _mm256_setzero_si256();

    int k = 0;

    for (k = 0; k + 15 < T / 32; k += 16)
    {
        __m256i s = _mm256_setzero_si256();

        for (int i = 0; i < 15; i += 8)
        {
            __m256i x = _mm256_loadu_si256((__m256i *)(((int *)&src1) + k + i));
            __m256i x1 = _mm256_loadu_si256((__m256i *)(((int *)&src2) + k + i));

            x = _mm256_and_si256(x, x1);

            __m256i l = _mm256_and_si256(x, low_mask);
            __m256i h = _mm256_and_si256(_mm256_srli_epi16(x, 4), low_mask);

            __m256i pl = _mm256_shuffle_epi8(lookup, l);
            __m256i ph = _mm256_shuffle_epi8(lookup, h);

            s = _mm256_add_epi8(s, pl);
            s = _mm256_add_epi8(s, ph);
        }

        t = _mm256_add_epi64(t, _mm256_sad_epu8(s, _mm256_setzero_si256()));
    }

    int res = 0;

    for (; k + 1 < T / 32; k += 2)
        res += __builtin_popcountll((*((long long *)(((int *)&src1) + k))) & (*((long long *)(((int *)&src2) + k))));

    __m128i l = _mm256_extracti128_si256(t, 0);
    __m128i h = _mm256_extracti128_si256(t, 1);
    l = _mm_add_epi32(l, h);
    l = _mm_hadd_epi32(l, l);
    return _mm_extract_epi32(l, 0) + _mm_extract_epi32(l, 1) + res;
}