#include <openssl/sha.h>
#include <merkle_node.hh>

namespace trm::merkle {
  std::array<char, 32> MerkleNode::computeHash(const std::array<char, 32> &left, const std::array<char, 32> &right) {
    std::array<char, 2 * 32> concat;
    std::copy(left.begin(), left.end(), concat.begin());
    std::copy(right.begin(), right.end(), concat.begin() + 32);
    unsigned char hash_out[32];
    SHA256(reinterpret_cast<const unsigned char *>(concat.data()), concat.size(), hash_out);
    std::array<char, 32> hash;
    std::copy(hash_out, hash_out + 32, hash.begin());
    return hash;
  }

  MerkleNode::MerkleNode(const std::array<char, 32> &hash) : m_left{nullptr}, m_right{nullptr}, m_hash{hash} {}

  MerkleNode::MerkleNode(std::unique_ptr<MerkleNode> left, std::unique_ptr<MerkleNode> right)
    : m_left{std::move(left)}, m_right{std::move(right)}, m_hash{computeHash(this->m_left->hash(), this->m_right->hash())} {}
}
