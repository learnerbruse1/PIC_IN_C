
cmake_minimum_required(VERSION 3.15)
project(KSVD)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

#生成文件位置
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(ksvd ${SRC})

#包含头文件
target_include_directories(ksvd PRIVATE 
                ${CMAKE_CURRENT_SOURCE_DIR}/include                                   
                ${CMAKE_CURRENT_SOURCE_DIR}/deps/Daeknet
                ${CMAKE_CURRENT_SOURCE_DIR}/deps/std
)

#add_subdirectory(deps/smallcv-main)        指定另一个项目位置（含有CMakeLists文件）
#指定 静态/动态 库路径
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/jepglib/bin)



