cmake_minimum_required(VERSION 3.25)
project(blockchain)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_PREFIX_PATH "C:/Program Files/OpenSSL-Win64")
include_directories("C:/Program Files/OpenSSL-Win64/include")
link_directories("C:/Program Files/OpenSSL-Win64/lib")

add_executable(blockchain main.cpp block.h blockchain.h block.cpp blockchain.cpp)

target_link_libraries(blockchain PRIVATE libssl libcrypto)
