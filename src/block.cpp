#include "../includes/block.h"

uint32_t Block::count = 0;

Block::Block() = default;

Block::Block(std::string data) : m_data(data)
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

void Block::mine(uint32_t difficult)
{
    std::string combin_data = std::to_string(this->m_index) + this->m_data +
                              this->m_hash + std::to_string(this->m_nonce) +
                              this->m_prevhash;
    char char_str[difficult + 1];
    for(uint32_t i = 0; i < difficult; ++i) {
        char_str[i] = '0';
    }
    char_str[difficult] = '\0';

    std::string str(char_str);

    do {
        combin_data =  std::to_string(this->m_index) + this->m_data +
                              this->m_hash + std::to_string(this->m_nonce) +
                              this->m_prevhash;
        this->m_timestamp = static_cast<unsigned>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        this->m_nonce++;
        this->m_hash = sha256(combin_data);
    }
    while(this->m_hash.substr(0,difficult) != str);
}

void Block::get_data() const
{
    std::cout << "Index: " << m_index << "\nNonce: " << m_nonce << "\nHash: " << m_hash << "\nPrevious hash: " << m_prevhash << "\nData: " << m_data << "\nTimestamp: " << m_timestamp << "\n\n" << std::endl;
}
