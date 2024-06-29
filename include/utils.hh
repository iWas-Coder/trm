#pragma once

namespace trm::utils {
  uint32_t unix_epoch_timestamp(void);
  std::string unix_epoch_to_iso8601(uint32_t t);
}
