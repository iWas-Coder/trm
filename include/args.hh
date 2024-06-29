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
    const std::vector<std::string> &getFiles(void) const { return m_files; }
    void printFlags(void) const;
    void printFiles(void) const;
  };
}
