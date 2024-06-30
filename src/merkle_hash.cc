#include <algorithm>
#include <merkle_hash.hh>

namespace trm::merkle {
  template <DigestType T>
  Hash<T>::Hash(const std::string &digest_str) {
    size_t n = std::min(digest_str.size(), digesttype_to_value<T>());
    std::copy_n(digest_str.begin(), n, digest.begin());
  }

  template <DigestType T>
  Hash<T> Hash<T>::zero(void) {
    return Hash<T> { std::string(digesttype_to_value<T>(), '\0') };
  }

  template <>
  Hash<DigestType::SHA256> Hash<DigestType::SHA256>::compute(const std::string &input) {
    constexpr auto digest_len { digesttype_to_value<DigestType::SHA256>() };
    unsigned char digest_out[digest_len];
    SHA256(reinterpret_cast<const unsigned char *>(input.data()), input.size(), digest_out);
    Digest<DigestType::SHA256> digest;
    std::copy(digest_out, digest_out + digest_len, digest.begin());
    return Hash<DigestType::SHA256> { std::string(digest.data(), digest.size()) };
  }

  template struct Hash<DigestType::SHA256>;
}
