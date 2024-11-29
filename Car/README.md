
# ESP32 Car Control System

This project is an ESP32-based car control system that uses ESP-NOW for wireless communication. 
A joystick is used to control the movement of the car, which is driven by two motors controlled through a motor driver.

## Features

- **Wireless Communication**: Utilizes ESP-NOW for fast and reliable data transfer.
- **Joystick Control**: Reads joystick values for forward, backward, and rotational movement.
- **PWM Motor Control**: Adjusts motor speed using PWM signals.
- **Buzzer**: Audible feedback using a connected buzzer.

## Components

- **ESP32**: Main microcontroller.
- **Motor Driver**:
  - ENA: PWM pin 4
  - IN1: Direction pin 16
  - IN2: Direction pin 17
  - ENB: PWM pin 19
  - IN3: Direction pin 5
  - IN4: Direction pin 18
- **Motors**: Two DC motors connected to the motor driver.
- **Joystick**: Sends X, Y, and button state values to control the car.
- **Buzzer**: Connected to pin 2 for alerts.
- **Power Source**: External power supply for the motors and ESP32.

## Pin Configuration

| Component         | ESP32 Pin |
|--------------------|-----------|
| ENA (PWM Motor A)  | 4         |
| IN1 (Motor A)      | 16        |
| IN2 (Motor A)      | 17        |
| ENB (PWM Motor B)  | 19        |
| IN3 (Motor B)      | 5         |
| IN4 (Motor B)      | 18        |
| Buzzer             | 2         |

## Diagram

Refer to the connection diagram in the repository for detailed wiring.

## Setup

1. **Hardware**: Connect the components as shown in the diagram.
2. **Software**:
   - Install the necessary libraries for ESP-NOW and PWM motor control.
   - Upload the `Car.ino` code to your ESP32.
3. **Operation**:
   - Pair the joystick with the ESP32.
   - Power the system and control the car using the joystick.

## License

This project is licensed under the MIT License. Feel free to use and modify it.
