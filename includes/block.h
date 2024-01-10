#ifndef BLOCK_H
#define BLOCK_H

#include <openssl/sha.h>

#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <chrono>


class Block
{
public:
    std::string m_data;
    std::string m_hash;
    std::string m_prevhash;
    uint32_t m_index;
    uint32_t m_timestamp;
    int32_t m_nonce;
        
    static uint32_t count;

    std::string sha256(std::string& combin_data);

    Block();
    Block(std::string data);

    void mine(uint32_t difficult);
    void get_data() const;
};

#endif
