#include "../includes/blockchain.h"

Blockchain::Blockchain()
{
    this->chain = {this->create_genesis()};
}

void Blockchain::add(Block& block)
{
    block.m_prevhash = get_last().m_hash;
    block.mine();
    chain.push_back(block);
}

void Blockchain::mine_pending_transactions(std::string reward_address, RSA* miner_private_key)
{
    std::vector<std::string> transactions_hash;
    for(const auto& elem : pending_transactions)
    {
        std::string hashed = sha256(elem.get_all_data());
        transactions_hash.push_back(hashed);
    }

    MerkleTree merkle_tree(transactions_hash);
    
    Block block(pending_transactions);
    block.mine();

    for(auto& transaction : block.m_transactions) {
        transaction.sign(miner_private_key);
    }
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

    for (const auto& block : chain) {
        for (const auto& transaction : block.m_transactions) {
            if(address == transaction.m_receiver) {
                balance += transaction.m_amount;
            }
            else if(address == transaction.m_sender) {
                balance -= transaction.m_amount;
            }
        }
    }

    return balance;
}

void Blockchain::get_blocks_data() const
{
    for(const auto& block : chain) {
        block.get_data();
    }
}

bool Blockchain::is_valid() const
{
    for(int i = 0; i < chain.size(); ++i) {
        if(chain[0].m_hash != chain[1].m_prevhash) {
            return false;
        }
    }

    return true;
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

Block Blockchain::get_genesis()
{
    return chain.empty() ? Block() : chain[0];
}

Block Blockchain::get_last() const
{
    return chain[get_height() - 1];
}

size_t Blockchain::get_height() const
{
    return chain.size();
}
