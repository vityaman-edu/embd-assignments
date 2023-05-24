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

  // TODO: here it is possible to add some
  // bitset cache to reduce IO operations as
  // we don't need to call write when it has been 
  // already set
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

  auto clear() const -> void {
    for (const auto& led : leds) {
      led.turnOff();
    }
  }

private:
  std::array<Led, N> leds;
};

}