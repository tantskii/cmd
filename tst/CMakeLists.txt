set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest c++experimental)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest stdc++fs)
endif()
