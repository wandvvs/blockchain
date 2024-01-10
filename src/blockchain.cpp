#include "../includes/blockchain.h"

Blockchain::Blockchain() = default;

void Blockchain::add(Block& block)
{
    if(!chain.empty()) {
        std::string prev = chain.back().m_hash;
        block.m_prevhash = prev;
    }
    block.mine();
    chain.push_back(block);
}

void Blockchain::get_blocks_data()
{
    for(const auto& block : chain) {
        block.get_data();
    }
}

bool Blockchain::is_valid()
{
    for(int i = 0; i < chain.size(); ++i) {
        if(chain[0].m_hash != chain[1].m_prevhash) {
            return false;
        }
    }

    return true;
}
