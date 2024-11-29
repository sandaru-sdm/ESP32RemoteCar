# ESP-NOW Joystick Controller

This project demonstrates the implementation of an ESP-NOW joystick controller using ESP32. The joystick data, including X-axis, Y-axis, and button state, is read and broadcast to other ESP-NOW-compatible devices over WiFi.

## Features
- Reads joystick data from analog pins.
- Detects button press state.
- Broadcasts joystick data to all ESP-NOW peers using a single channel.

## Hardware Requirements
- 1 x ESP32
- 1 x Joystick Module (with X, Y, and button pins)
- Breadboard and jumper wires

## Wiring Diagram
| Joystick Pin | ESP32 Pin |
|--------------|-----------|
| X-axis       | GPIO 34   |
| Y-axis       | GPIO 35   |
| Button       | GPIO 32   |

**Note:** Use the `INPUT_PULLUP` configuration for the button pin.

## Software Requirements
- Arduino IDE (latest version)
- ESP32 Board Package for Arduino IDE
- WiFi library (comes pre-installed with the ESP32 package)
- ESP-NOW library (comes pre-installed with the ESP32 package)

## Setup Instructions
1. Install the Arduino IDE and set up the ESP32 board package.
2. Connect the joystick module to the ESP32 as per the wiring diagram.
3. Copy the code from `ESP_NOW_Joystick_Controller.ino` into the Arduino IDE.
4. Set the `ESPNOW_WIFI_CHANNEL` to the desired WiFi channel (default is 6).
5. Compile and upload the code to the ESP32.

## Code Description
- **Joystick Data Structure**: The `struct_message` struct holds the X-axis, Y-axis, and button state data.
- **ESP-NOW Setup**: An ESP-NOW broadcast peer is configured to send messages to all connected ESP-NOW devices.
- **Reading Joystick Values**: `analogRead` is used for the joystick X and Y pins, while `digitalRead` is used for the button pin.
- **Data Broadcasting**: Joystick data is sent every 100ms using the ESP-NOW protocol.

## How It Works
1. The ESP32 reads analog values for X and Y positions of the joystick.
2. The button state (pressed or not) is read using `digitalRead`.
3. The data is packed into a `struct_message` structure and sent to all ESP-NOW peers.
4. Other ESP-NOW devices can receive and process this data for further use.

## Troubleshooting
- **Failed to initialize broadcast peer**: Check if the WiFi channel is correctly set and ensure no interference from other WiFi networks.
- **Failed to broadcast joystick data**: Ensure the ESP32 is properly powered and the joystick module is connected correctly.

## Notes
- This code uses the `ESP_NOW_Broadcast_Peer` class to manage the ESP-NOW broadcast peer.
- Broadcasting is done using the predefined `ESP_NOW.BROADCAST_ADDR`.

## Future Enhancements
- Add data encryption for secure communication.
- Implement acknowledgment and retry mechanisms to ensure data delivery.
- Extend the functionality to control a remote device, such as a robot or car.

## License
This project is licensed under the MIT License. Feel free to use, modify, and distribute as per the terms of the license.
