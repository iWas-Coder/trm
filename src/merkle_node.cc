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
