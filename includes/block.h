#ifndef BLOCK_H
#define BLOCK_H

#include <nlohmann/json_fwd.hpp>
#include <nlohmann/json.hpp>
#include <openssl/sha.h>

#include "transaction.h"

#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

class Blockchain; // FIX: (main file cannot be included recursively when building)

class Block
{
private:
    friend Blockchain;

    std::string m_data;
    std::string m_hash;
    std::string m_prevhash;
    uint32_t m_index;
    uint32_t m_timestamp;
    int32_t m_nonce;
    std::vector<Transaction> m_transactions;
        
    static uint32_t count; // It is nedeed for store the number of blocks created and to index the created blocks

    std::string sha256(std::string& combin_data); // Generating a hash based on the combined data of the block object
    
    void mine(); // POW (Proof Of Work) implementation. Generates a hash until it is correct. Increasing the nonce.
public:
    Block();
    Block(std::string data, std::vector<Transaction> transactions);

    void get_data() const;
    void get_transactions() const;

    nlohmann::json serialize();
    nlohmann::json serialize_transactions();
    void deserialize(const nlohmann::json& json);
    void deserialize_transactions(const nlohmann::json& transactions);
};

#endif
