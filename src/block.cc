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


#include <sstream>
#include <iostream>
#include <block.hh>
#include <utils.hh>
#include <merkle_tree.hh>

namespace trm::chain {
  template <merkle::DigestType T>
  Block<T>::Block(const std::vector<TX<T>> &txns, const merkle::Hash<T> &prev) : m_txns{txns} {
    m_header.prevHash = prev;
    m_header.timestamp = utils::unix_epoch_timestamp();
    merkle::Tree<T> txns_tree;
    for (const auto &i : m_txns) txns_tree.insert(i.id());
    m_header.merkleRoot = txns_tree.root();
    std::stringstream ss;
    ss << m_header.timestamp << std::endl << merkle::digest_to_string<T>(m_header.prevHash.digest) << std::endl << merkle::digest_to_string<T>(m_header.merkleRoot.digest);
    m_header.hash = merkle::Hash<T>::compute(ss.str());
  }

  template <merkle::DigestType T>
  void Block<T>::print(void) const {
    std::cout << "Block's Header:" << std::endl;
    std::cout << "  Hash:           " << merkle::digest_to_string<T>(m_header.hash.digest) << std::endl;
    std::cout << "  Previous Block: " << merkle::digest_to_string<T>(m_header.prevHash.digest) << std::endl;
    std::cout << "  Merkle Root:    " << merkle::digest_to_string<T>(m_header.merkleRoot.digest) << std::endl;
    std::cout << "  Timestamp:      " << utils::unix_epoch_to_iso8601(m_header.timestamp) << std::endl;
    std::cout << "Block's Transactions:" << std::endl;
    for (const auto &i : m_txns) {
      std::cout << "  - Hash: " << merkle::digest_to_string<T>(i.id().digest) << std::endl;
      std::cout << "    File: " << i.getFile() << std::endl;
    }
  }

  template <merkle::DigestType T>
  std::ostream &operator<<(std::ostream &os, const Block<T> &blk) {
    os.write(reinterpret_cast<const char *>(&blk.m_header.hash.digest), sizeof(blk.m_header.hash.digest));
    os.write(reinterpret_cast<const char *>(&blk.m_header.prevHash.digest), sizeof(blk.m_header.prevHash.digest));
    os.write(reinterpret_cast<const char *>(&blk.m_header.merkleRoot.digest), sizeof(blk.m_header.merkleRoot.digest));
    os.write(reinterpret_cast<const char *>(&blk.m_header.timestamp), sizeof(blk.m_header.timestamp));
    for (const auto &i : blk.m_txns) {
      os.write(reinterpret_cast<const char *>(&i.id().digest), sizeof(i.id().digest));
      os.write(reinterpret_cast<const char *>(&i.getFile()), sizeof(i.getFile()));
    }
    return os;
  }

  template class Block<merkle::DigestType::SHA256>;
  template std::ostream &operator<<(std::ostream &os, const Block<merkle::DigestType::SHA256> &blk);
}
