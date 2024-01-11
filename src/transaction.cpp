#include "../includes/transaction.h"
#include <nlohmann/json_fwd.hpp>

Transaction::Transaction() = default;

Transaction::Transaction(std::string sender, std::string receiver, float amount)
        : m_sender(sender), m_receiver(receiver), m_amount(amount) {}

nlohmann::json Transaction::serialize() const
{
    return {
        {"sender", m_sender},
        {"receiver", m_receiver},
        {"amount", m_amount}
    };
}

void Transaction::deserialize(const nlohmann::json& json)
{
    this->m_sender = json.value("sender", "");
    this->m_receiver = json.value("receiver", "");
    this->m_amount = json.value("amount", 0);
}
