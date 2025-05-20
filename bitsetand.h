#pragma once
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2,bmi,popcnt,fma")

#include <cstdint>
#include <immintrin.h>
#include <bitset>

template<unsigned long long T>
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
