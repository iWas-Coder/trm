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
    inline const Hash<T> &getHash(void) const { return m_hash; }
  };
}
