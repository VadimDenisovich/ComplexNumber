cmake_minimum_required(VERSION 3.10...3.30)
project(ComplexNumberProject)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/lib/Catch2/src")

# Поскольку я устанавливал Catch2 вручную с помощью git clone, то отыскиваем библиотеку по репозиторию. 
find_package(Catch2 3 REQUIRED)

add_executable(ComplexNumberTest include/complexNumber.h src/complexNumber.cpp tests/test_complexNumber.cpp)
target_include_directories(ComplexNumberTest PRIVATE
  "${PROJECT_SOURCE_DIR}/include"
)
target_link_libraries(ComplexNumberTest PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(ComplexNumberTest)