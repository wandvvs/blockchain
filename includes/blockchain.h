#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "transaction.h"

#include <openssl/x509.h>

#include <cstdint>
#include <algorithm>

const uint32_t DIFFICULT = 3; // Temporarily it will be const, cuz i dont have network and network config now.

class Blockchain
{
private:
    std::vector<Block> chain;
    std::vector<Transaction> pending_transactions;
    
    float reward = 100;

    Block create_genesis();
public:
    Blockchain();

    void add(Block& block);
    void get_blocks_data();
    void mine_pending_transactions(std::string reward_address, RSA* miner_private_key);
    void create_transaction(Transaction transaction, RSA* private_key);

    float get_balance(std::string address);

    Block get_genesis();
    Block get_last();

    bool is_valid();

    size_t get_height();
};

#endif
