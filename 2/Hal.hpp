#pragma once

#include "hal.h"
#include <functional>
#include <utility>

namespace HAL {

struct Milliseconds {
  explicit Milliseconds(uint count) : count(count) {} // NOLINT
  uint count;                                         // NOLINT
};

inline auto Delay(Milliseconds delay) { //
  HAL_Delay(delay.count);
}

namespace GPIO {

struct Port {
  explicit Port(uint number) : number(number) {}

  static auto A() noexcept { return Port(GPIOA); }
  static auto B() noexcept { return Port(GPIOB); }
  static auto C() noexcept { return Port(GPIOC); }
  static auto D() noexcept { return Port(GPIOD); }
  static auto E() noexcept { return Port(GPIOE); }

  uint number; // NOLINT
};

struct PinNumber {
  PinNumber(uint value) : value(value) {} // NOLINT
  uint value;                             // NOLINT
};

using PinState = enum {
  RESET = GPIO_PinState::GPIO_PIN_RESET,
  SET = GPIO_PinState::GPIO_PIN_SET,
};

class Pin {
public:
  Pin(Port port, PinNumber pin) : port(port), pin(pin) {}

  inline auto toggle() const { //
    HAL_GPIO_TogglePin(port.number, pin.value);
  }

  inline auto write(PinState state) const {
    const auto legacy = static_cast<GPIO_PinState>(state);
    HAL_GPIO_WritePin(port.number, pin.value, legacy);
  }

  [[nodiscard]] inline auto read() const {
    const auto state = HAL_GPIO_ReadPin(port.number, pin.value);
    return static_cast<PinState>(state);
  }

  inline auto set() const { write(PinState::SET); }

  inline auto reset() const { write(PinState::RESET); }

private:
  Port port;
  PinNumber pin;
};

} // namespace GPIO

class Interruptions {
public:
  static inline auto enable() -> void { __enable_irq(); }
  static inline auto disable() -> void { __disable_irq(); }
};

class Register {
public:
  explicit Register(uint address) : address(address) {}

  [[nodiscard]] auto read() const -> uint { //
    return READ_REG(address);
  }

  auto write(uint value) const -> void { //
    WRITE_REG(address, value);
  }

private:
  uint address;
};

struct TimerRegisters {
  Register arr;
  Register dier;
  Register cr1;
  Register psc;
  Register cnt;
};

using TimerHandler = void (*)();
using TimerHandlerRegstrator = std::function<void(TimerHandler)>;

class Timer {
public:
  explicit Timer(TimerRegisters reg, TimerHandlerRegstrator registrator)
      : reg(reg), registrator(std::move(registrator)) {}

  auto registerHandler(const TimerHandler& handler) const {
    registrator(handler);
  }

public:               // NOLINT
  TimerRegisters reg; // NOLINT
private:
  TimerHandlerRegstrator registrator;
};

} // namespace HAL