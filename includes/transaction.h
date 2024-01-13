#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <nlohmann/json.hpp>
#include <secp256k1.h>

class Block;
class Blockchain;

class Transaction
{
private:
    friend Block;
    friend Blockchain;

    std::string m_sender;
    std::string m_receiver;
    float m_amount;

    std::string m_signature;
public:
    Transaction();
    Transaction(std::string sender, std::string receiver, float amount);

    nlohmann::json serialize() const;
    void deserialize(const nlohmann::json& json);

    void sign(RSA* private_key);
    bool verify(RSA* public_key) const;
    bool is_valid(RSA* public_key) const;

    uint32_t signature_len;

    std::string get_hash();

    std::string get_sender() const { return m_sender; }
    std::string get_receiver() const { return m_receiver; }
    float get_amount() const { return m_amount; }
};

#endif
