#pragma once

#include <array>
#include <memory>
#include <merkle_hash.hh>

namespace trm::merkle {
  template <DigestType T>
  class Node {
    Node<T> *m_left;
    Node<T> *m_right;
    Hash<T> m_hash;
    Hash<T> merge(const Hash<T> &left, const Hash<T> &right);
  public:
    Node(const Hash<T> &hash);
    Node(Node<T> *left, Node<T> *right);
    const Hash<T> &getHash(void) const { return m_hash; }
  };
}
