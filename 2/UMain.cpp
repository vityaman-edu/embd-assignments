#include "BinaryInput.hpp"
#include "BinaryOutput.hpp"
#include "Hal.hpp"
#include "LedAnimation.hpp"
#include "STM.hpp"
#include "hal.h"
#include <bitset>

const auto DELAY_BASE = 500;
const auto DELAY_T = 150;

const auto OUT_BITS = 8;
const auto output = // NOLINT
    STM::BinaryOutput<OUT_BITS>({
        STM::Led(GPIO_PIN_12),
        STM::Led(GPIO_PIN_11),
        STM::Led(GPIO_PIN_9),
        STM::Led(GPIO_PIN_8),
        STM::Led(GPIO_PIN_6),
        STM::Led(GPIO_PIN_5),
        STM::Led(GPIO_PIN_4),
        STM::Led(GPIO_PIN_3),
    });

const auto ANIMATION_STATES = 12;
auto animation = // NOLINT
    STM::LedAnimation<ANIMATION_STATES, OUT_BITS>({
        std::bitset<OUT_BITS>("00000011"), // 0
        std::bitset<OUT_BITS>("00000110"), // 1
        std::bitset<OUT_BITS>("00001100"), // 2
        std::bitset<OUT_BITS>("00011000"), // 3
        std::bitset<OUT_BITS>("00110000"), // 4
        std::bitset<OUT_BITS>("01100000"), // 5
        std::bitset<OUT_BITS>("11000000"), // 6
        std::bitset<OUT_BITS>("01100000"), // 7
        std::bitset<OUT_BITS>("00110000"), // 8
        std::bitset<OUT_BITS>("00011000"), // 9
        std::bitset<OUT_BITS>("00001100"), // 10
        std::bitset<OUT_BITS>("00000110"), // 11
    });

const auto INPUT_SIZE = 4;
const auto input = // NOLINT
    STM::BinaryInput<INPUT_SIZE>({
        STM::Switch(GPIO_PIN_12),
        STM::Switch(GPIO_PIN_10),
        STM::Switch(GPIO_PIN_8),
        STM::Switch(GPIO_PIN_4),
    });

// clang-format off
const auto timer = HAL::Timer({ // NOLINT
    .arr = HAL::Register(TIM6_ARR),
    .dier = HAL::Register(TIM6_DIER),
    .cr1 = HAL::Register(TIM6_CR1),
    .psc = HAL::Register(TIM6_PSC),
    .cnt = HAL::Register(TIM6_CNT),
  }, registerTIM6_IRQHandler
);
// clang-format on

auto delay = DELAY_BASE; // NOLINT

auto showNextFrame() -> void {
  const auto number = input.bits().to_ulong();
  const auto delay = DELAY_BASE + number * DELAY_T;
  timer.reg.arr.write(delay);
  output.set(animation.next());
}

auto umain() -> int {
  timer.registerHandler(showNextFrame);
  HAL::Interruptions::enable();
  timer.reg.arr.write(DELAY_BASE);
  timer.reg.dier.write(TIM_DIER_UIE);
  timer.reg.psc.write(0);
  timer.reg.cr1.write(TIM_CR1_CEN);
  return 0;
}