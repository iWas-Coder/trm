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

extern "C" {
#include <unistd.h>
}

static constexpr std::string flags { "dfiPRrv" };
static constexpr std::string commit_flag { "--commit" };
static constexpr std::string rollback_flag { "--rollback" };

static inline void error(const char *prog_name) {
  std::cerr << "usage: " << prog_name << " [-" << flags << "] file ..." << std::endl;
  std::cerr << "       " << prog_name << " {" << commit_flag << "|" << rollback_flag << "[=1]}" << std::endl;
  exit(1);
}

namespace trm {
  Args::Args(int argc, char **argv) {
    // TODO: check if only 1 arg provided, and is `--commit`.
    // special flag to make effective all removals made with this tool.
    // basically, delete all blockchain data and ACTUALLY remove from disk all associated files.
    if (argc == 2 && argv[1] == commit_flag) {
      std::cout << "WARNING: `" << argv[1] << "` feature not yet implemented" << std::endl;
      exit(0);
    }
    // TODO: check if only 1 arg provided, and is `--rollback[=1]`.
    // special flag to delete the last block (the number can be changed with the `=` sign) and
    // bring back the associated files to their original location.
    if (argc == 2 && argv[1] == rollback_flag) {
      std::cout << "WARNING: `" << argv[1] << "` feature not yet implemented" << std::endl;
      exit(0);
    }
    for (char c : flags) m_flags[c] = false;
    int c;
    while ((c = getopt(argc, argv, flags.c_str())) != -1) {
      try { m_flags.at(c) = true; }
      catch (const std::out_of_range &e) { error(argv[0]); }
    }
    for (int i = optind; i < argc; ++i) m_files.emplace_back(argv[i]);
    if (m_files.empty()) { error(argv[0]); }
  }

  bool Args::isEnabled(char flag) const {
    try { return m_flags.at(flag); }
    catch (const std::out_of_range &e) { return false; }
  }

  void Args::printFlags(void) const {
    std::cout << "Flags:" << std::endl;
    for (const auto &i : m_flags) std::cout << "  " << i.first << ": " << std::boolalpha << i.second << std::endl;
  }

  void Args::printFiles(void) const {
    std::cout << "Files:" << std::endl;
    for (const auto &i : m_files) std::cout << "  - " << i << std::endl;
  }
}
