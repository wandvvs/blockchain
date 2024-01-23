#ifndef BLOCK_H
#define BLOCK_H

#include "../utils/crypto.h"
#include "transaction.h"

#include <nlohmann/json_fwd.hpp>
#include <nlohmann/json.hpp>
#include <openssl/sha.h>

#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <functional>

class Blockchain;

class Block
{
private:
    friend Blockchain;

    std::vector<Transaction> m_transactions;
    void mine();

    std::string m_hash;
    std::string m_prevhash;
    std::function<std::string(std::string)> HASH_FUNC {sha256};

    static uint32_t count;
    uint32_t        m_index;
    uint32_t        m_timestamp;
    int32_t         m_nonce;

public:
    Block();
    Block(std::vector<Transaction> transactions);

    std::string get_combined_data() const;

    void get_data()         const;
    void get_transactions() const;

    nlohmann::json serialize();
    void deserialize(const nlohmann::json& json);

    void tcp_send_block(int client_socket) const;
};

#endif
