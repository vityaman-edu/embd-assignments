#include "Hal.hpp"
#include "STM.hpp"
#include "hal.h"
#include <array>

auto i = 0;       // NOLINT
const auto N = 8; // NOLINT
const auto leds = // NOLINT
    std::array<STM::Led, N>({
        STM::Led(GPIO_PIN_12),
        STM::Led(GPIO_PIN_11),
        STM::Led(GPIO_PIN_9),
        STM::Led(GPIO_PIN_8),
        STM::Led(GPIO_PIN_6),
        STM::Led(GPIO_PIN_5),
        STM::Led(GPIO_PIN_4),
        STM::Led(GPIO_PIN_3),
    });

void TIM6_IRQ_Handler() { //
  leds[i].turnOn();
}

void TIM7_IRQ_Handler() {
  leds[i].turnOff();
  i++;
  if (i == N) {
    HAL::Interruptions::disable();
  }
}

auto umain() -> int {
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

  i = 0;

  timer6.registerHandler(TIM6_IRQ_Handler);
  timer7.registerHandler(TIM7_IRQ_Handler);

  HAL::Interruptions::enable();

  timer6.reg.arr.write(500);
  timer6.reg.dier.write(TIM_DIER_UIE);
  timer6.reg.psc.write(0);

  timer7.reg.arr.write(500);
  timer7.reg.dier.write(TIM_DIER_UIE);
  timer7.reg.psc.write(1);

  timer6.reg.cr1.write(TIM_CR1_CEN);
  timer7.reg.cr1.write(TIM_CR1_CEN);

  return 0;
}