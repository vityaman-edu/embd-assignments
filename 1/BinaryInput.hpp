#pragma once

#include <bitset>
#include <array>
#include "STM.hpp"

namespace STM {

template <std::size_t N>
class BinaryInput {
public:
  explicit BinaryInput(const std::array<Switch, N>& pins) //
      : switches(pins) {}

  auto bits() const -> std::bitset<N> {
    auto bits = std::bitset<N>();
    for (std::size_t i = 0; i < N; i++) {
      const auto sw = switches[i];
      if (sw.isOn()) {
        bits.set(i);
      }
    }
    return bits;
  }

private:
  std::array<Switch, N> switches;
};

} // namespace STM