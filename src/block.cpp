#include "../includes/block.h"
#include "../includes/blockchain.h"
#include <nlohmann/json_fwd.hpp>

uint32_t Block::count = 0;

Block::Block() = default;

Block::Block(std::string data, std::vector<Transaction> transactions) : m_data(data), m_transactions(transactions)
{
    this->m_nonce = 0;
    this->m_index = count;
    this->m_timestamp = static_cast<unsigned>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    this->m_prevhash = "";
    this->m_hash = "";
    count++;
}

std::string Block::sha256(std::string& combin_data)
{
    uint8_t hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX context;
    SHA256_Init(&context);
    SHA256_Update(&context, combin_data.c_str(), combin_data.length());
    SHA256_Final(hash, &context);

    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

void Block::mine()
{
    std::string combin_data = std::to_string(this->m_index) + this->m_data +
                              this->m_hash + std::to_string(this->m_nonce) +
                              this->m_prevhash;
    char char_str[DIFFICULT + 1];
    for(uint32_t i = 0; i < DIFFICULT; ++i) {
        char_str[i] = '0';
    }
    char_str[DIFFICULT] = '\0';

    std::string str(char_str);
do {
        combin_data =  std::to_string(this->m_index) + this->m_data +
                              this->m_hash + std::to_string(this->m_nonce) +
                              this->m_prevhash;
        this->m_timestamp = static_cast<unsigned>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        this->m_nonce++;
        this->m_hash = sha256(combin_data);
    }
    while(this->m_hash.substr(0,DIFFICULT) != str);
}

void Block::get_data() const
{
    std::cout << "Index: " << m_index << "\nNonce: " << m_nonce << "\nHash: " << m_hash << "\nPrevious hash: " << m_prevhash << "\nData: " << m_data << "\nTimestamp: " << m_timestamp << "\nTransactions count: " << m_transactions.size() << "\n\n";
}

nlohmann::json Block::serialize()
{
    nlohmann::json blockJson;

    blockJson["index"] = m_index;
    blockJson["data"] = m_data;
    blockJson["hash"] = m_hash;
    blockJson["previous hash"] = m_prevhash;
    blockJson["nonce"] = m_nonce;
    blockJson["timestamp"] = m_timestamp;

    blockJson["transactions"] = serialize_transactions();

    return blockJson;
}

nlohmann::json Block::serialize_transactions()
{
    nlohmann::json transactions;

    for(const auto& transaction : m_transactions) {
        transactions.push_back(transaction.serialize());
    }

    return transactions;
}

void Block::deserialize(const nlohmann::json& json)
{
    m_index = json.value("index", 0);
    m_data = json.value("data", "");
    m_hash = json.value("hash", "");
    m_prevhash = json.value("previous hash", "");
    m_nonce = json.value("nonce", 0);
    m_timestamp = json.value("timestamp", 0);
    
    deserialize_transactions(json.value("transactions", nlohmann::json::array()));
}

void Block::deserialize_transactions(const nlohmann::json& transactions)
{
    m_transactions.clear();

    for(const auto& transaction : transactions) {
        Transaction trans;
        trans.deserialize(transaction);
        m_transactions.push_back(trans);
    }
}

void Block::get_transactions() const
{
    for(const auto& transaction : m_transactions) {
        std::cout << "Sender: "     << transaction.m_sender
                  << "\nReceiver: " << transaction.m_receiver
                  << "\nAmount: "   << transaction.m_amount
                  << "\n\n";
    }
}
