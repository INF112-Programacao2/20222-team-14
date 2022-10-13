cmake_minimum_required(VERSION 3.22)
project(20222_team_14)

set(CMAKE_CXX_STANDARD 14)

include_directories(classes/Board)
include_directories(classes/Piece)
include_directories(classes/Tower)
include_directories(classes/Cell)
include_directories(classes/Bishop)
include_directories(controllers/BoardController)

add_executable(20222_team_14
        classes/Board/Board.h
        classes/Board/boardMtd.cpp
        classes/Cell/Cell.h
        classes/Cell/cellMtd.cpp
        classes/Piece/Piece.h
        classes/Bishop/Bishop.h
        classes/Bishop/bishopMtd.cpp
        classes/Tower/Tower.h
        classes/Tower/towerMtd.cpp
        classes/Piece/pieceMtd.cpp
        classes/Piece/TotalPiece.h
        classes/Piece/totalPieceMtd.cpp
        controllers/BoardController/BoardController.h
        controllers/BoardController/BoardControllerMtd.cpp
        main.cpp)
