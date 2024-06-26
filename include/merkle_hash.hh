#pragma once

#include <array>
#include <string>
#include <openssl/sha.h>

namespace trm::merkle {
  enum class DigestType {
    SHA256 = SHA256_DIGEST_LENGTH
  };

  template <DigestType T>
  constexpr size_t DigestTypeValue(void) {
    return static_cast<size_t>(T);
  }

  template <DigestType T>
  using Digest = std::array<char, DigestTypeValue<T>()>;

  template <DigestType T>
  struct Hash {
    Digest<T> digest;
    Hash(const std::string &digest_str);
    static Hash<T> compute(const std::string &input);
    static Hash<T> zero(void);
  };
}
