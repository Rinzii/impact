include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
        #include <arm_neon.h>
        int main() {
            int32x4_t neon_test = vdupq_n_s32(1);
            return 0;
        }
    " IMPACT_SIMD_HAS_NEON_SUPPORT)

if (IMPACT_SIMD_HAS_NEON_SUPPORT)
    add_compile_definitions(IMPACT_CONFIG_SIMD_HAS_NEON)
endif ()
