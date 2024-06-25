#pragma once

#include <vector>
#include <merkle_node.hh>

namespace trm::merkle {
  class MerkleTree {
    std::unique_ptr<MerkleNode> m_root;
    std::vector<std::unique_ptr<MerkleNode>> m_leaves;
    std::unique_ptr<MerkleNode> build(std::vector<std::unique_ptr<MerkleNode>> &nodes) const;
  public:
    MerkleTree(void) = default;
    void insert(const std::array<char, 32> &hash);
    std::array<char, 32> root(void) const;
  };
}
