project(impact-ext)

find_package(Threads)

include(FetchContent)

FetchContent_Declare(
        WinLite
        GIT_REPOSITORY https://github.com/Rinzii/WinLite.git
        GIT_TAG  main
)
FetchContent_MakeAvailable(WinLite)
add_library(Win::Lite ALIAS WinLite)

FetchContent_Declare(
        ccmath
        GIT_REPOSITORY https://github.com/Rinzii/ccmath.git
        GIT_TAG main
)
FetchContent_MakeAvailable(ccmath)

set (GLM_ENABLE_CXX_20 ON)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG  1.0.1
)
FetchContent_MakeAvailable(glm)

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    target_compile_options(glm INTERFACE -Wno-volatile)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    target_compile_options(glm INTERFACE -Wno-deprecated-volatile)
endif()


# TODO: Add ImGUI to libs

add_library(impact-ext INTERFACE)
add_library(impact::ext ALIAS impact-ext)

target_link_libraries(impact-ext INTERFACE
        ccmath::ccmath
        Win::Lite
        glm::glm

        Threads::Threads
)

target_compile_definitions(glm INTERFACE
        GLM_FORCE_XYZW_ONLY
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        GLM_FORCE_SILENT_WARNINGS
        GLM_ENABLE_EXPERIMENTAL
        GLM_EXT_INCLUDED
)