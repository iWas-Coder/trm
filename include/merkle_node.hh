#pragma once

#include <array>
#include <memory>

namespace trm::merkle {
  class MerkleNode {
    std::unique_ptr<MerkleNode> m_left;
    std::unique_ptr<MerkleNode> m_right;
    std::array<char, 32> m_hash;
    std::array<char, 32> computeHash(const std::array<char, 32> &left, const std::array<char, 32> &right);
  public:
    MerkleNode(const std::array<char, 32> &hash);
    MerkleNode(std::unique_ptr<MerkleNode> left, std::unique_ptr<MerkleNode> right);
    std::array<char, 32> hash(void) const { return m_hash; }
  };
}
