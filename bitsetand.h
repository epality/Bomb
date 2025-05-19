#pragma once

#pragma GCC target("avx2,bmi,popcnt,fma")

#include <cstdint>
#include <immintrin.h>
#include <bitset>

void bitset_and(std::bitset<66816> &dst, const std::bitset<66816> &src1, const std::bitset<66816> &src2)
{
    const int avx2_elements = 4;
    const int num_blocks = 66816 / 64 / avx2_elements;

    for (int block = 0; block < num_blocks; ++block)
    {
        const size_t offset = block * avx2_elements;
        __m256i vec1 = _mm256_load_si256((__m256i *)(((unsigned long long *)&src1) + offset));
        __m256i vec2 = _mm256_load_si256((__m256i *)(((unsigned long long *)&src2) + offset));

        __m256i result = _mm256_and_si256(vec1, vec2);

        _mm256_store_si256((__m256i *)(((unsigned long long *)&dst) + offset), result);
    }
}
