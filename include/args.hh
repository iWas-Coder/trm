#pragma once

#include <unordered_map>

namespace trm {
  class Args {
    std::unordered_map<char, bool> m_flags;
  public:
    Args(int argc, char **argv);
  };
}
