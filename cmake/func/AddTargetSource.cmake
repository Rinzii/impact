# Helper function to add headers to the global source list
function(imp_add_headers)
    set(SOURCE_FILES "")
    foreach(header IN LISTS ARGV)
        list(APPEND SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${header}")
    endforeach()
    target_sources(${PROJECT_NAME} PUBLIC ${SOURCE_FILES})
endfunction()

# Helper function to add sources to the global source list
function(imp_add_sources)
    set(SOURCE_FILES "")
    foreach(source IN LISTS ARGV)
        list(APPEND SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
    endforeach()
    target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
endfunction()


function(imp_add_public)
    set(PUBLIC_FILES "")
    foreach(public_file IN LISTS ARGV)
        list(APPEND PUBLIC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${public_file}")
    endforeach()
    target_sources(${PROJECT_NAME} PUBLIC ${PUBLIC_FILES})
endfunction()

# Helper function to add headers to the global source list
function(imp_add_private)
    set(PRIVATE_FILES "")
    foreach(private_file IN LISTS ARGV)
        list(APPEND PRIVATE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${private_file}")
    endforeach()
    target_sources(${PROJECT_NAME} PUBLIC ${PRIVATE_FILES})
endfunction()
