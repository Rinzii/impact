include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
        #include <immintrin.h>
        int main() {
            __m128d sse2_test = _mm_set1_pd(1.0);
            return 0;
        }
    " IMPACT_SIMD_HAS_SSE2_SUPPORT)

if (IMPACT_SIMD_HAS_SSE2_SUPPORT)
    add_compile_definitions(IMPACT_CONFIG_SIMD_HAS_SSE2)
endif ()
