#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace trm {
  class Args {
    std::unordered_map<char, bool> m_flags;
    std::vector<std::string> m_files;
  public:
    Args(int argc, char **argv);
    void printFlags(void) const;
    void printFiles(void) const;
  };
}
