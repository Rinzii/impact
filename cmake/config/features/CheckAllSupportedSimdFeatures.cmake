if (NOT DEFINED CCMATH_SOURCE_DIR)
    message(FATAL_ERROR "CCMATH_SOURCE_DIR is not defined. Did you forget to include the main CMakeLists.txt?")
endif ()

include(${CCMATH_SOURCE_DIR}/cmake/config/features/simd/CheckAVX2Support.cmake)
include(${CCMATH_SOURCE_DIR}/cmake/config/features/simd/CheckSSE2Support.cmake)
include(${CCMATH_SOURCE_DIR}/cmake/config/features/simd/CheckSSE4Support.cmake)
include(${CCMATH_SOURCE_DIR}/cmake/config/features/simd/CheckNEONSupport.cmake)

if (NOT CCMATH_DISABLE_SVML_USAGE)
  include(${CCMATH_SOURCE_DIR}/cmake/config/features/simd/CheckSVMLSupport.cmake)
endif ()

