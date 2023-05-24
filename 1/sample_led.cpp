#include "Hal.hpp"
#include <array>

auto umain() -> int {
  const auto DELAY = 500;
  const auto N = 8;
  const auto PORT = HAL::GPIO::Port::D();
  const auto leds = std::array<HAL::GPIO::Pin, N>({
      HAL::GPIO::Pin(PORT, GPIO_PIN_3),
      HAL::GPIO::Pin(PORT, GPIO_PIN_4),
      HAL::GPIO::Pin(PORT, GPIO_PIN_5),
      HAL::GPIO::Pin(PORT, GPIO_PIN_6),
      HAL::GPIO::Pin(PORT, GPIO_PIN_8),
      HAL::GPIO::Pin(PORT, GPIO_PIN_9),
      HAL::GPIO::Pin(PORT, GPIO_PIN_11),
      HAL::GPIO::Pin(PORT, GPIO_PIN_12),
  });
  for (const auto led : leds) {
    led.write(HAL::GPIO::PinState::SET);
    HAL::Delay(HAL::Milliseconds(DELAY));
    led.write(HAL::GPIO::PinState::RESET);
    HAL::Delay(HAL::Milliseconds(DELAY));
  }
  return 0;
}