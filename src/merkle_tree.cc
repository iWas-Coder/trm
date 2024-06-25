#include <merkle_tree.hh>

namespace trm::merkle {
  std::unique_ptr<MerkleNode> MerkleTree::build(std::vector<std::unique_ptr<MerkleNode>> &nodes) const {
    if (nodes.size() == 1) return std::move(nodes.at(0));
    std::vector<std::unique_ptr<MerkleNode>> parents;
    for (size_t i = 0; i < nodes.size(); i += 2) {
      if (i + 1 < nodes.size()) parents.emplace_back(std::make_unique<MerkleNode>(std::move(nodes.at(i)), std::move(nodes.at(i + 1))));
      else parents.emplace_back(std::move(nodes.at(i)));
    }
    return build(parents);
  }

  void MerkleTree::insert(const std::array<char, 32> &hash) {
    m_leaves.emplace_back(std::make_unique<MerkleNode>(hash));
    if (m_leaves.size() > 1) m_root = build(m_leaves);
    else m_root = std::move(m_leaves.at(0));
  }

  std::array<char, 32> MerkleTree::root(void) const {
    if (m_root) return m_root->hash();
    else throw std::runtime_error("trm::MerkleTree::root -> the tree is empty");
  }
}
