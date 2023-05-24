#include "BinaryInput.hpp"
#include "BinaryOutput.hpp"
#include "Hal.hpp"
#include "STM.hpp"

auto umain() -> int {
  const auto N = 4;
  const auto input = STM::BinaryInput<N>({
      STM::Switch(GPIO_PIN_12),
      STM::Switch(GPIO_PIN_10),
      STM::Switch(GPIO_PIN_8),
      STM::Switch(GPIO_PIN_4),
  });
  const auto output = STM::BinaryOutput<N>({
      STM::Led(GPIO_PIN_6),
      STM::Led(GPIO_PIN_5),
      STM::Led(GPIO_PIN_4),
      STM::Led(GPIO_PIN_3),
  });
  while (true) {
    output.set(input.bits());
  }
  return 0;
}