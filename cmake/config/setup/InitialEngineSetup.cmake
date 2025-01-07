if (NOT DEFINED IMPACT_ROOT_DIR)
    message(FATAL_ERROR "IMPACT_ROOT_DIR is not defined. It must ve set before we can include InitialSetup")
endif()

if (NOT DEFINED IMPACT_ENGINE_ROOT_DIR)
    message(FATAL_ERROR "IMPACT_ENGINE_ROOT_DIR is not defined. It must ve set before we can include InitialSetup")
endif()

include(${IMPACT_ROOT_DIR}/cmake/config/setup/CMakeArchs.cmake)
include(${IMPACT_ROOT_DIR}/cmake/config/setup/CMakeCompilers.cmake)
include(${IMPACT_ROOT_DIR}/cmake/config/setup/CMakePlatforms.cmake)

include(${IMPACT_ROOT_DIR}/cmake/config/setup/DownloadSDKs.cmake)