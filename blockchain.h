#include <vector>
#include "block.h"

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

class Blockchain {
private:
    std::vector<Block> chain;
public:
    Blockchain();
    void add(Block block);
};

#endif //BLOCKCHAIN_H
