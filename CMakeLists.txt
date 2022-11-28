cmake_minimum_required(VERSION 3.22)
project(grafica__first_one_)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pirates_Hide_and_Seek src/main.cpp)

include_directories("D:\\Informatica-facultate\\Graphics library\\winbgim")
include_directories(src)

target_link_libraries (Pirates_Hide_and_Seek "D:\\Informatica-facultate\\Graphics library\\winbgim\\libbgi.a")
