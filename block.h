#include <string>
#include <openssl/ssl.h>

#ifndef BLOCK_H
#define BLOCK_H

class Blockchain;

class Block {
private:
    static unsigned count;
    unsigned index;
    unsigned timestamp;
    int proof_of_work;
    std::string data;
    void mine(unsigned difficulty);
    unsigned difficulty;
    std::string previous_hash;
    std::string hash;
    std::string getHash();
    friend class Blockchain;
public:
    Block(std::string data, unsigned difficulty);
};

#endif //BLOCK_H
