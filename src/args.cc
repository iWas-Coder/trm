#include <args.hh>
#include <unistd.h>
#include <iostream>

static constexpr std::string flags { "dfiPRrv" };

static inline void error(const char *prog_name) {
  std::cerr << "usage: " << prog_name << " [-" << flags << "] file ..." << std::endl;
  exit(1);
}

namespace trm {
  Args::Args(int argc, char **argv) {
    for (char c : flags) m_flags[c] = false;
    int c;
    while ((c = getopt(argc, argv, flags.c_str())) != -1) {
      try { m_flags.at(c) = true; }
      catch (const std::out_of_range &e) { error(argv[0]); }
    }
    for (int i = optind; i < argc; ++i) m_files.emplace_back(argv[i]);
    if (m_files.empty()) { error(argv[0]); }
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
