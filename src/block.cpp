#include "../includes/block.h"
#include "../includes/blockchain.h"

uint32_t Block::count = 1;

Block::Block()
{

}

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
    std::string combin_data = std::to_string(this->m_index) +
                              this->m_hash + std::to_string(this->m_nonce) +
                              this->m_prevhash;
    char char_str[DIFFICULT + 1];
    for(uint32_t i = 0; i < DIFFICULT; ++i) {
        char_str[i] = '0';
    }
    char_str[DIFFICULT] = '\0';

    std::string str(char_str);
do {
        combin_data =  std::to_string(this->m_index) + 
                              this->m_hash + std::to_string(this->m_nonce) +
                              this->m_prevhash;
        this->m_timestamp = static_cast<unsigned>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        this->m_nonce++;
        this->m_hash = HASH_FUNC(combin_data);
    }
    while(!this->m_hash.starts_with(char_str));
}

void Block::get_data() const
{
    std::cout << "Index: " << m_index << "\nNonce: " << m_nonce << "\nHash: " << m_hash << "\nPrevious hash: " << m_prevhash << "\nTimestamp: " << m_timestamp << "\nTransactions count: " << m_transactions.size() << "\nMerkle root hash: " << merkle_root_transaction << "\n\n";
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
        std::cout << "Sender: "     << transaction.m_sender
                  << "\nReceiver: " << transaction.m_receiver
                  << "\nAmount: "   << transaction.m_amount
                  << "\n\n";
    }
}

std::string Block::get_combined_data() const
{
    return std::to_string(m_index) + "\n" + m_hash + "\n" + std::to_string(m_nonce) 
        + "\n" + m_prevhash + "\n"; 
}
