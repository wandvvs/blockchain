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
- data ( contains some string )
- hash ( hash outstanding after mining given difficulty
- prevhash ( previous block hash )
- index ( unique block identifier )
- nonce ( number of attempts to generate a valid hash )
- timestamp ( date and time when block has been successfully added to chain )
