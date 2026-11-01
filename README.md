# Smart Field Alert System (Agriculture)

An Arduino-based smart sensor system that protects agricultural fields by detecting animals or intruders and alerting the farmer instantly with LEDs and a buzzer.

**Live demo:** https://sohan-rana.github.io/Smart-Field-Alert-System-Agriculture/

The demo page includes the project explanation, circuit diagram, an interactive simulation, and the full Arduino code.

## Features

- Detects motion in the field with a PIR sensor
- Red LED + buzzer alert when motion is detected
- Green LED shows the normal / secure state
- 30-second PIR warm-up at start-up (no false alarms)
- Serial Monitor messages only when the state changes
- Low cost and easy to build

## Components

| No. | Component | Qty | Purpose |
|-----|-----------|-----|---------|
| 1 | Arduino Uno | 1 | Main controller |
| 2 | PIR Motion Sensor (HC-SR501) | 1 | Detects infrared motion |
| 3 | Active Buzzer (5V) | 1 | Sound alert |
| 4 | LED (Red + Green) | 2 | Alert / normal indicator |
| 5 | 220 ohm Resistor | 2 | Current limiting for the LEDs |
| 6 | Breadboard | 1 | Circuit connections |
| 7 | Jumper Wires | ~15 | Connections |
| 8 | Power Supply (USB or 7-12V adapter) | 1 | Powers the Arduino |

## Pin Connections

| Component | Arduino Pin | Notes |
|-----------|-------------|-------|
| PIR OUT | D2 | PIR VCC to 5V, PIR GND to GND |
| Green LED | D6 | Through a 220 ohm resistor, cathode to GND |
| Red LED | D7 | Through a 220 ohm resistor, cathode to GND |
| Buzzer (+) | D8 | Other leg to GND. Use an **active** buzzer |

## How It Works

1. The PIR sensor detects infrared motion in the field.
2. It sends a HIGH signal to the Arduino on pin D2.
3. The Arduino decides what to do:
   - **Motion detected:** red LED ON, buzzer ON, green LED OFF
   - **No motion:** green LED ON, red LED OFF, buzzer OFF

## Upload the Code

1. Open `arduino/smart_field_alert.ino` in the Arduino IDE.
2. Select **Tools > Board > Arduino Uno** and the correct port.
3. Click **Upload**.
4. Open the Serial Monitor at **9600 baud** to see the messages.

> After power-on, wait about 30 seconds while the green LED blinks. The PIR sensor is calibrating.

## Project Structure

```
.
├── index.html                      # Project website (GitHub Pages)
├── arduino/
│   └── smart_field_alert.ino       # Arduino sketch
└── README.md
```

## Future Improvements

- **GSM module** for SMS alerts to the farmer's phone
- **Camera module** to capture images of intruders
- **Solar power** for remote fields
- **Mobile app** (WiFi / Bluetooth) for real-time monitoring

## Author

Sohan Rana
