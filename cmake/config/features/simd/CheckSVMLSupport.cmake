include(CheckCXXSourceCompiles)

# Try to compile a small piece of code that uses an SVML function
check_cxx_source_compiles("
        #include <immintrin.h>
        int main() {
            _mm_sin_pd(_mm_set1_pd(1.0));
            return 0;
        }
    " IMPACT_SIMD_HAS_SVML_SUPPORT)

if (IMPACT_SIMD_HAS_SVML_SUPPORT)
    add_compile_definitions(IMPACT_CONFIG_SIMD_HAS_SVML)
endif ()
