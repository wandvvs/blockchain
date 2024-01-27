cmake_minimum_required(VERSION 3.10)
project(rlblockchain)

set(CLIENT_SOURCES
    src/main.cpp
    src/block.cpp
    src/blockchain.cpp
    src/transaction.cpp
    src/merkle_tree.cpp
)

set(INCLUDE_DIRS
    include
)

find_package(OpenSSL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

add_executable(run_client ${CLIENT_SOURCES})

target_include_directories(run_client PRIVATE ${INCLUDE_DIRS})

target_link_libraries(run_client PRIVATE
    Boost::system
    OpenSSL::SSL OpenSSL::Crypto
    nlohmann_json::nlohmann_json
)

set_target_properties(run_client PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_compile_options(run_client PRIVATE -Wno-deprecated-declarations)
