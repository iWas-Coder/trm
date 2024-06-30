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

#include <tx.hh>
#include <vector>
#include <merkle_hash.hh>

namespace trm::chain {
  template <merkle::DigestType T>
  struct BlockHeader {
    uint32_t timestamp {0};
    merkle::Hash<T> hash { merkle::Hash<T>::zero() };
    merkle::Hash<T> prevHash { merkle::Hash<T>::zero() };
    merkle::Hash<T> merkleRoot { merkle::Hash<T>::zero() };
  };

  template <merkle::DigestType T>
  class Block {
    BlockHeader<T> m_header;
    std::vector<TX<T>> m_txns;
  public:
    Block(const std::vector<TX<T>> &txns, const merkle::Hash<T> &prev = merkle::Hash<T>::zero());
    const merkle::Hash<T> &id(void) const { return m_header.hash; }
    const merkle::Hash<T> &prev(void) const { return m_header.prevHash; }
    void print(void) const;
  };
}
