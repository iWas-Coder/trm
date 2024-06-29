#pragma once

#include <vector>
#include <merkle_hash.hh>

namespace trm::chain {
  template <merkle::DigestType T>
  class TX {
    uint32_t m_time;
    std::string m_file;
    merkle::Hash<T> m_hash;
  public:
    TX(const std::string &file);
    const merkle::Hash<T> &id(void) const { return m_hash; }
    const std::string &getFile(void) const { return m_file; }
  };
}
