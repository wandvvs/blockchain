#include "block.h"
#include "blockchain.h"
#include <chrono>
#include <openssl/ssl.h>
#include <iostream>

unsigned Block::count = 0;

std::string Block::getHash() {
    std::string combinedData = std::to_string(index) + std::to_string(timestamp) +
                               std::to_string(proof_of_work) + data + previous_hash;
    unsigned char hashBuffer[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, combinedData.c_str(), combinedData.length());
    SHA256_Final(hashBuffer, &sha256);

    char hashStr[2 * SHA256_DIGEST_LENGTH + 1];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashStr + 2 * i, "%02x", hashBuffer[i]);
    }
    hashStr[2*SHA256_DIGEST_LENGTH] = '\0';

    return std::string(hashStr);
}

Block::Block(std::string data, unsigned difficulty) {
    count++;
    this->timestamp = static_cast<unsigned>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    this->proof_of_work = -1;
    this->hash = getHash();
    this->data = data;
    this->index = count;
    this->difficulty = difficulty;
}

void Block::mine(unsigned Difficulty) {
    char char_str[Difficulty + 1];
    for(int i = 0; i < Difficulty; ++i) {
        char_str[i] = '0';
    }
    char_str[Difficulty] = '\0';

    std::string str(char_str);

    do {
        this->proof_of_work++;
        this->hash = getHash();
    } while (this->hash.substr(0, Difficulty) != str);

    std::cout << "Block mined\n"
              << "Index: " << this->index << "\n"
              << "Timestamp: " << this->timestamp << "\n"
              << "Proof Of Work: " << this->proof_of_work << "\n"
              << "Data: " << this->data << "\n"
              << "Hash: " << this->hash << "\n"
              << "Previous Hash: " << this->previous_hash << "\n"
              << "Difficulty: " << Difficulty << "\n"
              << std::endl;
}

