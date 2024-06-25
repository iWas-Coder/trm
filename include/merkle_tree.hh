#pragma once

#include <vector>
#include <merkle_node.hh>

namespace trm::merkle {
  template <DigestType T>
  class Tree {
    std::unique_ptr<Node<T>> m_root;
    std::vector<std::unique_ptr<Node<T>>> m_leaves;
    std::unique_ptr<Node<T>> build(std::vector<std::unique_ptr<Node<T>>> &nodes) const;
  public:
    Tree(void) = default;
    void insert(const Hash<T> &hash);
    std::string root(void) const;
  };
}
