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

constexpr auto digest_type { trm::merkle::DigestType::SHA256 };

static inline const trm::chain::Block<digest_type> create_block(const std::vector<std::string> &files) {
  std::vector<trm::chain::TX<digest_type>> txns;
  for (const auto &i : files) txns.emplace_back(trm::chain::TX<digest_type> {i});
  return trm::chain::Block<digest_type> {txns};
}

int main(int argc, char **argv) {
  trm::Args args { argc, argv };
  args.printFlags();
  args.printFiles();

  std::cout << std::endl;

  const auto block { create_block(args.getFiles()) };
  block.print();

  std::ofstream ofs { "blk.dat", std::ios::binary | std::ios::app };
  if (!ofs) {
    std::cerr << "ERROR: unable to open file for writing (`blk.dat`)" << std::endl;
    return 1;
  }
  ofs << block;
  ofs.close();

  return 0;
}
