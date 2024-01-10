# Get started with blockchain

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

## Block object
**Fields:**
- data ( contains some string )
- hash ( hash outstanding after mining given difficulty
- prevhash ( previous block hash )
- index ( unique block identifier )
- nonce ( number of attempts to generate a valid hash )
- timestamp ( date and time when block has been successfully added to chain )

**Methods:**
- sha256 ( generate hash based on input data )
- mine ( start looking for a hash that will have as many zeros at the beginning as we passed it to the parameters )
- get_data ( it will print all information about this block )

## Blockchain object
**Fields:**
- chain ( all blocks which have been added )

**Methods:**
- add ( the function adds a specific block object to its chain, but not before calling the mine method on the object, after which it adds )
- get_blocks_data ( calls the get_data method on all blocks in the chain )

## Example
```cpp
#include <iostream>
#include "../includes/block.h"
#include "../includes/blockchain.h"

int main()
{
    Blockchain chain;

    Block first("hello");
    Block second("test");
    
    chain.add(first, 4);
    chain.add(second, 6);

    chain.get_blocks_data();
}
```
**Output:**
``Index: 0
Nonce: 9133
Hash: 00000ee010fe3516efdb3456102216e76ecdb2bd48a11670b1b27ad5ec28fb54
Previous hash: 
Data: hello
Timestamp: 4103741549


Index: 1
Nonce: 3681803
Hash: 000000e4e62b2f779f14972fdd7569a3c12f3a7ce2b97b053b570003b07034b0
Previous hash: 00000ee010fe3516efdb3456102216e76ecdb2bd48a11670b1b27ad5ec28fb54
Data: test
Timestamp: 4103749316
```

