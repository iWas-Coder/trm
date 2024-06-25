#pragma once

#include <array>
#include <memory>
#include <merkle_hash.hh>

namespace trm::merkle {
  template <DigestType T>
  class Node {
    std::unique_ptr<Node<T>> m_left;
    std::unique_ptr<Node<T>> m_right;
    Hash<T> m_hash;
    Hash<T> merge(const Hash<T> &left, const Hash<T> &right);
  public:
    Node(const Hash<T> &hash);
    Node(std::unique_ptr<Node<T>> left, std::unique_ptr<Node<T>> right);
    const Hash<T> &getHash(void) const { return m_hash; }
  };
}
