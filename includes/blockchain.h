#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "transaction.h"

#include <cstdint>
#include <algorithm>

const uint32_t DIFFICULT = 3;

class Blockchain
{
private:
    std::vector<Block>       chain;
    std::vector<Transaction> pending_transactions;
    
    float reward = 100.0f;

    Block create_genesis();

public:
    Blockchain();

    void add(Block& block);
    void get_blocks_data() const;
    void mine_pending_transactions(std::string reward_address, RSA* miner_private_key);
    void create_transaction(Transaction transaction, RSA* private_key);

    Block get_genesis();
    Block get_last() const;
    
    float  get_balance(std::string address);
    bool   is_valid()   const;
    size_t get_height() const;
};

#endif
