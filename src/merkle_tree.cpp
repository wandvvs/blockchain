// SPDX-License-Identifier: MIT
/*
 * Implementation file for merkle tree class
 *
 * Copyright (C) 2024 wandvvs
*/
#include "../includes/merkle_tree.h"
#include <cstddef>

void MerkleTree::build_tree(const std::vector<std::string>& hashes)
{
    merkle_tree.clear();
    merkle_tree = hashes;

    while(merkle_tree.size() > 1)
    {
        if (merkle_tree.size() % LEAF_COUNT != 0)
        {
            merkle_tree.push_back(merkle_tree.back());
        }

        std::vector<std::string> res;

        for(size_t i = 0; i < merkle_tree.size(); i += 2)
        {
            std::string one_leaf = crypto::sha::sha256(merkle_tree[i]);
            std::string second_leaf = crypto::sha::sha256(merkle_tree[i+1]);
            std::string hash = crypto::sha::sha256(one_leaf + second_leaf);

            res.push_back(hash);
        }
        merkle_tree = res;
    }
}

MerkleTree::MerkleTree(const std::vector<std::string>& hashes)
{
    build_tree(hashes);
}

const std::string MerkleTree::get_tree_root() const
{
    return merkle_tree.at(0);
}
