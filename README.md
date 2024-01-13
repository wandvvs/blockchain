# Blockchain
simple blockchain implementation with c++

## Building

### System Requirements
There are several system requirements including clang.

#### Arch
```bash
sudo pacman -S openssl
sudo pacman -S nlohmann-json
```

### Running
```bash
cd build
cmake ..
make
./run
```

## TODO in (possible) future:
- [x] Proof Of Work (Mining)
- [x] Serialization
- [x] Transactions
- [x] Signing transactions
- [x] More type for hashing
- [ ] More types for mining
- [ ] Consensus algorithms
- [ ] Peer-to-peer network
- [ ] Merkle trees
- [ ] Excellent security and code fixes

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
- sha256 ( generate hash based on input data )
- mine ( starts looking for a hash in which the number of zeros at the beginning is the same as the number of constants DIFFICULT  )

- get_data ( it will print all information about this block )
- get_transactions ( it will print all transaction that had been pushed to block )
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

## Example
```cpp
#include "../includes/blockchain.h"

int main() {
    Blockchain chain;

    RSA* sender_private_key = generate_private_key();
    RSA* sender_public_key = generate_public_key(sender_private_key);

    RSA* miner_private_key = generate_private_key();

    RSA* receiver_private_key = generate_private_key();
    RSA* receiver_public_key = generate_public_key(receiver_private_key);

    Transaction test {"Sender", "Receiver", 250.5};

    test.sign(sender_private_key);
    
    if(test.verify(sender_public_key)) {
        chain.create_transaction(test, sender_private_key);
        chain.mine_pending_transactions("wand", miner_private_key);

        std::cout << "Sender balance: " << chain.get_balance("Sender") << std::endl;
        std::cout << "Receiver balance: " << chain.get_balance("Receiver") << std::endl;
    }
    else {
        std::cerr << "Failed to sign transaction" << std::endl;
    }

    chain.mine_pending_transactions("wand", miner_private_key);

    std::cout << "Miner balance: " << chain.get_balance("wand") << std::endl;

    return 0;
}
```
**Output:**
```
Sender balance: -250.5
Receiver balance: 250.5
Miner balance: 100
```

