#ifndef BLOCK_H
#define BLOCK_H

#include "../utils/crypto.h"
#include "transaction.h"

#define SHA_SHA256(data) sha256(data)
#define SHA_SHA384(data) sha384(data)
#define SHA_SHA512(data) sha512(data)

#define HASH_FUNC SHA_SHA512        /* select the hashing algorithm from defines above */

#include <nlohmann/json_fwd.hpp>
#include <nlohmann/json.hpp>
#include <openssl/sha.h>

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

    std::string m_hash;
    std::string m_prevhash;
    uint32_t m_index;
    uint32_t m_timestamp;
    int32_t m_nonce;
    std::vector<Transaction> m_transactions;
        
    static uint32_t count; // It is nedeed for store the number of blocks created and to index the created blocks
    
    void mine(); // POW (Proof Of Work) implementation. Generates a hash until it is correct. Increasing the nonce.
public:
    Block();
    Block(std::vector<Transaction> transactions);

    std::string get_combined_data();

    void get_data() const;
    void get_transactions() const;

    nlohmann::json serialize();
    void deserialize(const nlohmann::json& json);

    void tcp_send_block(int client_socket);
};
#endif
