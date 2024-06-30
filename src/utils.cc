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


#include <chrono>
#include <utils.hh>

namespace trm::utils {
  uint32_t unix_epoch_timestamp(void) {
    auto tp = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(tp);
    return static_cast<uint32_t>(t);
  }

  std::string unix_epoch_to_iso8601(uint32_t ts) {
    auto t = static_cast<time_t>(ts);
    tm *t_info = std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(t_info, "%Y-%m-%dT%H:%M:%S%z");
    return ss.str();
  }
}
