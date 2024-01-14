cmake_minimum_required(VERSION 3.10)
project(rlblockchain)

set(CLIENT_SOURCES
    src/main.cpp
    src/block.cpp
    src/blockchain.cpp
    src/transaction.cpp
)

set(SERVER_SOURCES
    src/network/server.cpp
    src/block.cpp
    src/blockchain.cpp
    src/transaction.cpp
)

set(INCLUDE_DIRS
    include
)

find_package(OpenSSL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_library(SECP256K1_LIBRARY NAMES secp256k1)

add_executable(run_client ${CLIENT_SOURCES})
add_executable(run_server ${SERVER_SOURCES})

target_include_directories(run_client PRIVATE ${INCLUDE_DIRS})
target_include_directories(run_server PRIVATE ${INCLUDE_DIRS})

target_link_libraries(run_client PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(run_client PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(run_client PRIVATE ${SECP256K1_LIBRARY})

target_link_libraries(run_server PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(run_server PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(run_server PRIVATE ${SECP256K1_LIBRARY})

set_target_properties(run_client PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(run_server PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

