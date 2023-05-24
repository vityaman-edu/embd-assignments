#pragma once

#include "Hal.hpp"

namespace STM {

class Switch {
public:
  explicit Switch(HAL::GPIO::Pin pin) : pin(pin) {}

  explicit Switch(HAL::GPIO::PinNumber pin)
      : Switch(HAL::GPIO::Pin(HAL::GPIO::Port::E(), pin)) {}

  [[nodiscard]] inline auto isOn() const -> bool {
    return pin.read() == HAL::GPIO::PinState::SET;
  }

  [[nodiscard]] inline auto isOff() const -> bool { //
    return !isOn();
  }

private:
  HAL::GPIO::Pin pin;
};

class Led {
public:
  explicit Led(HAL::GPIO::Pin pin) : pin(pin) {}

  explicit Led(HAL::GPIO::PinNumber pin)
      : Led(HAL::GPIO::Pin(HAL::GPIO::Port::D(), pin)) {}

  inline auto turnOn() const -> void { //
    pin.write(HAL::GPIO::PinState::SET);
  }

  inline auto turnOff() const -> void { //
    pin.write(HAL::GPIO::PinState::RESET);
  }

private:
  HAL::GPIO::Pin pin;
};

}