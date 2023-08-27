#include "block.h"
#include "blockchain.h"
#include "string"

Blockchain::Blockchain() {
    Block genesisBlock("Genesis block", 0);
    chain.push_back(genesisBlock);
}

void Blockchain::add(Block block) {
    std::string previousHash = chain.back().getHash();
    block.previous_hash = previousHash;
    block.mine(block.difficulty);
    chain.push_back(block);
}
