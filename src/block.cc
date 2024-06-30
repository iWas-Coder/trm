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

  template class Block<merkle::DigestType::SHA256>;
}
