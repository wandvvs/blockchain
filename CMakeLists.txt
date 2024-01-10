cmake_minimum_required(VERSION 3.10)
project(rlblockchain)

set(SOURCES
    src/main.cpp
    src/block.cpp
    src/blockchain.cpp
)

set(INCLUDE_DIRS
    include
)

find_package(OpenSSL REQUIRED)

add_executable(run ${SOURCES})

target_include_directories(run PRIVATE ${INCLUDE_DIRS})

target_link_libraries(run PRIVATE OpenSSL::SSL OpenSSL::Crypto)

set_target_properties(run PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
