# Blockchain
Blockchain implementation with C++20, all test were performed on Arch Linux.

## Was done:
- [x] Proof Of Work (Mining)
- [x] Serialization
- [x] Transactions
- [x] Signing transactions
- [x] More type for hashing
- [x] Merkle trees
- [ ] P2P
- [ ] Consensus

## **Dependencies:**
```bash
sudo pacman -S openssl
sudo pacman -S nlohmann-json
```
## **Build:**
```bash
cd build
cmake ..
make
./run
```

## Block object
**Fields:**
- data ( contains some string )
- hash ( hash outstanding after mining given difficulty
- prevhash ( previous block hash )
- index ( unique block identifier )
- nonce ( number of attempts to generate a valid hash )
- timestamp ( date and time when block has been successfully added to chain )
- list of transaction

**Methods:**
- pointer to a function from  ../utils/crypto.h (sha256, sha384, sha512) for hashing
- mine ( starts looking for a hash in which the number of zeros at the beginning is the same as the number of constants DIFFICULT  )
- get_data ( it will print all information about this block )
- get_transactions ( it will print all transaction that had been pushed to block )
- get_merkle_root
- serialize ( translates the fields of a block into a json structure )
- deserialize ( takes json as argument and fills the block fields with json argument fields )

## Blockchain object
**Fields:**
- chain ( all blocks which have been added )
- pending_transactions
- reward of mining

**Methods:**
public:
- add ( the function adds a specific block object to its chain, but not before calling the mine method on the object, after which it adds )
- get_blocks_data ( calls the get_data method on all blocks in the chain )
- is_valid ( goes through the entire blockchain and compares whether the previous hash of the next block is equal to the current hash of the current block )
- create_genesis
- create_transaction
- get_balance(address)
- get_last_block
- get_genesis_block
- get_height

## Transaction object
**Fields:**
- sender ( string of sender name )
- receiver ( string of receiver name )
- amount ( amount of deal )

**Methods:**
- serialize ( same essence as the block object )
- deserialize ( same essence as the block object )
- sign
- verify sign
- is_valid
- signature_len
- get_hash
- get_sender
- get_receiver
- get_amount

## Merkle Tree Object
**Fields:**
- string vector ( merkle tree )

**Methods:**
- get_tree_root
- is_empty
- build_tree

## Transaction signing example:
```cpp
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

    std::cout << (chain.is_valid() ? "Chain are valid" : "Chain aren`t valid") << std::endl;

    return 0;
}
```
**Output:**
```
Sender balance: -250.5
Receiver balance: 250.5
Miner balance: 100
Index: 0
Nonce: 0
Hash: Genesis Block
Previous hash: Genesis Block
Timestamp: 1408
Transactions count: 0
Merkle root hash: 

Index: 1
Nonce: 852
Hash: 000a90e11be60a607bd75cbb0f4ce049493565edec85ec17896b80f1cd1be104
Previous hash: Genesis Block
Timestamp: 1346666548
Transactions count: 1
Merkle root hash: ce0356d39a072e660598e59bca7c511d2ca852b15c6e1ca4c0955e2f52382273

Index: 2
Nonce: 1640
Hash: 000d5f867849eeea0f4a8f175c13f2d95c26f134d0d4d43fff275feb3df009b8
Previous hash: 000a90e11be60a607bd75cbb0f4ce049493565edec85ec17896b80f1cd1be104
Timestamp: 1346666556
Transactions count: 1
Merkle root hash: 6f5430c287309c1ac847de0885835e7d5d32c1eff9f77084978896a6e538fc6a

Chain are valid
```
