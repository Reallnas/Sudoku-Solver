cmake_minimum_required(VERSION 3.5)

project(Sudoku_solver LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Sudoku_solver
        src/main.cpp
        src/sudoku.h
        src/sudoku.cpp
        src/sudokusolver.h
        src/sudokusolver.cpp
        src/mainwindow.h
        src/mainwindow.cpp
        src/graphicssudokugrid.h
        src/graphicssudokugrid.cpp
    )

target_link_libraries(Sudoku_solver PRIVATE Qt5::Widgets)

