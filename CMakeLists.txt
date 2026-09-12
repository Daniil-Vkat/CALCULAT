cmake_minimum_required(VERSION 3.16)
project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

# Объявляем header-only библиотеку mathops
# INTERFACE используется, так как библиотека состоит только из заголовков
add_library(mathops INTERFACE)

# Указываем, где искать заголовки для этой библиотеки
# Это необходимо, чтобы main.cpp мог найти libmath.h
target_include_directories(mathops INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)



# Создаем исполняемый файл только из main.cpp
add_executable(test_math test/test.cpp)

# Подключаем библиотеку mathops к исполняемому файлу
target_link_libraries(test_math PRIVATE mathops)