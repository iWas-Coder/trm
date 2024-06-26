#include <algorithm>
#include <merkle_hash.hh>

namespace trm::merkle {
  template <DigestType T>
  Hash<T>::Hash(const std::string &digest_str) {
    size_t n = std::min(digest_str.size(), DigestTypeValue<T>());
    std::copy_n(digest_str.begin(), n, digest.begin());
  }

  template <DigestType T>
  Hash<T> Hash<T>::compute(const std::string &input) {
    unsigned char digest_out[DigestTypeValue<T>()];
    SHA256(reinterpret_cast<const unsigned char *>(input.data()), input.size(), digest_out);
    Digest<T> digest;
    std::copy(digest_out, digest_out + DigestTypeValue<T>(), digest.begin());
    return Hash<T> { std::string(digest.data(), digest.size()) };
  }

  template <DigestType T>
  Hash<T> Hash<T>::zero(void) {
    return Hash<T> { std::string(DigestTypeValue<T>(), '0') };
  }

  template class Hash<DigestType::SHA256>;
}
