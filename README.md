<div align="center">

# ONECHIP Nano Shield

**A single-board expansion shield that turns an Arduino Nano into a ready-to-go robotics controller.**

Motor driver · sensors · buttons · LEDs · Bluetooth · IR — no breadboard, no jumper wires.

[![Arduino](https://img.shields.io/badge/Arduino-Nano-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Maintained by](https://img.shields.io/badge/maintained%20by-Nova%20Dynamics-orange)](https://github.com/novadynamics-io)
[![Instagram](https://img.shields.io/badge/Instagram-nova__dynamics__-E4405F?logo=instagram&logoColor=white)](https://www.instagram.com/nova_dynamics_)

<img src="https://github.com/user-attachments/assets/b23dc912-8cc8-4843-ae1c-f232d1324061" width="500">
</div>


---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [What's in the Box](#whats-in-the-box)
- [Pin Map](#pin-map)
- [Repository Structure](#repository-structure)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
- [Examples](#examples)
- [Important Notes](#important-notes)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

The **OneChip Nano Shield** is a compact, beginner-friendly expansion board for the Arduino Nano. It brings the components every small robot needs — a dual motor driver, sensor headers, onboard buttons and LEDs, and a dedicated Bluetooth connection — onto a single PCB, so you can go from unboxing to a moving robot without touching a breadboard.

It ships with the **Onechip Nano Shield Arduino library**, which wraps all of that hardware in a simple, class-based API (`Nova.move.FORWARD(100)`, `Nova.ultrasonic.distCM()`, `Nova.led1.on()` …), so you write robot behavior instead of pin-twiddling boilerplate.

## Features

-  **Dual motor driver** (TB6612FNG) — drive two DC gear motors with independent speed and direction
-  **Simple motion API** — `FORWARD`, `BACKWARD`, `LEFT`, `RIGHT`, `SLOWLEFT`, `SLOWRIGHT`, `STOP`, and a raw `TURN(leftSpeed, rightSpeed)` for full differential control
-  **Onboard Bluetooth header** — plug in an HC-05 for wireless robot control over hardware serial
-  **Ultrasonic distance sensing** — one line to get distance in cm
-  **IR remote receiver support** — built on the IRremote library, works with any standard IR remote
-  **2 onboard buttons + 2 onboard LEDs** — ready for status indicators or simple UI, no extra wiring
-  **6 free servo-capable pins (A0–A5)** — enough for a gripper, pan-tilt, or multi-joint arm
-  **Built-in PID controller class** — for line-following, wall-following, or distance-hold behaviors
-  **Speed is 0–100, not 0–255** — motion functions use intuitive percentage speed values

## What's in the Box

| File | Description |
|---|---|
| `Onechip Nano Shield.zip` | Arduino library — drop into `Documents/Arduino/libraries/` |
| `ONECHIP NANO SHIELD MANUAL.pdf` | Full hardware manual: board layout, specs, assembly |

## Pin Map

These are fixed by the PCB — no rewiring needed for onboard components.

| Arduino Pin | Connected Component | Status |
|---|---|---|
| D0 | HC-05 Bluetooth TX | Used |
| D1 | HC-05 Bluetooth RX | Used |
| D2 | Push Button 2 | Used |
| D3 | Push Button 1 | Used |
| D4 | — | Free |
| D5 | — | Free |
| D6 | TB6612FNG Motor 2 Speed (PWM) | Used |
| D7 | TB6612FNG Motor 2 IN A | Used |
| D8 | TB6612FNG Motor 2 IN B | Used |
| D9 | TB6612FNG Motor 1 IN A | Used |
| D10 | TB6612FNG Motor 1 IN B | Used |
| D11 | TB6612FNG Motor 1 Speed (PWM) | Used |
| D12 | Onboard LED 1 | Used |
| D13 | Onboard LED 2 | Used |
| A0 – A5 | Servo headers (up to 6 servos) | Free |
| A6 / A7 | Analog input | Free |

> Ultrasonic and IR TSOP sensors are not hardwired — you assign their pins in code via `.setup()` (see [Examples](#examples)).

## Repository Structure

```
Onechip Nano Shield/
├── library.properties          # Arduino Library Manager metadata
├── src/
│   ├── OnechipNanoShield.h     # Main library — classes & pin map
│   ├── OnechipNanoShield.cpp   # Implementation
│   └── ...                     # Bundled IRremote library (IR support)
└── examples/
    ├── Basic/
    │   ├── LED_Blink/
    │   ├── Button_Read/
    │   ├── Motor_Demo/
    │   ├── Servo_Sweep/
    │   ├── Ultrasonic_Read/
    │   ├── IR_Remote_Control/
    │   └── Bluetooth_Control/
    └── Documentation/
        └── Documentation.ino    # Full API reference sketch (not meant to be run)
```

## Installation

1. Download `Onechip Nano Shield.zip` from this repo.
2. Open the Arduino IDE.
3. Go to **Sketch → Include Library → Add .ZIP Library…**
4. Select the downloaded zip.
5. Restart the IDE. You'll find example sketches under **File → Examples → Onechip Nano Shield**.

## Quick Start

```cpp
#include <OnechipNanoShield.h>

OnechipNanoShield Nova;

void setup() {
  Nova.setup();        // configures LEDs, buttons, and motor driver pins
}

void loop() {
  Nova.move.FORWARD(80);   // drive forward at 80% speed
  delay(1000);
  Nova.move.STOP();
  delay(1000);
}
```

## API Reference

### `OnechipNanoShield`
The main board object. Call `.setup()` once in `setup()` to configure onboard pins. Exposes `.led1`, `.led2`, `.btn1`, `.btn2`, `.move`, `.ultrasonic`, `.ir`, and `.pid`.

### `LED`
| Method | Description |
|---|---|
| `on()` | Turn the LED on |
| `off()` | Turn the LED off |

### `BTN`
| Method | Description |
|---|---|
| `read()` | Returns `true` while the button is pressed |

### `Move` — accessed via `Nova.move`
Speed values are **0–100 (%)**, not 0–255.

| Method | Description |
|---|---|
| `FORWARD(speed)` | Drive straight forward |
| `BACKWARD(speed)` | Drive straight backward |
| `LEFT(speed, radius)` | Turn left; `radius = 0` spins in place, higher radius = wider arc |
| `RIGHT(speed, radius)` | Turn right; same radius behavior |
| `SLOWLEFT(speed)` | Car-like left turn — right wheel only |
| `SLOWRIGHT(speed)` | Car-like right turn — left wheel only |
| `TURN(leftSpeed, rightSpeed)` | Raw differential control, `-100` to `100` each side |
| `STOP()` | Stop both motors |

### `Ultrasonic` — accessed via `Nova.ultrasonic`
| Method | Description |
|---|---|
| `setup(echoPin, trigPin)` | Assign the sensor's pins |
| `distCM()` | Returns distance in centimeters (float) |

### `IR_TSOP` — accessed via `Nova.ir`
| Method | Description |
|---|---|
| `setup(pin)` | Assign the TSOP receiver's signal pin |
| `available()` | Returns `true` if a command was received |
| `read()` | Returns the received command code |

### `OnechipPID` — accessed via `Nova.pid`
| Method | Description |
|---|---|
| `setting(kp, ki, kd)` | Set PID gains |
| `setTimeStep(dt)` | Set control loop time step in seconds |
| `reset()` | Clear accumulated error |
| `correction(target, currentValue)` | Returns the PID output |

## Examples

| Sketch | Demonstrates |
|---|---|
| LED_Blink | Onboard LED control |
| Button_Read | Reading onboard buttons over Serial |
| Motor_Demo | Every motion function — forward, turns, spins, raw `TURN()` |
| Servo_Sweep | Driving up to 6 servos on A0–A5 |
| Ultrasonic_Read | Distance sensing + LED proximity indicator |
| IR_Remote_Control | Controlling the robot with any IR remote |
| Bluetooth_Control | Wireless control via HC-05 |

## Important Notes

- **Speed range is 0–100**, not the standard Arduino 0–255 PWM range — this applies to every `move` function.
- **IR + motors:** using the TSOP IR receiver can interfere with PWM on some timers. If you're driving motors while listening for IR, run motors at 100% speed to avoid timer conflicts.
- **Bluetooth uses hardware serial** (D0/D1) via the HC-05 — this is the same port used for USB upload/debug, so don't run both at once during development.
- **IR command codes are remote-specific.** Print `Nova.ir.read()` to Serial first to find your remote's codes before mapping them to actions.

## Documentation

Full board layout, dimensions, and assembly instructions: [`ONECHIP NANO SHIELD MANUAL.pdf`](<ONECHIP  NANO SHIELD MANUAL.pdf>)

---

<div align="center">
Built by <a href="https://github.com/novadynamics-io">Nova Dynamics</a>
</div>

