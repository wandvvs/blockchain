#include "../includes/block.h"
#include "../includes/blockchain.h"

uint32_t Block::count = 1;

Block::Block() = default;

Block::Block(std::vector<Transaction> transactions) : m_transactions(transactions)
{
    this->m_nonce = 0;
    this->m_index = count;
    this->m_timestamp = static_cast<unsigned>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    this->m_prevhash = "";
    this->m_hash = "";
    count++;
}

void Block::mine()
{
    std::string combin_data = std::format("{}{}{}{}{}", m_index, m_hash, m_nonce, m_prevhash, m_timestamp);

    char char_str[DIFFICULT + 1];
    for(uint32_t i = 0; i < DIFFICULT; ++i) {
        char_str[i] = '0';
    }
    char_str[DIFFICULT] = '\0';

    std::string str(char_str);
    do
    {
        combin_data = std::format("{}{}{}{}{}", m_index, m_hash, m_nonce, m_prevhash, m_timestamp);
        this->m_timestamp = static_cast<unsigned>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        this->m_nonce++;
        this->m_hash = HASH_FUNC(combin_data);
    }
    while(!this->m_hash.starts_with(char_str));
}

void Block::get_data() const
{

   std::cout << std::format("Index: {}\nNonce: {}\nHash: {}\nPrevious hash: {}\nTimestamp: {}\nTransactions count: {}\nMerkle root hash: {}",
                           m_index,   m_nonce,   m_hash,   m_prevhash, m_timestamp, m_transactions.size(), m_merkle_root_transaction) << "\n\n";
}

nlohmann::json Block::serialize()
{
    nlohmann::json blockJson;

    blockJson["index"] = m_index;
    blockJson["hash"] = m_hash;
    blockJson["previous hash"] = m_prevhash;
    blockJson["nonce"] = m_nonce;
    blockJson["timestamp"] = m_timestamp;

    return blockJson;
}


void Block::deserialize(const nlohmann::json& json)
{
    m_index = json.value("index", 0);
    m_hash = json.value("hash", "");
    m_prevhash = json.value("previous hash", "");
    m_nonce = json.value("nonce", 0);
    m_timestamp = json.value("timestamp", 0);
    
}

void Block::get_transactions() const
{
    for(const auto& transaction : m_transactions) {
        std::cout << std::format("Sender: {}\nReceiver: {}\nAmount: {}", transaction.m_sender, transaction.m_receiver, transaction.m_amount) << "\n\n";
    }
}

std::string Block::get_combined_data() const
{
    return std::format("{}{}{}{}{}{}", m_index, m_hash, m_nonce, m_prevhash, m_timestamp, m_merkle_root_transaction);
}
