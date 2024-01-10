#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <vector>

class Blockchain
{
private:
    std::vector<Block> chain;
public:
    Blockchain();
    void add(Block& block, uint32_t diff);
    void get_blocks_data();
};

#endif
