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
