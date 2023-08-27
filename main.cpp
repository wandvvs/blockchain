#include "block.h"
#include "blockchain.h"

int main() {
    Blockchain chain;

    Block s("Data", 1);
    Block a("Text", 3);
    Block f("Xfff", 2);

    chain.add(s);
    chain.add(a);
    chain.add(f);
}
