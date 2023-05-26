#include "hal.h"
#include <array>

auto umain() -> int {
  const auto delay = 500;
  const auto N = 8;
  const auto leds_num = std::array<int, N>({
      GPIO_PIN_3,
      GPIO_PIN_4,
      GPIO_PIN_5,
      GPIO_PIN_6,
      GPIO_PIN_8,
      GPIO_PIN_9,
      GPIO_PIN_11,
      GPIO_PIN_12,
  });

  while (true) {
    // read nBTN
    const auto state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
    if (state == GPIO_PIN_RESET) {
      break;
    }
  }

  for (auto i = 0; i < N; i++) {
    HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_SET);
    HAL_Delay(delay);
    HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_RESET);
    HAL_Delay(delay);
  }

  return 0;
}