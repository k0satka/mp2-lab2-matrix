set(target ${MP2_BENCHMARK})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${target} ${srcs} ${hdrs})

target_include_directories(${target} PUBLIC ${MP2_INCLUDE})