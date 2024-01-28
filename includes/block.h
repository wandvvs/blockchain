// SPDX-License-Identifier: MIT
/*
 * Header file of block class
 *
 * Copyright (C) 2024 wandvvs
*/
#ifndef BLOCK_H
#define BLOCK_H

#include "../utils/crypto.h"
#include "transaction.h"
#include "merkle_tree.h"

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
#include <format>

class Blockchain;

class Block
{
private:
    friend Blockchain;

    std::vector<Transaction> m_transactions;
    void mine();
    
    std::string m_merkle_root_transaction;
    std::string m_hash;
    std::string m_prevhash;
    std::function<std::string(std::string)> HASH_FUNC {crypto::sha::sha256};

    static uint32_t count;
    uint32_t        m_index;
    uint32_t        m_timestamp;
    int32_t         m_nonce;

    void set_merkle_root(std::string root) {m_merkle_root_transaction = root;} 
public:
    Block();
    Block(std::vector<Transaction> transactions);

    std::string get_combined_data() const;

    void get_data()         const;
    void get_transactions() const;

    nlohmann::json serialize();
    void deserialize(const nlohmann::json& json);

    std::string get_merkle_root() const { return m_merkle_root_transaction; }
};

#endif
