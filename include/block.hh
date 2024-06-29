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
