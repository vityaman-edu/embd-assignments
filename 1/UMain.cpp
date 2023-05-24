#include "BinaryInput.hpp"
#include "BinaryOutput.hpp"
#include "Hal.hpp"
#include "LedAnimation.hpp"
#include "STM.hpp"

auto umain() -> int {
  const auto DELAY = 500;
  const auto CODE = 0x05U;
  const auto NUMBER_SIZE = 4;
  const auto numberInput = STM::BinaryInput<NUMBER_SIZE>({
      STM::Switch(GPIO_PIN_12),
      STM::Switch(GPIO_PIN_10),
      STM::Switch(GPIO_PIN_8),
      STM::Switch(GPIO_PIN_4),
  });
  const auto numberOutput = STM::BinaryOutput<NUMBER_SIZE>({
      STM::Led(GPIO_PIN_6),
      STM::Led(GPIO_PIN_5),
      STM::Led(GPIO_PIN_4),
      STM::Led(GPIO_PIN_3),
  });
  const auto ANIMATION_STATES = 14;
  const auto ANIMATION_BITS = 8;
  const auto animationOutput = STM::BinaryOutput<ANIMATION_BITS>({
      STM::Led(GPIO_PIN_12),
      STM::Led(GPIO_PIN_11),
      STM::Led(GPIO_PIN_9),
      STM::Led(GPIO_PIN_8),
      STM::Led(GPIO_PIN_6),
      STM::Led(GPIO_PIN_5),
      STM::Led(GPIO_PIN_4),
      STM::Led(GPIO_PIN_3),
  });
  auto animation = STM::LedAnimation<ANIMATION_STATES, ANIMATION_BITS>({
      std::bitset<ANIMATION_BITS>("10000000"),
      std::bitset<ANIMATION_BITS>("11000000"),
      std::bitset<ANIMATION_BITS>("11100000"),
      std::bitset<ANIMATION_BITS>("11110000"),
      std::bitset<ANIMATION_BITS>("11111000"),
      std::bitset<ANIMATION_BITS>("11111100"),
      std::bitset<ANIMATION_BITS>("11111110"),
      std::bitset<ANIMATION_BITS>("11111111"),
      std::bitset<ANIMATION_BITS>("11111110"),
      std::bitset<ANIMATION_BITS>("11111100"),
      std::bitset<ANIMATION_BITS>("11111000"),
      std::bitset<ANIMATION_BITS>("11110000"),
      std::bitset<ANIMATION_BITS>("11100000"),
      std::bitset<ANIMATION_BITS>("11000000"),
  });
  while (true) {
    const auto number = numberInput.bits();
    if (number.to_ulong() == CODE) {
      animationOutput.set(animation.next());
      HAL::Delay(HAL::Milliseconds(DELAY));
    } else {
      animation.reset();
      animationOutput.clear();
      numberOutput.set(number);
    }
  }
  return 0;
}