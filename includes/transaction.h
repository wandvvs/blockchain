// SPDX-License-Identifier: MIT
/*
 * Header file of transaction class
 *
 * Copyright (C) 2024 wandvvs
*/
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <nlohmann/json_fwd.hpp>
#include <nlohmann/json.hpp>
#include <secp256k1.h>

#include "../utils/crypto.h"

#include <cstdint>
#include <string>
#include <format>

class Block;
class Blockchain;

class Transaction
{
private:
    friend Block;
    friend Blockchain;

    std::string m_sender;
    std::string m_receiver;
    std::string m_signature;
    float       m_amount;

public:
    Transaction();
    Transaction(std::string sender, std::string receiver, float amount);

    nlohmann::json serialize() const;
    void deserialize(const nlohmann::json& json);

    void sign(RSA* private_key);
    bool verify(RSA* public_key)   const;
    bool is_valid(RSA* public_key) const;

    uint32_t signature_len;

    std::string get_hash();
    std::string get_all_data() const  { return m_sender + m_receiver + std::to_string(m_amount); }
    std::string get_sender() const { return m_sender; }
    std::string get_receiver() const { return m_receiver; }
    float       get_amount() const { return m_amount; }
};

#endif
