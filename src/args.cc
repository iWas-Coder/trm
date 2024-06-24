#include <string>
#include <args.hh>
#include <unistd.h>
#include <iostream>

// usage: trm [-dfiPRrv] file ...

static constexpr std::string flags { "dfiPRrv" };

namespace trm {
  Args::Args(int argc, char **argv) {
    for (char c : flags) m_flags[c] = false;
    int c;
    while ((c = getopt(argc, argv, flags.c_str())) != -1) {
      try { m_flags.at(c) = true; }
      catch (const std::out_of_range &e) {
        std::cerr << "usage: " << argv[0] << " [-dfiPRrv] file ..." << std::endl;
        exit(1);
      }
    }
    // Print parsed flags
    for (const auto &i : m_flags) {
      std::cout << i.first << ": " << std::boolalpha << i.second << std::endl;
    }
  }
}
