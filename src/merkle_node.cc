#include <merkle_node.hh>

namespace trm::merkle {
  template <DigestType T>
  Hash<T> Node<T>::merge(const Hash<T> &left, const Hash<T> &right) {
    std::string concat;
    concat.insert(concat.end(), left.digest.begin(), left.digest.end());
    concat.insert(concat.end(), right.digest.begin(), right.digest.end());
    return Hash<T>::compute(concat);
  }

  template <DigestType T>
  Node<T>::Node(const Hash<T> &hash) : m_left{nullptr}, m_right{nullptr}, m_hash{hash} {}

  template <DigestType T>
  Node<T>::Node(Node<T> *left, Node<T> *right)
    : m_left{left}, m_right{right}, m_hash{merge(this->m_left->m_hash, this->m_right->m_hash)} {}

  template class Node<DigestType::SHA256>;
}
