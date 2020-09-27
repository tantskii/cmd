cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    message(STATUS "TRAVIS_BUILD_NUMBER environment variable is not defined. Run 'export TRAVIS_BUILD_NUMBER=1'.")
endif()

project(bulk VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories(src)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)

set(LOG_DIRECTORY ${CMAKE_SOURCE_DIR}/log)
configure_file(src/log_dir.h.in "${CMAKE_SOURCE_DIR}/src/log_dir.h")

set_target_properties(bulk bulk_test bulk_lib PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

FIND_PACKAGE(Doxygen)
if (DOXYGEN_FOUND)
    message(STATUS "Doxygen is found:)")
    
    set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/src)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/doc)
    set(DOXYGEN_PROJECT_NAME ${CMAKE_PROJECT_NAME})
    set(DOXYGEN_PROJECT_NUMBER 0.0.$ENV{TRAVIS_BUILD_NUMBER})
    
    configure_file(doxygen.conf.in doxygen.conf)
    add_custom_target(bulk_doc COMMAND ${DOXYGEN_EXECUTABLE} doxygen.conf)
else ()
    message(STATUS "WARNING: Doxygen is not found:(")
endif()

if (MSVC)
    target_compile_options(bulk PRIVATE
        /W4
    )
    target_compile_options(bulk_test PRIVATE
        /W4
    )
    target_compile_options(bulk_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(bulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(bulk_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(bulk_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT tihon1997@gmail.com)
include(CPack)

# enable_testing()
# add_test(bulk_test bulk_test)
