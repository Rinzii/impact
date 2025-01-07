mark_as_advanced(CMAKE_TOOLCHAIN_FILE)

# TODO: Finish PS5 toolchain file
# TODO: Research how to get PS5 SDK path
# TODO: Validate all this information is correct some how

if (_PS5_PROSPERO_TOOLCHAIN_)
    return()
endif ()

# PS5 SCE version requirement
set(REQUIRED_PS5_VERSION "5.000")

# Get PS4 SCE environment
if (EXISTS "$ENV{SCE_ROOT_DIR}" AND IS_DIRECTORY "$ENV{SCE_ROOT_DIR}")
    string(REGEX REPLACE "\\\\" "/" PS5_ROOT $ENV{SCE_ROOT_DIR})
    string(REGEX REPLACE "//" "/" PS5_ROOT ${PS5_ROOT})
    if (EXISTS "$ENV{SCE_PROSPERO_SDK_DIR}" AND IS_DIRECTORY "$ENV{SCE_PROSPERO_SDK_DIR}")
        string(REGEX REPLACE "\\\\" "/" PS5_SDK $ENV{SCE_PROSPERO_SDK_DIR})
        string(REGEX REPLACE "//" "/" PS5_SDK ${PS5_SDK})
        get_filename_component(SCE_VERSION "${PS5_SDK}" NAME)
    endif ()
endif ()

# Report and check version if it exist
if (NOT "${SCE_VERSION}" STREQUAL "")
    message(STATUS "PS5 SCE version found: ${SCE_VERSION}")
    if (NOT "${SCE_VERSION}" MATCHES "${REQUIRED_PS5_VERSION}+")
        message(WARNING "Expected PS5 SCE version: ${REQUIRED_PS5_VERSION}")
        if (PLATFORM_TOOLCHAIN_ENVIRONMENT_ONLY)
            set(PS5_ROOT)
            set(PS5_SDK)
        endif ()
    endif ()
endif ()

# If we only want the environment values, exit now
if (PLATFORM_TOOLCHAIN_ENVIRONMENT_ONLY)
    return()
endif ()

# We are building PS5 platform, fail if PS5 SCE not found
if (NOT PS5_ROOT OR NOT PS5_SDK)
    message(FATAL_ERROR "Engine requires PS5 SCE SDK to be installed in order to build PS5 platform.")
endif ()

# Tell CMake we are cross-compiling to PS5 (Prospero)
set(CMAKE_SYSTEM_NAME Prospero)
set(PS5 True)

# Set CMake system root search path
set(CMAKE_SYSROOT "${PS5_ROOT}")

# Set compilers to the ones found in PS4 SCE SDK directory
set(CMAKE_C_COMPILER "${PS5_SDK}/host_tools/bin/prospero-clang.exe")
set(CMAKE_CXX_COMPILER "${PS5_SDK}/host_tools/bin/prospero-clang++.exe")
set(CMAKE_ASM_COMPILER "${PS5_SDK}/host_tools/bin/prospero-as.exe")

# Only search the PS5 SCE SDK, not the remainder of the host file system
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(_PS5_PROSPERO_TOOLCHAIN_ ON)