#pragma once

#include <array>
#include <string>
#include <iomanip>
#include <openssl/sha.h>

namespace trm::merkle {
  enum class DigestType {
    SHA256 = SHA256_DIGEST_LENGTH
  };

  template <DigestType T>
  consteval size_t digesttype_to_value(void) {
    return static_cast<size_t>(T);
  }

  template <DigestType T>
  using Digest = std::array<char, digesttype_to_value<T>()>;

  template <DigestType T>
  inline std::string digest_to_string(Digest<T> digest) {
    std::stringstream ss;
    for (const auto &i : digest) ss << std::hex << std::setw(2) << std::setfill('0') << (static_cast<unsigned int>(i) & 0xff);
    return ss.str();
  }

  template <DigestType T>
  struct Hash {
    Digest<T> digest;
    Hash(void) = default;
    Hash(const std::string &digest_str);
    static Hash<T> compute(const std::string &input);
    static Hash<T> zero(void);
  };
}
