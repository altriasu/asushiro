# 指定CMake最低版本要求（根据你的版本3.18.0设置）
cmake_minimum_required(VERSION 3.18.0)

# 项目名称（可自定义）
project(ThreadProgram)

# 设置C++标准（多线程建议至少C++11）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_libraries(pthread)

add_executable(firstBuild.out src/firstBuild.cpp)
add_executable(Exception.out src/Exception.cpp)
add_executable(dataShare.out src/dataShare.cpp)

# 可选：指定可执行文件的输出路径（默认在build目录下）
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
