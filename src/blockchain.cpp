// SPDX-License-Identifier: MIT
/*
 * Implementation file for blockchain class
 *
 * Copyright (C) 2024 wandvvs
*/
#include "../includes/blockchain.h"
#include <algorithm>

Blockchain::Blockchain() { this->chain = {this->create_genesis()}; }

void Blockchain::add(Block& block)
{
    block.m_prevhash = get_last().m_hash;
    block.mine();
    chain.push_back(block);
}

void Blockchain::mine_pending_transactions(std::string reward_address, RSA* miner_private_key)
{
    std::vector<std::string> transactions_hash;

    std::transform(pending_transactions.begin(), pending_transactions.end(), std::back_inserter(transactions_hash),
        [](const auto& elem)
        {
            return crypto::sha::sha256(elem.get_all_data());
        });

    MerkleTree merkle_tree(transactions_hash);
    
    Block block(pending_transactions);
    block.mine();

    std::for_each(block.m_transactions.begin(), block.m_transactions.end(), [miner_private_key](auto& transaction){
        transaction.sign(miner_private_key);
    });

    block.m_merkle_root_transaction = merkle_tree.get_tree_root();

    block.m_prevhash = get_last().m_hash;

    chain.push_back(block);


    pending_transactions.clear();

    create_transaction({"Reward",
                        reward_address,
                        reward}, miner_private_key);
}

void Blockchain::create_transaction(Transaction transaction, RSA* private_key)
{
    transaction.sign(private_key);
    pending_transactions.push_back(transaction);
}

float Blockchain::get_balance(std::string address)
{
    float balance = 0;

    std::for_each(chain.begin(), chain.end(), [address, &balance](const auto& block)
    {
        std::for_each(block.m_transactions.begin(), block.m_transactions.end(), [address, &balance](const auto& transaction)
        {
             balance += (address == transaction.m_receiver) ? transaction.m_amount : ((address == transaction.m_sender) ? -transaction.m_amount : 0);
        });
    });

    return balance;
}

void Blockchain::get_blocks_data() const
{
    std::for_each(chain.begin(), chain.end(), [](const Block& block) { block.get_data(); });
}

bool Blockchain::is_valid() const {
    return std::adjacent_find(chain.begin() + 1, chain.end(),
        [](const auto& current, const auto& previous) {
            return current.m_prevhash == previous.m_hash;
        }) == chain.end();
}

Block Blockchain::create_genesis()
{
    Block block;

    block.m_index = 0;
    block.m_hash = "Genesis Block";
    block.m_prevhash = "Genesis Block";
    block.m_nonce = 0;

    return block;
}

Block Blockchain::get_genesis()    { return chain.empty() ? Block() : chain[0]; }
Block Blockchain::get_last() const { return chain[get_height()]; }

size_t Blockchain::get_height() const { return chain.size() - 1; }
