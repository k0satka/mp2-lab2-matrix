set(target gtest)

add_library(${target} STATIC
    src/gtest-all.cc
)

target_include_directories(${target}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    target_link_libraries(${target} PUBLIC pthread)
endif()