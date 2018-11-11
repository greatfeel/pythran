/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XSIMD_AVX_INT32_HPP
#define XSIMD_AVX_INT32_HPP

#include <cstdint>

#include "xsimd_base.hpp"
#include "xsimd_avx_int_base.hpp"
#include "xsimd_int_conversion.hpp"

namespace xsimd
{

    /**************************
     * batch_bool<int32_t, 8> *
     **************************/

    template <>
    struct simd_batch_traits<batch_bool<int32_t, 8>>
    {
        using value_type = int32_t;
        static constexpr std::size_t size = 8;
        using batch_type = batch<int32_t, 8>;
        static constexpr std::size_t align = 32;
    };

    template <>
    struct simd_batch_traits<batch_bool<uint32_t, 8>>
    {
        using value_type = uint32_t;
        static constexpr std::size_t size = 8;
        using batch_type = batch<uint32_t, 8>;
        static constexpr std::size_t align = 32;
    };

    template <>
    class batch_bool<int32_t, 8> : public avx_int_batch_bool<int32_t, 8>
    {
    public:
        using avx_int_batch_bool::avx_int_batch_bool;
    };

    template <>
    class batch_bool<uint32_t, 8> : public avx_int_batch_bool<uint32_t, 8>
    {
    public:
        using avx_int_batch_bool::avx_int_batch_bool;
    };

    namespace detail
    {
        template <>
        struct batch_bool_kernel<int32_t, 8> : public avx_int_batch_bool_kernel<int32_t, 8>
        {
        };

        template <>
        struct batch_bool_kernel<uint32_t, 8> : public avx_int_batch_bool_kernel<uint32_t, 8>
        {
        };
    }

    /*********************
     * batch<int32_t, 8> *
     *********************/

    template <>
    struct simd_batch_traits<batch<int32_t, 8>>
    {
        using value_type = int32_t;
        static constexpr std::size_t size = 8;
        using batch_bool_type = batch_bool<int32_t, 8>;
        static constexpr std::size_t align = 32;
    };

    template <>
    struct simd_batch_traits<batch<uint32_t, 8>>
    {
        using value_type = uint32_t;
        static constexpr std::size_t size = 8;
        using batch_bool_type = batch_bool<uint32_t, 8>;
        static constexpr std::size_t align = 32;
    };

    template <>
    class batch<int32_t, 8> : public avx_int_batch<int32_t, 8>
    {
    public:

        using base_type = avx_int_batch<int32_t, 8>;
        using base_type::base_type;
        using base_type::load_aligned;
        using base_type::load_unaligned;
        using base_type::store_aligned;
        using base_type::store_unaligned;

        XSIMD_DECLARE_LOAD_STORE_INT32(int32_t, 8);
        XSIMD_DECLARE_LOAD_STORE_LONG(int32_t, 8);
   };

    batch<int32_t, 8> operator<<(const batch<int32_t, 8>& lhs, int32_t rhs);
    batch<int32_t, 8> operator>>(const batch<int32_t, 8>& lhs, int32_t rhs);

    template <>
    class batch<uint32_t, 8> : public avx_int_batch<uint32_t, 8>
    {
    public:

        using base_type = avx_int_batch<uint32_t, 8>;
        using base_type::base_type;
        using base_type::load_aligned;
        using base_type::load_unaligned;
        using base_type::store_aligned;
        using base_type::store_unaligned;

        XSIMD_DECLARE_LOAD_STORE_INT32(uint32_t, 8);
        XSIMD_DECLARE_LOAD_STORE_LONG(uint32_t, 8);
    };

    batch<uint32_t, 8> operator<<(const batch<uint32_t, 8>& lhs, int32_t rhs);
    batch<uint32_t, 8> operator>>(const batch<uint32_t, 8>& lhs, int32_t rhs);

    /************************************
     * batch<int32_t, 8> implementation *
     ************************************/

    namespace avx_detail
    {
        inline __m256i load_aligned_int32(const int8_t* src)
        {
            __m128i tmp = _mm_loadl_epi64((const __m128i*)src);
            return detail::xsimd_cvtepi8_epi32(tmp);
        }

        inline __m256i load_unaligned_int32(const int8_t* src)
        {
            return load_aligned_int32(src);
        }

        inline __m256i load_aligned_int32(const uint8_t* src)
        {
            __m128i tmp = _mm_loadl_epi64((const __m128i*)src);
            return detail::xsimd_cvtepu8_epi32(tmp);
        }

        inline __m256i load_unaligned_int32(const uint8_t* src)
        {
            return load_aligned_int32(src);
        }

        inline __m256i load_aligned_int32(const int16_t* src)
        {
            __m128i tmp = _mm_load_si128((__m128i const*)src);
            return detail::xsimd_cvtepi16_epi32(tmp);
        }

        inline __m256i load_unaligned_int32(const int16_t* src)
        {
            __m128i tmp = _mm_loadu_si128((__m128i const*)src);
            return detail::xsimd_cvtepi16_epi32(tmp);
        }

        inline __m256i load_aligned_int32(const uint16_t* src)
        {
            __m128i tmp = _mm_load_si128((__m128i const*)src);
            return detail::xsimd_cvtepu16_epi32(tmp);
        }

        inline __m256i load_unaligned_int32(const uint16_t* src)
        {
            __m128i tmp = _mm_loadu_si128((__m128i const*)src);
            return detail::xsimd_cvtepu16_epi32(tmp);
        }

        inline void store_aligned_int32(__m256i src, int8_t* dst)
        {
            __m128i tmp = detail::xsimd_cvtepi32_epi8(src);
            _mm_storel_epi64((__m128i*)dst, tmp);
        }

        inline void store_unaligned_int32(__m256i src, int8_t* dst)
        {
            store_aligned_int32(src, dst);
        }

        inline void store_aligned_int32(__m256i src, uint8_t* dst)
        {
            __m128i tmp = detail::xsimd_cvtepi32_epu8(src);
            _mm_storel_epi64((__m128i*)dst, tmp);
        }

        inline void store_unaligned_int32(__m256i src, uint8_t* dst)
        {
            store_aligned_int32(src, dst);
        }

        inline void store_aligned_int32(__m256i src, int16_t* dst)
        {
            __m128i tmp = detail::xsimd_cvtepi32_epi16(src);
            _mm_store_si128((__m128i*)dst, tmp);
        }

        inline void store_unaligned_int32(__m256i src, int16_t* dst)
        {
            __m128i tmp = detail::xsimd_cvtepi32_epi16(src);
            _mm_storeu_si128((__m128i*)dst, tmp);
        }

        inline void store_aligned_int32(__m256i src, uint16_t* dst)
        {
            __m128i tmp = detail::xsimd_cvtepi32_epu16(src);
            _mm_store_si128((__m128i*)dst, tmp);
        }

        inline void store_unaligned_int32(__m256i src, uint16_t* dst)
        {
            __m128i tmp = detail::xsimd_cvtepi32_epu16(src);
            _mm_storeu_si128((__m128i*)dst, tmp);
        }
    }

#define AVX_DEFINE_LOAD_STORE_INT32(TYPE, CVT_TYPE)                            \
    inline batch<TYPE, 8>& batch<TYPE, 8>::load_aligned(const CVT_TYPE* src)   \
    {                                                                          \
        this->m_value = avx_detail::load_aligned_int32(src);                   \
        return *this;                                                          \
    }                                                                          \
    inline batch<TYPE, 8>& batch<TYPE, 8>::load_unaligned(const CVT_TYPE* src) \
    {                                                                          \
        this->m_value = avx_detail::load_unaligned_int32(src);                 \
        return *this;                                                          \
    }                                                                          \
    inline void batch<TYPE, 8>::store_aligned(CVT_TYPE* dst) const             \
    {                                                                          \
        avx_detail::store_aligned_int32(this->m_value, dst);                   \
    }                                                                          \
    inline void batch<TYPE, 8>::store_unaligned(CVT_TYPE* dst) const           \
    {                                                                          \
        avx_detail::store_unaligned_int32(this->m_value, dst);                 \
    }

    AVX_DEFINE_LOAD_STORE_INT32(int32_t, int8_t)
    AVX_DEFINE_LOAD_STORE_INT32(int32_t, uint8_t)
    AVX_DEFINE_LOAD_STORE_INT32(int32_t, int16_t)
    AVX_DEFINE_LOAD_STORE_INT32(int32_t, uint16_t)
    XSIMD_DEFINE_LOAD_STORE_LONG(int32_t, 8, 32)
    XSIMD_DEFINE_LOAD_STORE(int32_t, 8, int64_t, 32)
    XSIMD_DEFINE_LOAD_STORE(int32_t, 8, uint64_t, 32)

    inline batch<int32_t, 8>& batch<int32_t, 8>::load_aligned(const float* src)
    {
        m_value = _mm256_cvtps_epi32(_mm256_load_ps(src));
        return *this;
    }

    inline batch<int32_t, 8>& batch<int32_t, 8>::load_unaligned(const float* src)
    {
        m_value = _mm256_cvtps_epi32(_mm256_loadu_ps(src));
        return *this;
    }

    inline batch<int32_t, 8>& batch<int32_t, 8>::load_aligned(const double* src)
    {
        __m128i tmp1 = _mm256_cvtpd_epi32(_mm256_load_pd(src));
        __m128i tmp2 = _mm256_cvtpd_epi32(_mm256_load_pd(src + 4));
        m_value = _mm256_castsi128_si256(tmp1);
        m_value = _mm256_insertf128_si256(m_value, tmp2, 1);
        return *this;
    }

    inline batch<int32_t, 8>& batch<int32_t, 8>::load_unaligned(const double* src)
    {
        __m128i tmp1 = _mm256_cvtpd_epi32(_mm256_loadu_pd(src));
        __m128i tmp2 = _mm256_cvtpd_epi32(_mm256_loadu_pd(src + 4));
        m_value = _mm256_castsi128_si256(tmp1);
        m_value = _mm256_insertf128_si256(m_value, tmp2, 1);
        return *this;
    }

    inline void batch<int32_t, 8>::store_aligned(float* dst) const
    {
        _mm256_store_ps(dst, _mm256_cvtepi32_ps(m_value));
    }

    inline void batch<int32_t, 8>::store_unaligned(float* dst) const
    {
        _mm256_storeu_ps(dst, _mm256_cvtepi32_ps(m_value));
    }

    inline void batch<int32_t, 8>::store_aligned(double* dst) const
    {
        __m128i tmp1 = _mm256_extractf128_si256(m_value, 0);
        __m128i tmp2 = _mm256_extractf128_si256(m_value, 1);
        _mm256_store_pd(dst, _mm256_cvtepi32_pd(tmp1));
        _mm256_store_pd(dst + 4 , _mm256_cvtepi32_pd(tmp2));
    }

    inline void batch<int32_t, 8>::store_unaligned(double* dst) const
    {
        __m128i tmp1 = _mm256_extractf128_si256(m_value, 0);
        __m128i tmp2 = _mm256_extractf128_si256(m_value, 1);
        _mm256_storeu_pd(dst, _mm256_cvtepi32_pd(tmp1));
        _mm256_storeu_pd(dst + 4, _mm256_cvtepi32_pd(tmp2));
    }

    AVX_DEFINE_LOAD_STORE_INT32(uint32_t, int8_t)
    AVX_DEFINE_LOAD_STORE_INT32(uint32_t, uint8_t)
    AVX_DEFINE_LOAD_STORE_INT32(uint32_t, int16_t)
    AVX_DEFINE_LOAD_STORE_INT32(uint32_t, uint16_t)
    XSIMD_DEFINE_LOAD_STORE_LONG(uint32_t, 8, 32)
    XSIMD_DEFINE_LOAD_STORE(uint32_t, 8, int64_t, 32)
    XSIMD_DEFINE_LOAD_STORE(uint32_t, 8, uint64_t, 32)
    XSIMD_DEFINE_LOAD_STORE(uint32_t, 8, float, 32)
    XSIMD_DEFINE_LOAD_STORE(uint32_t, 8, double, 32)

#undef AVX_DEFINE_LOAD_STORE_INT32

    namespace detail
    {
        template <>
        struct batch_kernel<int32_t, 8>
            : avx_int_kernel_base<batch<int32_t, 8>>
        {
            using batch_type = batch<int32_t, 8>;
            using value_type = int32_t;
            using batch_bool_type = batch_bool<int32_t, 8>;

            static batch_type neg(const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_sub_epi32(_mm256_setzero_si256(), rhs);
#else
                XSIMD_SPLIT_AVX(rhs);
                __m128i res_low = _mm_sub_epi32(_mm_setzero_si128(), rhs_low);
                __m128i res_high = _mm_sub_epi32(_mm_setzero_si128(), rhs_high);
                XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
            }

            static batch_type add(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_add_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_add_epi32, lhs, rhs);
#endif
            }

            static batch_type sub(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_sub_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_sub_epi32, lhs, rhs);
#endif
            }

            static batch_type mul(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_mullo_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_mullo_epi32, lhs, rhs);
#endif
            }

            static batch_type div(const batch_type& lhs, const batch_type& rhs)
            {
#if defined(XSIMD_FAST_INTEGER_DIVISION)
                return _mm256_cvttps_epi32(_mm256_div_ps(_mm256_cvtepi32_ps(lhs), _mm256_cvtepi32_ps(rhs)));
#else
                alignas(64) int32_t tmp_lhs[8], tmp_rhs[8], tmp_res[8];
                lhs.store_aligned(tmp_lhs);
                rhs.store_aligned(tmp_rhs);
                unroller<8>([&](std::size_t i) {
                    tmp_res[i] = tmp_lhs[i] / tmp_rhs[i];
                });
                return batch_type(tmp_res, aligned_mode());
#endif
            }

            static batch_type mod(const batch_type& lhs, const batch_type& rhs)
            {
                alignas(64) int32_t tmp_lhs[8], tmp_rhs[8], tmp_res[8];
                lhs.store_aligned(tmp_lhs);
                rhs.store_aligned(tmp_rhs);
                unroller<8>([&](std::size_t i) {
                    tmp_res[i] = tmp_lhs[i] % tmp_rhs[i];
                });
                return batch_type(tmp_res, aligned_mode());
            }

            static batch_bool_type eq(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_cmpeq_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_cmpeq_epi32, lhs, rhs);
#endif
            }

            static batch_bool_type lt(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_cmpgt_epi32(rhs, lhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_cmpgt_epi32, rhs, lhs);
#endif
            }

            static batch_type min(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_min_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_min_epi32, lhs, rhs);
#endif
            }

            static batch_type max(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_max_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_max_epi32, lhs, rhs);
#endif
            }

            static batch_type abs(const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_sign_epi32(rhs, rhs);
#else
                XSIMD_SPLIT_AVX(rhs);
                __m128i res_low = _mm_sign_epi32(rhs_low, rhs_low);
                __m128i res_high = _mm_sign_epi32(rhs_high, rhs_high);
                XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
            }

            static value_type hadd(const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                __m256i tmp1 = _mm256_hadd_epi32(rhs, rhs);
                __m256i tmp2 = _mm256_hadd_epi32(tmp1, tmp1);
                __m128i tmp3 = _mm256_extracti128_si256(tmp2, 1);
                __m128i tmp4 = _mm_add_epi32(_mm256_castsi256_si128(tmp2), tmp3);
                return _mm_cvtsi128_si32(tmp4);
#else
                XSIMD_SPLIT_AVX(rhs);
                __m128i tmp1 = _mm_add_epi32(rhs_low, rhs_high);
                __m128i tmp2 = _mm_hadd_epi32(tmp1, tmp1);
                __m128i tmp3 = _mm_hadd_epi32(tmp2, tmp2);
                return _mm_cvtsi128_si32(tmp3);
#endif
            }

            static batch_type select(const batch_bool_type& cond, const batch_type& a, const batch_type& b)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_blendv_epi8(b, a, cond);
#else
                XSIMD_SPLIT_AVX(cond);
                XSIMD_SPLIT_AVX(a);
                XSIMD_SPLIT_AVX(b);
                __m128i res_low = _mm_blendv_epi8(b_low, a_low, cond_low);
                __m128i res_high = _mm_blendv_epi8(b_high, a_high, cond_high);
                XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
            }
        };

        template <>
        struct batch_kernel<uint32_t, 8>
            : avx_int_kernel_base<batch<uint32_t, 8>>
        {
            using batch_type = batch<uint32_t, 8>;
            using value_type = uint32_t;
            using batch_bool_type = batch_bool<uint32_t, 8>;

            static batch_type neg(const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_sub_epi32(_mm256_setzero_si256(), rhs);
#else
                XSIMD_SPLIT_AVX(rhs);
                __m128i res_low = _mm_sub_epi32(_mm_setzero_si128(), rhs_low);
                __m128i res_high = _mm_sub_epi32(_mm_setzero_si128(), rhs_high);
                XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
            }

            static batch_type add(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_add_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_add_epi32, lhs, rhs);
#endif
            }

            static batch_type sub(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_sub_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_sub_epi32, lhs, rhs);
#endif
            }

            static batch_type mul(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_mullo_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_mullo_epi32, lhs, rhs);
#endif
            }

            static batch_type div(const batch_type& lhs, const batch_type& rhs)
            {
#if defined(XSIMD_FAST_INTEGER_DIVISION)
                return _mm256_cvttps_epi32(_mm256_div_ps(_mm256_cvtepi32_ps(lhs), _mm256_cvtepi32_ps(rhs)));
#else
                alignas(64) uint32_t tmp_lhs[8], tmp_rhs[8], tmp_res[8];
                lhs.store_aligned(tmp_lhs);
                rhs.store_aligned(tmp_rhs);
                unroller<8>([&](std::size_t i) {
                    tmp_res[i] = tmp_lhs[i] / tmp_rhs[i];
                });
                return batch_type(tmp_res, aligned_mode());
#endif
            }

            static batch_type mod(const batch_type& lhs, const batch_type& rhs)
            {
                alignas(64) uint32_t tmp_lhs[8], tmp_rhs[8], tmp_res[8];
                lhs.store_aligned(tmp_lhs);
                rhs.store_aligned(tmp_rhs);
                unroller<8>([&](std::size_t i) {
                    tmp_res[i] = tmp_lhs[i] % tmp_rhs[i];
                });
                return batch_type(tmp_res, aligned_mode());
            }

            static batch_bool_type eq(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_cmpeq_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_cmpeq_epi32, lhs, rhs);
#endif
            }

            static batch_bool_type lt(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_cmpgt_epi32(rhs, lhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_cmpgt_epi32, rhs, lhs);
#endif
            }

            static batch_type min(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_min_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_min_epi32, lhs, rhs);
#endif
            }

            static batch_type max(const batch_type& lhs, const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_max_epi32(lhs, rhs);
#else
                XSIMD_APPLY_SSE_FUNCTION(_mm_max_epi32, lhs, rhs);
#endif
            }

            static batch_type abs(const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_sign_epi32(rhs, rhs);
#else
                XSIMD_SPLIT_AVX(rhs);
                __m128i res_low = _mm_sign_epi32(rhs_low, rhs_low);
                __m128i res_high = _mm_sign_epi32(rhs_high, rhs_high);
                XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
            }

            static value_type hadd(const batch_type& rhs)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                __m256i tmp1 = _mm256_hadd_epi32(rhs, rhs);
                __m256i tmp2 = _mm256_hadd_epi32(tmp1, tmp1);
                __m128i tmp3 = _mm256_extracti128_si256(tmp2, 1);
                __m128i tmp4 = _mm_add_epi32(_mm256_castsi256_si128(tmp2), tmp3);
                return _mm_cvtsi128_si32(tmp4);
#else
                XSIMD_SPLIT_AVX(rhs);
                __m128i tmp1 = _mm_add_epi32(rhs_low, rhs_high);
                __m128i tmp2 = _mm_hadd_epi32(tmp1, tmp1);
                __m128i tmp3 = _mm_hadd_epi32(tmp2, tmp2);
                return _mm_cvtsi128_si32(tmp3);
#endif
            }

            static batch_type select(const batch_bool_type& cond, const batch_type& a, const batch_type& b)
            {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
                return _mm256_blendv_epi8(b, a, cond);
#else
                XSIMD_SPLIT_AVX(cond);
                XSIMD_SPLIT_AVX(a);
                XSIMD_SPLIT_AVX(b);
                __m128i res_low = _mm_blendv_epi8(b_low, a_low, cond_low);
                __m128i res_high = _mm_blendv_epi8(b_high, a_high, cond_high);
                XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
            }
        };
    }

    inline batch<int32_t, 8> operator<<(const batch<int32_t, 8>& lhs, int32_t rhs)
    {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
        return _mm256_slli_epi32(lhs, rhs);
#else
        XSIMD_SPLIT_AVX(lhs);
        __m128i res_low = _mm_slli_epi32(lhs_low, rhs);
        __m128i res_high = _mm_slli_epi32(lhs_high, rhs);
        XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
    }

    inline batch<int32_t, 8> operator>>(const batch<int32_t, 8>& lhs, int32_t rhs)
    {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
        return _mm256_srli_epi32(lhs, rhs);
#else
        XSIMD_SPLIT_AVX(lhs);
        __m128i res_low = _mm_srli_epi32(lhs_low, rhs);
        __m128i res_high = _mm_srli_epi32(lhs_high, rhs);
        XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
    }

    inline batch<uint32_t, 8> operator<<(const batch<uint32_t, 8>& lhs, int32_t rhs)
    {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
        return _mm256_slli_epi32(lhs, rhs);
#else
        XSIMD_SPLIT_AVX(lhs);
        __m128i res_low = _mm_slli_epi32(lhs_low, rhs);
        __m128i res_high = _mm_slli_epi32(lhs_high, rhs);
        XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
    }

    inline batch<uint32_t, 8> operator>>(const batch<uint32_t, 8>& lhs, int32_t rhs)
    {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX2_VERSION
        return _mm256_srli_epi32(lhs, rhs);
#else
        XSIMD_SPLIT_AVX(lhs);
        __m128i res_low = _mm_srli_epi32(lhs_low, rhs);
        __m128i res_high = _mm_srli_epi32(lhs_high, rhs);
        XSIMD_RETURN_MERGED_SSE(res_low, res_high);
#endif
    }
}

#endif