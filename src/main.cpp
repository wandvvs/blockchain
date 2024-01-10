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
