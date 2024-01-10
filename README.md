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
** Fields:
- data ( contains some string )
- hash ( hash outstanding after mining given difficulty
- prevhash ( previous block hash )
- index ( unique block identifier )
- nonce ( number of attempts to generate a valid hash )
- timestamp ( date and time when block has been successfully added to chain )

** Methods:
- sha256 ( generate hash based on input data )
- mine ( start looking for a hash that will have as many zeros at the beginning as we passed it to the parameters )
- get_data ( it will print all information about this block )

## Blockchain object
** Fields:
- chain ( all blocks which have been added )

** Methods:
- add ( the function adds a specific block object to its chain, but not before calling the mine method on the object, after which it adds )
- get_blocks_data ( calls the get_data method on all blocks in the chain )
