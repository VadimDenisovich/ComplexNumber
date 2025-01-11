cmake_minimum_required(VERSION 3.10...3.30)
project(ComplexNumberProject)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поскольку я устанавливал Catch2 вручную с помощью git clone, то отыскиваем библиотеку по репозиторию. 
# find_package(Catch2 3 REQUIRED)
# set(CMAKE_PREFIX_PATH "D:/CPP_externalLib/vcpkg-2024.12.16/packages/boost_lexical_cast_x64-windows/share" ${CMAKE_PREFIX_PATH})
set(boost_lexical_cast_DIR "D:/CPP_externalLib/vcpkg-2024.12.16/packages/boost-lexical_cast_x64-windows/share/boost_lexical_cast")
set(Boost_NO_SYSTEM_PATHS ON)
set(Catch2_DIR "D:/CPP_externalLib/vcpkg-2024.12.16/packages/catch2_x64-windows/share/Catch2")
find_package(Catch2 CONFIG REQUIRED)

find_package(Boost REQUIRED COMPONENTS lexical_cast)

add_executable(ComplexNumberApp main.cpp include/complexNumber.h src/complexNumber.cpp include/rationalNumber.h src/rationalNumber.cpp)
target_include_directories(ComplexNumberApp PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(ComplexNumberApp PRIVATE Boost::lexical_cast)

add_executable(ComplexNumberTest include/complexNumber.h src/complexNumber.cpp include/rationalNumber.h src/rationalNumber.cpp tests/test_complexNumber.cpp)
target_include_directories(ComplexNumberTest PRIVATE
  "${PROJECT_SOURCE_DIR}/include"
)
target_link_libraries(ComplexNumberTest PRIVATE Catch2::Catch2WithMain Boost::lexical_cast)

include(CTest)
include(Catch)
catch_discover_tests(ComplexNumberTest)