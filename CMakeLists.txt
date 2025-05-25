cmake_minimum_required(VERSION 3.10)
project(matrix_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

# Add test executables
add_executable(lu_test src/tests/lu_test.cpp)
add_executable(vector_test src/tests/vector_test.cpp)

# Add main executable (if needed)
add_executable(matrix_test src/main.cpp) 