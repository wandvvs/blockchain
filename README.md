# Blockchain
Blockchain implementation with C++

## Building
All functionality was tested on Arch Linux successfully

**Get a secp256k1 for signing algorithms**
```bash
git clone https://github.com/bitcoin-core/secp256k1.git
cd secp256k1
./autogen.s
./configure
make
```
**Install libraries**
```bash
sudo pacman -S openssl
sudo pacman -S nlohmann-json
```

```bash
cd build
cmake --build . --target run_client
./run_client
```

## TODO in (possible) future:
- [x] Proof Of Work (Mining)
- [x] Serialization
- [x] Transactions
- [x] Signing transactions
- [x] More type for hashing
- [x] Merkle trees
- [ ] Peer-to-peer network 
- [ ] Consensus algorithms

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

## Transaction signing example:
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

    chain.get_blocks_data();

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
Nonce: 234022
Hash: 00000ff4017eaf4d642fc3758c0cf168042d7605698dc114086a5b584560b48169efa9559a2b310d3da63e2aadda46b36ac6579877174e060140c3a85a3d7f80
Previous hash: Genesis Block
Timestamp: 914349399
Transactions count: 1
Merkle root hash: ce0356d39a072e660598e59bca7c511d2ca852b15c6e1ca4c0955e2f52382273

Index: 2
Nonce: 1145474
Hash: 00000fcfa299a09b9e0dd2d551dd3a3d9dc493de6404266770a79fdd34a74b27262276be052a57daa3087ba9037570348c15ed8a1740aa6789cf9066ca645207
Previous hash: 00000ff4017eaf4d642fc3758c0cf168042d7605698dc114086a5b584560b48169efa9559a2b310d3da63e2aadda46b36ac6579877174e060140c3a85a3d7f80
Timestamp: 914353405
Transactions count: 1
Merkle root hash: 6f5430c287309c1ac847de0885835e7d5d32c1eff9f77084978896a6e538fc6a
```
