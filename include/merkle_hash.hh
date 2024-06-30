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

#include <array>
#include <string>
#include <iomanip>
#include <openssl/sha.h>

namespace trm::merkle {
  enum class DigestType {
    SHA256 = SHA256_DIGEST_LENGTH
  };

  template <DigestType T>
  inline consteval size_t digesttype_to_value(void) {
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
    static Hash<T> zero(void);
    static Hash<T> compute(const std::string &input);
  };
}
