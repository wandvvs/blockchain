# The simplest blokchain

## Install OpenSSL
```bash
sudo pacman -S openssl
```
## Compile
```bash
cd build
cmake ..
make
./run
```

## TODO on (possible) future:
- [x] Mining
- [ ] Serialization
- [ ] Transactions
- [ ] More types of mining
- [ ] More type of encryption
- [ ] Consensus algorithms
- [ ] Peer-to-peer network
- [ ] Merkle trees
- [ ] Excellent security and code fixes

## Block object
**Fields:**
private:
- data ( contains some string )
- hash ( hash outstanding after mining given difficulty
- prevhash ( previous block hash )
- index ( unique block identifier )
- nonce ( number of attempts to generate a valid hash )
- timestamp ( date and time when block has been successfully added to chain )

**Methods:**
private:
- sha256 ( generate hash based on input data )
- mine ( starts looking for a hash in which the number of zeros at the beginning is the same as the number of constants DIFFICULT  )

public:
- get_data ( it will print all information about this block )

## Blockchain object
**Fields:**
private:
- chain ( all blocks which have been added )

**Methods:**
public:
- add ( the function adds a specific block object to its chain, but not before calling the mine method on the object, after which it adds )
- get_blocks_data ( calls the get_data method on all blocks in the chain )
- is_valid ( goes through the entire blockchain and compares whether the previous hash of the next block is equal to the current hash of the current block )
  
## Example
```cpp
#include "../includes/block.h"
#include "../includes/blockchain.h"

int main()
{
    Blockchain chain;

    Block first("hello");
    Block second("test");

    chain.add(first);
    chain.add(second);

    chain.get_blocks_data();
    
    std::cout << chain.is_valid() << std::endl;
}

```
**Output:**
```
Index: 0
Nonce: 2835
Hash: 0007881351a9319e62d1873f6539bc656ac8eacf0dcbc6681bb912ae16ad2ebf
Previous hash: 
Data: hello
Timestamp: 4112327928


Index: 1
Nonce: 6343
Hash: 0004861729598c801c770087773453fe10f16346d4d3126bda41acc5b339b0e8
Previous hash: 0007881351a9319e62d1873f6539bc656ac8eacf0dcbc6681bb912ae16ad2ebf
Data: test
Timestamp: 4112327943


1 // std::cout << chain.is_valid() << std::endl; (CHAIN IS VALID)

```

