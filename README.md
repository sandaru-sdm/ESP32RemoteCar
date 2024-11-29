# ESP-NOW Joystick and Car Control System

This project demonstrates a wireless communication system using ESP-NOW and ESP32. It combines a joystick controller and a car control system to enable remote vehicle operation. The joystick sends movement data to the car, which interprets the commands to control motor speed and direction.

## Features

### Joystick Controller
- Reads joystick values (X, Y, and button state).
- Broadcasts joystick data to other ESP-NOW devices.
- Simple and reliable wireless communication over ESP-NOW.

### Car Control System
- Processes joystick data to control a car's movement.
- Supports forward, backward, and rotational motions.
- Utilizes PWM for motor speed control.
- Includes a buzzer for audible alerts.

## Hardware Requirements
- **2 x ESP32** (one for joystick controller, one for car control).
- **Joystick Module** (with X, Y, and button outputs).
- **Motor Driver** (e.g., L298N or L293D).
- **2 x DC Motors**.
- **Buzzer**.
- Breadboard, jumper wires, and external power supply.

## Pin Configuration

### Joystick Controller
| Joystick Pin | ESP32 Pin |
|--------------|-----------|
| X-axis       | GPIO 34   |
| Y-axis       | GPIO 35   |
| Button       | GPIO 32   |

### Car Control System
| Component         | ESP32 Pin |
|--------------------|-----------|
| ENA (PWM Motor A)  | 4         |
| IN1 (Motor A)      | 16        |
| IN2 (Motor A)      | 17        |
| ENB (PWM Motor B)  | 19        |
| IN3 (Motor B)      | 5         |
| IN4 (Motor B)      | 18        |
| Buzzer             | 2         |

## Wiring Diagrams
Refer to the connection diagrams in the repository for detailed hardware setup.

## Software Requirements
- Arduino IDE (latest version).
- ESP32 Board Package for Arduino IDE.
- ESP-NOW library (pre-installed with the ESP32 package).
- PWM motor control libraries (if necessary).

## Setup Instructions

### Joystick Controller
1. Connect the joystick to the ESP32 as per the wiring diagram.
2. Configure the `ESPNOW_WIFI_CHANNEL` to your desired WiFi channel (default is 6).
3. Upload the joystick controller code to the ESP32.

### Car Control System
1. Connect the motors, motor driver, and buzzer to the ESP32 as per the wiring diagram.
2. Pair the car's ESP32 with the joystick controller ESP32.
3. Upload the car control code to the ESP32.

## How It Works
1. **Joystick Controller**: 
   - Reads X and Y positions and button state from the joystick.
   - Sends this data over ESP-NOW to the car's ESP32.

2. **Car Control System**:
   - Receives joystick data via ESP-NOW.
   - Uses PWM signals to control motor speed and direction based on the joystick input.
   - Activates the buzzer for alerts or feedback.

## Troubleshooting
- **Joystick Data Not Received**: Ensure both ESP32 devices are using the same WiFi channel and are properly paired.
- **Motors Not Moving**: Check motor driver connections and power supply.
- **Buzzer Not Working**: Verify buzzer connection and GPIO pin configuration.

## Future Enhancements
- Implement encryption for secure ESP-NOW communication.
- Add acknowledgment and retries for robust data transfer.
- Extend functionality to include additional sensors or features (e.g., obstacle avoidance).

## License
This project is licensed under the MIT License. Feel free to use, modify, and distribute as per the terms of the license.
