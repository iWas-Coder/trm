#include <iomanip>
#include <merkle_tree.hh>

namespace trm::merkle {
  template <DigestType T>
  std::unique_ptr<Node<T>> Tree<T>::build(std::vector<std::unique_ptr<Node<T>>> &nodes) const {
    if (nodes.size() == 1) return std::move(nodes.at(0));
    std::vector<std::unique_ptr<Node<T>>> parents;
    for (size_t i = 0; i < nodes.size(); i += 2) {
      if (i + 1 < nodes.size()) parents.emplace_back(std::make_unique<Node<T>>(std::move(nodes.at(i)), std::move(nodes.at(i + 1))));
      else parents.emplace_back(std::move(nodes.at(i)));
    }
    return build(parents);
  }

  template <DigestType T>
  void Tree<T>::insert(const Hash<T> &hash) {
    m_leaves.emplace_back(std::make_unique<Node<T>>(hash));
    if (m_leaves.size() > 1) m_root = build(m_leaves);
    else m_root = std::move(m_leaves.at(0));
  }

  template <DigestType T>
  std::string Tree<T>::root(void) const {
    if (!m_root) throw std::runtime_error("trm::merkle::Tree::root() -> the tree is empty");
    std::stringstream ss_hash;
    for (const auto &i : m_root->getHash().digest) ss_hash << std::hex << std::setw(2) << std::setfill('0') << (static_cast<unsigned int>(i) & 0xff);
    return ss_hash.str();
  }

  template class Tree<DigestType::SHA256>;
}
