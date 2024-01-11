#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <nlohmann/json.hpp>

class Block;

class Transaction
{
private:
    friend Block;

    std::string m_sender;
    std::string m_receiver;
    float m_amount;
public:
    Transaction();
    Transaction(std::string sender, std::string receiver, float amount);

    nlohmann::json serialize() const;
    void deserialize(const nlohmann::json& json);
};

#endif
