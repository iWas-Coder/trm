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

#include <vector>
#include <merkle_node.hh>

namespace trm::merkle {
  template <DigestType T>
  class Tree {
    Node<T> *m_root;
    std::vector<Node<T> *> m_leaves;
    Node<T> *build(std::vector<Node<T> *> &nodes) const;
  public:
    ~Tree(void);
    void insert(const Hash<T> &hash);
    Hash<T> root(void) const;
    std::string root_str(void) const;
  };
}
