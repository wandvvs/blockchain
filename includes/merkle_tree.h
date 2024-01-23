#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include "../utils/crypto.h"

class MerkleTree
{
private:
    std::vector<std::string> merkle_tree;

public:
    MerkleTree      (const std::vector<std::string>& hashes);
    void build_tree (const std::vector<std::string>& hashes);

    const std::string get_tree_root() const;

    bool is_empty() const { return merkle_tree.empty(); }
};

#endif
