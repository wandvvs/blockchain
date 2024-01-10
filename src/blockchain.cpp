#include "../includes/blockchain.h"

Blockchain::Blockchain() = default;

void Blockchain::add(Block& block, uint32_t diff)
{
    if(!chain.empty()) {
        std::string prev = chain.back().m_hash;
        block.m_prevhash = prev;
        block.mine(diff);
    }
    block.mine(diff);
    chain.push_back(block);
}

void Blockchain::get_blocks_data()
{
    for(const auto& block : chain) {
        block.get_data();
    }
}
