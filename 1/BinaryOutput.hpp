#pragma once

#include "STM.hpp"
#include <array>
#include <bitset>
#include <cstddef>

namespace STM {

template <std::size_t N>
class BinaryOutput {
public:
  explicit BinaryOutput(const std::array<Led, N>& leds) : leds(leds) {}

  auto set(const std::bitset<N>& bits) const -> void {
    for (std::size_t i = 0; i < N; i++) {
      const auto& led = leds[i];
      if (bits.test(i)) {
        led.turnOn();
      } else {
        led.turnOff();
      }
    }
  }

private:
  std::array<Led, N> leds;
};

}