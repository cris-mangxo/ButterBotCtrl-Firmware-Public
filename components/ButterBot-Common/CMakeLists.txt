# CMakeLists for ESP-IDF

file(GLOB_RECURSE SOURCES "src/**.cpp" "src/**.c")

# Optional generated catalog; default sources remain the manufacturer's sources.
if(DEFINED BUTTERBOT_PHRASES_CPP)
    # Positive portable POSIX alphabet, shared with the Python wrapper.
    # Validate before REALPATH: CMake otherwise interprets backslashes as slashes.
    if(NOT "${BUTTERBOT_PHRASES_CPP}" MATCHES "^/[A-Za-z0-9_./-]+$")
        message(FATAL_ERROR "BUTTERBOT_PHRASES_CPP requires a portable POSIX path")
    endif()
    if(NOT IS_ABSOLUTE "${BUTTERBOT_PHRASES_CPP}" OR NOT EXISTS "${BUTTERBOT_PHRASES_CPP}" OR IS_DIRECTORY "${BUTTERBOT_PHRASES_CPP}")
        message(FATAL_ERROR "BUTTERBOT_PHRASES_CPP must be an existing absolute file outside the repository")
    endif()
    get_filename_component(_phrases_real "${BUTTERBOT_PHRASES_CPP}" REALPATH)
    if(NOT "${_phrases_real}" MATCHES "^/[A-Za-z0-9_./-]+$" OR
       NOT "${BUTTERBOT_PHRASES_CPP}" STREQUAL "${_phrases_real}")
        message(FATAL_ERROR "BUTTERBOT_PHRASES_CPP requires the canonical portable POSIX path")
    endif()
    if(NOT "${BUTTERBOT_PHRASES_CPP}" MATCHES "\\.cpp$" OR NOT "${_phrases_real}" MATCHES "\\.cpp$")
        message(FATAL_ERROR "BUTTERBOT_PHRASES_CPP received and resolved paths must end in .cpp")
    endif()
    get_filename_component(_repo_real "${CMAKE_CURRENT_LIST_DIR}/../.." REALPATH)
    file(RELATIVE_PATH _phrases_relative "${_repo_real}" "${_phrases_real}")
    if(NOT _phrases_relative MATCHES "^\\.\\./")
        message(FATAL_ERROR "BUTTERBOT_PHRASES_CPP must be outside the repository")
    endif()
    file(SHA256 "${_phrases_real}" _phrases_sha256)
    if(NOT DEFINED BUTTERBOT_PHRASES_SHA256 OR NOT "${_phrases_sha256}" STREQUAL "${BUTTERBOT_PHRASES_SHA256}")
        message(FATAL_ERROR "BUTTERBOT_PHRASES_SHA256 mismatch")
    endif()
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Phrases.cpp")
    set(_phrases_selected "${_phrases_real}")
    list(LENGTH _phrases_selected _phrases_count)
    if(NOT _phrases_count EQUAL 1)
        message(FATAL_ERROR "BUTTERBOT_PHRASES_CPP must select exactly one verified source")
    endif()
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${_phrases_selected}")
    list(APPEND SOURCES "${_phrases_selected}")
endif()
set(COMPONENT_SRCS ${SOURCES})

set(COMPONENT_ADD_INCLUDEDIRS src)

set(COMPONENT_REQUIRES CMF)

register_component()
