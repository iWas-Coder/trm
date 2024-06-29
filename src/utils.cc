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
