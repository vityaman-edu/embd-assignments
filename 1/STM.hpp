#pragma once

#include "Hal.hpp"
#include <bitset>

namespace STM {

class Switch {
public:
  explicit Switch(HAL::GPIO::Pin pin) : pin(pin) {}

  // TODO: this kind of constructor was not a good
  // idea, it is better to explicitly write port
  // every time as it can be dependent on
  // microcontroller configuration
  explicit Switch(HAL::GPIO::PinNumber pin)
      : Switch(HAL::GPIO::Pin(HAL::GPIO::Port::E(), pin)) {}

  [[nodiscard]] inline auto enabled() const -> bool {
    return pin.read() == HAL::GPIO::PinState::SET;
  }

  [[nodiscard]] inline auto disabled() const -> bool { //
    return !enabled();
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

class Button {
public:
  explicit Button(HAL::GPIO::Pin pin) : pin(pin) {}

  explicit Button(HAL::GPIO::PinNumber pin)
      : Button(HAL::GPIO::Pin(HAL::GPIO::Port::C(), pin)) {}

  [[nodiscard]] auto cliked() const -> bool {
    return pin.read() == HAL::GPIO::PinState::RESET;
  }

private:
  HAL::GPIO::Pin pin;
};

enum TrafficLightColor {
  GREEN = 0,
  YELLOW = 1,
  RED = 2,
};

class TrafficLight {
public:
  explicit TrafficLight(
      HAL::GPIO::Pin green,  // NOLINT
      HAL::GPIO::Pin yellow, // NOLINT
      HAL::GPIO::Pin red     // NOLINT
  )
      : green(green), yellow(yellow), red(red) {}

  auto setColor(TrafficLightColor color) const -> void {
    switch (color) {
    case TrafficLightColor::GREEN: {
      green.set();
      yellow.reset();
      red.reset();
    } break;
    case TrafficLightColor::YELLOW: {
      green.reset();
      yellow.set();
      red.reset();
    } break;
    case TrafficLightColor::RED: {
      green.reset();
      yellow.reset();
      red.set();
    } break;
    }
  }

private:
  HAL::GPIO::Pin green;
  HAL::GPIO::Pin yellow;
  HAL::GPIO::Pin red;
};

}