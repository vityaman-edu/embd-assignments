#include "BinaryInput.hpp"
#include "BinaryOutput.hpp"
#include "Hal.hpp"
#include "LedAnimation.hpp"
#include "STM.hpp"
#include "hal.h"
#include <bitset>

auto umain() -> int {
  const auto T = 150;

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

  const auto ANIMATION_STATES = 12;
  auto animation = STM::LedAnimation<ANIMATION_STATES, OUT_BITS>({
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
  const auto input = STM::BinaryInput<INPUT_SIZE>({
      STM::Switch(GPIO_PIN_12),
      STM::Switch(GPIO_PIN_10),
      STM::Switch(GPIO_PIN_8),
      STM::Switch(GPIO_PIN_4),
  });

  const auto timer6 = HAL::Timer(
      {
          .arr = HAL::Register(TIM6_ARR),
          .dier = HAL::Register(TIM6_DIER),
          .cr1 = HAL::Register(TIM6_CR1),
          .psc = HAL::Register(TIM6_PSC),
          .cnt = HAL::Register(TIM6_CNT),
      },
      registerTIM6_IRQHandler
  );

  const auto timer7 = HAL::Timer(
      {
          .arr = HAL::Register(TIM7_ARR),
          .dier = HAL::Register(TIM7_DIER),
          .cr1 = HAL::Register(TIM7_CR1),
          .psc = HAL::Register(TIM7_PSC),
          .cnt = HAL::Register(TIM7_CNT),
      },
      registerTIM7_IRQHandler
  );

  HAL::Interruptions::enable();

  timer6.reg.arr.write(500);
  timer6.reg.dier.write(TIM_DIER_UIE);
  timer6.reg.psc.write(0);

  timer7.reg.arr.write(500);
  timer7.reg.dier.write(TIM_DIER_UIE);
  timer7.reg.psc.write(1);

  timer6.reg.cr1.write(TIM_CR1_CEN);
  timer7.reg.cr1.write(TIM_CR1_CEN);

  HAL::Interruptions::disable();

  return 0;
}