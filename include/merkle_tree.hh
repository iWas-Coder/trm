#pragma once

#include <vector>
#include <merkle_node.hh>

namespace trm::merkle {
  template <DigestType T>
  class Tree {
    Node<T> *m_root;
    std::vector<Node<T> *> m_leaves;
    Node<T> *build(std::vector<Node<T> *> &nodes) const;
  public:
    Tree(void) = default;
    ~Tree(void);
    void insert(const Hash<T> &hash);
    std::string root(void) const;
  };
}
