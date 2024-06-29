#include <iomanip>
#include <merkle_tree.hh>

template <trm::merkle::DigestType T>
static std::vector<trm::merkle::Node<T> *> inter;

namespace trm::merkle {
  template <DigestType T>
  Node<T> * Tree<T>::build(std::vector<Node<T> *> &nodes) const {
    if (nodes.size() == 1) return nodes.at(0);
    std::vector<Node<T> *> parents;
    for (size_t i = 0; i < nodes.size(); i += 2) {
      if (i + 1 < nodes.size()) {
        Node<T> *n = new Node<T>(nodes.at(i), nodes.at(i + 1));
        parents.emplace_back(n);
        inter<T>.emplace_back(n);
      }
      else parents.emplace_back(nodes.at(i));
    }
    return build(parents);
  }

  template <DigestType T>
  Tree<T>::~Tree(void) {
    for (const auto &i : m_leaves) delete i;
    for (const auto &i : inter<T>) delete i;
  }

  template <DigestType T>
  void Tree<T>::insert(const Hash<T> &hash) {
    m_leaves.emplace_back(new Node<T>(hash));
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
