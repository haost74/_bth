cmake_minimum_required(VERSION 3.2...3.5)
set (PROJECT_NAME "app" CXX)
project(${PROJECT_NAME})

# -----------------------------------------------------

set (PROJECT_SOURCE_DECLARATION_DIRECTORY ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DEFINITION_DIRECTORY ${PROJECT_SOURCE_DIR}/src)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set (BOOST_ROOT "C:/Boost/boost_1_80_0")

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package (Boost 1.80.0 REQUIRED COMPONENTS 
               system filesystem regex thread context)

if (Boost_FOUND)
   include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif()

include_directories (${PROJECT_SOURCE_DECLARATION_DIRECTORY})

# -----------------------------------------------------

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})