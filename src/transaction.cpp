#include "../includes/transaction.h"

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

std::string Transaction::get_hash()
{
    return sha256(this->m_sender + this->m_receiver + std::to_string(m_amount));
}

void Transaction::sign(RSA* private_key)
{
    std::string data_to_sign = m_sender + m_receiver + std::to_string(m_amount);

    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const uint8_t*>(data_to_sign.c_str()), data_to_sign.size(), hash);
    
    uint8_t sign[RSA_size(private_key)];
    uint32_t len;

    if (RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, sign, &len, private_key) != 1) {
        std::cout << "Signing failed.\n";
        return;
    }

    m_signature.assign(reinterpret_cast<char*>(sign), len);
    signature_len = len;
}

bool Transaction::verify(RSA* public_key) const {

    ERR_clear_error();

    std::string dataToVerify = m_sender + m_receiver + std::to_string(m_amount);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(dataToVerify.c_str()), dataToVerify.size(), hash);


    int ret = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH,
                     reinterpret_cast<const unsigned char*>(m_signature.data()), signature_len, public_key);

    if (ret != 1) {
        unsigned long err = ERR_get_error();
        char *errStr = ERR_error_string(err, NULL);
        std::cout << "Error occurred during verification: " << errStr << std::endl;
        return false;
    }
    return true;
}

bool Transaction::is_valid(RSA* publicKey) const {
    if (!(m_amount > 0)) {
        return false;
    }

    return verify(publicKey);
}
