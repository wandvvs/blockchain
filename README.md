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
- [x] More type of encryption
- [ ] More types of mining
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
- serialize_transactions ( helper function, calls serialize on each transaction object )

## Blockchain object
**Fields:**
- chain ( all blocks which have been added )

**Methods:**
public:
- add ( the function adds a specific block object to its chain, but not before calling the mine method on the object, after which it adds )
- get_blocks_data ( calls the get_data method on all blocks in the chain )
- is_valid ( goes through the entire blockchain and compares whether the previous hash of the next block is equal to the current hash of the current block )

## Transaction object
**Fields:**
- sender ( string of sender name )
- receiver ( string of receiver name )
- amount ( amount of deal )

**Methods:**
- serialize ( same essence as the block object )
- deserialize ( same essence as the block object )
  
## Example
```cpp
#include "../includes/block.h"
#include "../includes/blockchain.h"
#include "../includes/transaction.h"

int main()
{
    Blockchain chain; /* Creating block chain */

    Transaction first_trans("Bob", "Alexa", 5416.53); /* Creating some transactions */
    Transaction second_trans("Tomas", "Robert", 13.2);

    std::vector<Transaction> transactions {first_trans, second_trans}; /* Transactions vector for BLOCK constructor */

    Block block("data", transactions); /* Create a block for chain */
    chain.add(block);
    block.get_data(); /* Get block data */

    nlohmann::json serialized = block.serialize(); /* Block serialize */
    std::cout << serialized.dump() << std::endl;

    Block deserialized; /* Block deserialized */
    deserialized.deserialize(serialized);
    deserialized.get_data();
}

```
**Output:**
```
Index: 0
Nonce: 523
Hash: 0006c7174fb1c8bf75ed4fcb04672554889da5968e50c59e4492596c26c257d7
Previous hash: 
Data: data
Timestamp: 4193473935
Transactions count: 2

{"data":"data","hash":"0006c7174fb1c8bf75ed4fcb04672554889da5968e50c59e4492596c26c257d7","index":0,"nonce":523,"previous hash":"","timestamp":4193473935,"transactions":[{"amount":5416.52978515625,"receiver":"Alexa","sender":"Bob"},{"amount":13.199999809265137,"receiver":"Robert","sender":"Tomas"}]}
Index: 0
Nonce: 523
Hash: 0006c7174fb1c8bf75ed4fcb04672554889da5968e50c59e4492596c26c257d7
Previous hash: 
Data: data
Timestamp: 4193473935
Transactions count: 2

```

