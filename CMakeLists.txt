cmake_minimum_required(VERSION 3.22)
project(20222_team_14)

set(CMAKE_CXX_STANDARD 14)

include_directories(classes/Board)
include_directories(classes/Piece)
include_directories(controllers/BoardController)

add_executable(20222_team_14
        classes/Board/Board.h
        classes/Board/boardMtd.cpp
        classes/Piece/Piece.h
        classes/Piece/PieceMtd.cpp
        controllers/BoardController/BoardController.h
        controllers/BoardController/BoardControllerMtd.cpp
        main.cpp)
