cmake_minimum_required(VERSION 3.10)
project(zjucmm)

find_package( LLVM REQUIRED CONFIG)

#find_package(jsoncpp REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSONCPP_LIBRARIES})


include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# For jsb: specific the address
include_directories(/usr/include/llvm-10)
include_directories(/usr/include/llvm-c-10)



execute_process(COMMAND llvm-config-10 --libs OUTPUT_VARIABLE LLVM_LINK_LIBRARIES)
string(STRIP "${LLVM_LINK_LIBRARIES}" LLVM_LINK_LIBRARIES)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ljsoncpp ")
add_custom_command(
    OUTPUT cScanner.cpp
    COMMAND flex -o cScanner.cpp  ${CMAKE_CURRENT_LIST_DIR}/cScanner.l 
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/cScanner.l cParser.cpp
)

add_custom_command(
    OUTPUT cParser.cpp cParser.hpp
    COMMAND bison -d ${CMAKE_CURRENT_LIST_DIR}/cParser.y -o cParser.cpp 
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/cParser.y
)



add_executable(
    zjucmm
    main.cpp
    cCompilerCommon.cpp cCompilerCommon.hpp
    cParser.cpp cParser.hpp cScanner.cpp
    )

set_target_properties(zjucmm PROPERTIES LINK_LIBRARIES "${LLVM_LINK_LIBRARIES}")
target_link_libraries(${PROJECT_NAME} ${JSONCPP_LIBRARIES})