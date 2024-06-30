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


#include <args.hh>
#include <iostream>
#include <block.hh>

int main(int argc, char **argv) {
  trm::Args args { argc, argv };
  args.printFlags();
  args.printFiles();

  std::vector<trm::chain::TX<trm::merkle::DigestType::SHA256>> txns;
  for (const auto &i : args.getFiles()) txns.emplace_back(trm::chain::TX<trm::merkle::DigestType::SHA256> {i});
  trm::chain::Block<trm::merkle::DigestType::SHA256> block {txns};

  std::cout << std::endl;
  block.print();

  return 0;
}
