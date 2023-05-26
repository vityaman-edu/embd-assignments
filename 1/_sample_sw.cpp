#include "hal.h"
#include <array>

auto umain() -> int {
  const auto leds_num = std::array<int, 8>({
      GPIO_PIN_3,
      GPIO_PIN_4,
      GPIO_PIN_5,
      GPIO_PIN_6,
      GPIO_PIN_8,
      GPIO_PIN_9,
      GPIO_PIN_11,
      GPIO_PIN_12,
  });
  const auto N = 4;
  const auto sw_num = std::array<int, 4>({
      GPIO_PIN_4,
      GPIO_PIN_8,
      GPIO_PIN_10,
      GPIO_PIN_12,
  });
  while (true) {
    for (auto i = 0; i < N; i++) {
      const auto state = HAL_GPIO_ReadPin(GPIOE, sw_num[i]);
      HAL_GPIO_WritePin(GPIOD, leds_num[i], state);
    }
  }
  return 0;
}