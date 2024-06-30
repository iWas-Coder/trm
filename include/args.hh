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
