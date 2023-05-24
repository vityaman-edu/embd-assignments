#include "BinaryInput.hpp"
#include "BinaryOutput.hpp"
#include "Hal.hpp"
#include "LedAnimation.hpp"
#include "STM.hpp"
#include <bitset>

auto umain() -> int {
  const auto DELAY = 500;

  const auto CODE = 0x05U;

  const auto NUMBER_SIZE = 4;
  const auto input = STM::BinaryInput<NUMBER_SIZE>({
      STM::Switch(GPIO_PIN_12),
      STM::Switch(GPIO_PIN_10),
      STM::Switch(GPIO_PIN_8),
      STM::Switch(GPIO_PIN_4),
  });

  const auto OUT_BITS = 8;
  const auto output = STM::BinaryOutput<OUT_BITS>({
      STM::Led(GPIO_PIN_12),
      STM::Led(GPIO_PIN_11),
      STM::Led(GPIO_PIN_9),
      STM::Led(GPIO_PIN_8),
      STM::Led(GPIO_PIN_6),
      STM::Led(GPIO_PIN_5),
      STM::Led(GPIO_PIN_4),
      STM::Led(GPIO_PIN_3),
  });

  const auto ANIMATION_STATES = 14;
  auto animation = STM::LedAnimation<ANIMATION_STATES, OUT_BITS>({
      std::bitset<OUT_BITS>("10000000"),
      std::bitset<OUT_BITS>("11000000"),
      std::bitset<OUT_BITS>("11100000"),
      std::bitset<OUT_BITS>("11110000"),
      std::bitset<OUT_BITS>("11111000"),
      std::bitset<OUT_BITS>("11111100"),
      std::bitset<OUT_BITS>("11111110"),
      std::bitset<OUT_BITS>("11111111"),
      std::bitset<OUT_BITS>("11111110"),
      std::bitset<OUT_BITS>("11111100"),
      std::bitset<OUT_BITS>("11111000"),
      std::bitset<OUT_BITS>("11110000"),
      std::bitset<OUT_BITS>("11100000"),
      std::bitset<OUT_BITS>("11000000"),
  });

  const auto button = STM::Button(GPIO_PIN_15);

  const auto light = STM::TrafficLight(
      HAL::GPIO::Pin(HAL::GPIO::Port::D(), GPIO_PIN_13),
      HAL::GPIO::Pin(HAL::GPIO::Port::D(), GPIO_PIN_14),
      HAL::GPIO::Pin(HAL::GPIO::Port::D(), GPIO_PIN_15)
  );

  auto pause = false;
  while (true) {
    pause = pause != button.cliked();

    auto state = std::bitset<OUT_BITS>();

    const auto number = input.bits().to_ulong();
    if (!pause && number == CODE) {
      light.setColor(STM::TrafficLightColor::GREEN);
      state = animation.next();
      HAL::Delay(HAL::Milliseconds(DELAY));
    } else if (pause && number == CODE) {
      light.setColor(STM::TrafficLightColor::YELLOW);
      state = animation.current();
      HAL::Delay(HAL::Milliseconds(DELAY));
    } else {
      light.setColor(STM::TrafficLightColor::RED);
      animation.reset();
      state = number << 4U;
    }
    output.set(state);
  }

  return 0;
}