#include "../includes/blockchain.h"

// using namespace crypto::rsa;

int main()
{
    Blockchain chain;

    RSA* miner_private_key = crypto::rsa::generate_private_key();

    RSA* sender_private_key = crypto::rsa::generate_private_key();
    RSA* sender_public_key = crypto::rsa::generate_public_key(sender_private_key);

    RSA* receiver_private_key = crypto::rsa::generate_private_key();
    RSA* receiver_public_key = crypto::rsa::generate_public_key(receiver_private_key);

    Transaction test {"Sender", "Receiver", 250.5};

    test.sign(sender_private_key);
    
    if(test.verify(sender_public_key))
    {
        chain.create_transaction(test, sender_private_key);
        chain.mine_pending_transactions("wand", miner_private_key);

        std::cout << "Sender balance: " << chain.get_balance("Sender") << std::endl;
        std::cout << "Receiver balance: " << chain.get_balance("Receiver") << std::endl;
    }
    else
    {
        std::cerr << "Failed to sign transaction" << std::endl;
    }

    chain.mine_pending_transactions("wand", miner_private_key);

    std::cout << "Miner balance: " << chain.get_balance("wand") << std::endl;

    chain.get_blocks_data();
    
    std::cout << chain.is_valid() << std::endl;

    return 0;
}
