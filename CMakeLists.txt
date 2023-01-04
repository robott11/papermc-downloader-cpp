cmake_minimum_required(VERSION 3.23.2)

project(PaperMC-tool)

set(CMAKE_CXX_STANDARD 14)
set(SRC_DIR ./src)
set(INCLUDE_DIR ./include)
set(LIB_DIR ./lib)

add_executable(
        PaperMC-tool
        ${SRC_DIR}/Main.cpp
        ${SRC_DIR}/Cli.cpp
        ${SRC_DIR}/PaperMC.cpp
)

include_directories(BEFORE ${INCLUDE_DIR})

target_link_libraries(PaperMC-tool libcurl.so)