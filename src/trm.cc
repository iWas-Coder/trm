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


#include <fstream>
#include <args.hh>
#include <iostream>
#include <block.hh>
#include <filesystem>
#include <unordered_set>

static constexpr auto digest_type { trm::merkle::DigestType::SHA256 };
static constexpr std::string filename { "blk.dat" };

static inline const trm::chain::Block<digest_type> create_block(const std::vector<std::string> &files, const trm::Args &args) {
  std::vector<trm::chain::TX<digest_type>> txns;
  std::unordered_set<std::string> dangerous_tgts {
    "/", "/*",
    "/bin", "/bin/",
    "/dev", "/dev/",
    "/etc", "/etc/",
    "/usr", "/usr/",
    "/var", "/var/"
  };
  for (const auto &i : files) {
    if (dangerous_tgts.contains(i))
      throw std::runtime_error { "It is forbidden to operate on `/` due to its destructive nature" };
    if (not std::filesystem::exists(i))
      throw std::runtime_error { "`" + i + "` does not exist" };
    if (std::filesystem::is_directory(i)) {
      if (not std::filesystem::is_empty(i) && not args.isEnabled('R') && not args.isEnabled('r'))
        throw std::runtime_error { "`" + i + "` is a non-empty directory (forgot to use the `-R/-r` flag?)" };
      if (std::filesystem::is_empty(i) && not args.isEnabled('d') && not args.isEnabled('R') && not args.isEnabled('r'))
        throw std::runtime_error { "`" + i + "` is an empty directory (forgot to use the `-d/-R/-r` flag?)" };
    }
    txns.emplace_back(trm::chain::TX<digest_type> {i});
  }
  // TODO: read file.
  // if there are blocks, get last one and put its hash as the previous hash of the block being created down there.
  // if there aren't, leave it as default (null hash with zeros).
  return trm::chain::Block<digest_type> {txns};
}

static inline void write_block(const trm::chain::Block<digest_type> &blk) {
  std::ofstream ofs { filename, std::ios::binary | std::ios::app };
  if (not ofs) throw std::runtime_error { "unable to open `" + filename + "` for writing" };
  ofs << blk;
}

int main(int argc, char **argv) {
  trm::Args args { argc, argv };
  const auto block { create_block(args.getFiles(), args) };
  if (args.isEnabled('v')) {
    args.printFlags();
    args.printFiles();
    std::cout << std::endl;
    block.print();
  }
  write_block(block);
}
