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
