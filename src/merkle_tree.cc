/*
 * GNU trm --- A transactional POSIX’s rm command
 * Copyright (C) 2024 Wasym A. Alonso
 *
 * This file is part of trm.
 *
 * trm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * trm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with trm.  If not, see <http://www.gnu.org/licenses/>.
 */


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
  Hash<T> Tree<T>::root(void) const {
    if (!m_root) throw std::runtime_error("trm::merkle::Tree::root() -> the tree is empty");
    return m_root->getHash();
  }

  template <DigestType T>
  std::string Tree<T>::root_str(void) const {
    return digest_to_string<T>(root().digest);
  }

  template class Tree<DigestType::SHA256>;
}
