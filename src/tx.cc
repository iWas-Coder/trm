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


#include <tx.hh>
#include <sstream>
#include <utils.hh>
#include <filesystem>

namespace trm::chain {
  template <merkle::DigestType T>
  TX<T>::TX(const std::string &file) : m_time{utils::unix_epoch_timestamp()}, m_file{file} {
    if (not std::filesystem::exists(m_file)) throw std::runtime_error { "`" + m_file + "` does not exist" };
    std::stringstream ss;
    ss << m_time << std::endl << m_file;
    m_hash = merkle::Hash<T>::compute(ss.str());
  }

  template class TX<merkle::DigestType::SHA256>;
}
