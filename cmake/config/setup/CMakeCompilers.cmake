# detect the compiler
# Note: The detection order is important because:
# - Visual Studio can both use MSVC and Clang
# - GNUCXX can still be set on macOS when using Clang
if(MSVC)
    set(IMPACT_COMPILER_MSVC 1)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(IMPACT_COMPILER_CLANG_CL 1)
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(IMPACT_COMPILER_CLANG 1)
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(IMPACT_COMPILER_GCC 1)

    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION)
    string(REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" IMPACT_COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}")
else()
    message(FATAL_ERROR "Unsupported compiler")
    return()
endif()

message(STATUS "Detected Compiler: ${CMAKE_CXX_COMPILER_ID}")