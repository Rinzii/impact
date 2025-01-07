include(CMakeDependentOption)

if (NOT DEFINED IMPACT_ENGINE_ROOT_DIR)
    set(IMPACT_ENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif ()

# Make sure we have setup the project root variable before including the main setup
if (NOT DEFINED IMPACT_ROOT_DIR)
    message(FATAL_ERROR "IMPACT_ROOT_DIR is not defined!")
else ()
    include(${IMPACT_ROOT_DIR}/cmake/config/setup/InitialEngineSetup.cmake)
endif ()

add_library(impact)
add_library(impact::engine ALIAS impact)

set_target_properties(impact PROPERTIES OUTPUT_NAME "impact-engine")

target_compile_definitions(impact
        PUBLIC
        $<$<CONFIG:Debug>:IMP_DEBUG>
        $<$<CONFIG:RelWithDebInfo>:IMP_DEBUG>
        $<$<CONFIG:Release>:IMP_NDEBUG>
)

if (CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    target_compile_options(impact PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    target_compile_options(impact PRIVATE
            /W4 /WX
    )
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL MSVC OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    # Make MSVC shut up about not actually deprecated functions
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif ()

target_link_libraries(impact
        PRIVATE
        impact::ext
)

target_include_directories(impact
        PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include"
        PRIVATE src
)

set_target_properties(impact
        PROPERTIES
        LINKER_LANGUAGE CXX
        POSITION_INDEPENDENT_CODE $<BOOL:${BUILD_SHARED_LIBS}>
)

if (CMAKE_GENERATOR MATCHES "^(Visual Studio)")
    target_compile_options(impact INTERFACE /MP)
endif ()

# Generate build version header
#configure_file(src/impact_version.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/include/genesis_version.hpp" @ONLY)

# Define the final output directory for binaries
set(IMPACT_LIB_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/ImpactEngine/lib/")
set(IMPACT_DLL_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/ImpactEngine/bin/")

# Use generator expressions to conditionally set the final output directory
set(IMPACT_OUTPUT_DIR_FINAL
        "$<IF:$<BOOL:${BUILD_SHARED_LIBS}>,${IMPACT_DLL_OUTPUT_DIR},${IMPACT_LIB_OUTPUT_DIR}>$<CONFIG>"
)

# Check that the folder impact/bin/ImpactEngine exists
file(MAKE_DIRECTORY ${IMPACT_LIB_OUTPUT_DIR})
file(MAKE_DIRECTORY ${IMPACT_DLL_OUTPUT_DIR})

# Add a custom post-build command to copy the library
add_custom_command(
        TARGET impact
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${IMPACT_OUTPUT_DIR_FINAL}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${PROJECT_NAME}>" # Main library file
        "${IMPACT_OUTPUT_DIR_FINAL}"
        COMMENT "Copying $<TARGET_FILE:${PROJECT_NAME}> to ${IMPACT_OUTPUT_DIR_FINAL}"
)

# Conditionally copy the PDB file if it exists (only for linker-based targets)
if (BUILD_SHARED_LIBS)
    add_custom_command(
            TARGET impact
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${IMPACT_OUTPUT_DIR_FINAL}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<IF:$<BOOL:$<CONFIG:Debug>>,$<TARGET_PDB_FILE:${PROJECT_NAME}>,>" # PDB file only exists in Debug mode
            "${IMPACT_OUTPUT_DIR_FINAL}"
            COMMENT "Copying PDB file $<TARGET_PDB_FILE:${PROJECT_NAME}> to ${IMPACT_OUTPUT_DIR_FINAL}"
            VERBATIM
    )
endif ()

# All sources are included through the actual directories
add_subdirectory(include/impact)
add_subdirectory(src)