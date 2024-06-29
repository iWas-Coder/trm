#include <tx.hh>
#include <sstream>
#include <utils.hh>

namespace trm::chain {
  template <merkle::DigestType T>
  TX<T>::TX(const std::string &file) : m_time{utils::unix_epoch_timestamp()}, m_file{file} {
    std::stringstream ss;
    ss << m_time << std::endl << m_file;
    m_hash = merkle::Hash<T>::compute(ss.str());
  }

  template class TX<merkle::DigestType::SHA256>;
}
