#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"

const uint32_t DIFFICULT = 3; // Temporarily it will be const, cuz i dont have network and network config now.

class Blockchain
{
private:
    std::vector<Block> chain;
public:
    Blockchain();

    void add(Block& block);
    void get_blocks_data();

    bool is_valid();
};

#endif
