#pragma once

#include <array>
#include <bitset>
#include <cstddef>

namespace STM {

template <std::size_t Nstates, std::size_t Nbits>
class LedAnimation {
public:
  explicit LedAnimation(const std::array<std::bitset<Nbits>, Nstates>& states)
      : states(states) {}

  auto next() -> std::bitset<Nbits> {
    const auto state = current();
    current_state = (current_state + 1) % Nstates;
    return state;
  }

  auto current() -> std::bitset<Nbits> { //
    return states[current_state];
  }

  auto reset() -> void { //
    current_state = 0;
  }

private:
  std::size_t current_state = 0;
  std::array<std::bitset<Nbits>, Nstates> states;
};

}