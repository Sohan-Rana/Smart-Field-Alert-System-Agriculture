# Smart Field Alert System: Project Report

**Author:** Sohan Rana
**Platform:** Arduino Uno + PIR motion sensor
**Live demo:** https://sohan-rana.github.io/Smart-Field-Alert-System-Agriculture/

## 1. Introduction

Robotics and embedded systems use sensors, a controller and actuators to perform tasks automatically. In this project the **sensor** is a PIR motion sensor (the "eyes"), the **controller** is an Arduino Uno (the "brain"), and the **actuators** are LEDs and a buzzer (the "hands"). The system watches an agricultural field and alerts the farmer when movement is detected.

## 2. Problem Statement

Crop fields are often left unguarded at night. Animals can enter and damage crops, and thieves can enter unnoticed. Guarding the field by hand means a person must stay awake in the open, which is tiring, costs money and can be unsafe. A cheap automatic system that watches the field and raises an alert immediately can reduce this burden.

## 3. Objectives

1. Improve the security of an agricultural field.
2. Detect animals or intruders using a PIR sensor.
3. Alert the farmer immediately using LEDs and a buzzer.
4. Keep the solution low-cost and easy to build.

## 4. Components

| Component | Qty | Purpose |
|-----------|-----|---------|
| Arduino Uno | 1 | Main controller |
| PIR sensor (HC-SR501) | 1 | Motion detection |
| Active buzzer (5V) | 1 | Sound alert |
| LED, red and green | 2 | Alert and normal indicators |
| 220 ohm resistor | 2 | LED current limiting |
| Breadboard | 1 | Connections |
| Jumper wires | ~15 | Connections |
| Power supply | 1 | USB 5V or 7-12V adapter |

## 5. Circuit Connections

| Component | Arduino pin |
|-----------|-------------|
| PIR OUT | D2 (VCC to 5V, GND to GND) |
| Green LED (via 220 ohm) | D6 |
| Red LED (via 220 ohm) | D7 |
| Buzzer (+) | D8 |

Diagrams: [`wiring/circuit-diagram.svg`](../wiring/circuit-diagram.svg) and [`docs/block-diagram.svg`](block-diagram.svg).

## 6. Working Principle

1. After power-on the PIR sensor warms up for about 30 seconds (the green LED blinks).
2. The PIR sensor outputs HIGH when it detects a moving heat source.
3. The Arduino reads pin D2 every 100 ms.
4. **Motion detected:** red LED on, buzzer on, green LED off.
5. **No motion:** green LED on, red LED off, buzzer off.

## 7. Results

Fill in the measured results from [`test-log.md`](test-log.md): maximum reliable detection range, average response time and false alarm observations.

## 8. Limitations

- The PIR sensor covers a limited range and angle (HC-SR501 is typically rated for several metres), so a large field needs several units.
- A PIR sensor cannot tell an animal from a person or from other moving heat sources.
- Strong sunlight, hot wind and small animals can cause false alarms.
- The basic version needs a 5V supply, which may be hard to provide in a remote field (a solar panel and battery can help).
- The basic version alerts only at the device. Remote alerts need the GSM or WiFi versions.

## 9. Future Work

- SMS alerts with a GSM module (see `arduino/smart_field_alert_gsm`)
- Fewer false alarms using an ultrasonic distance check (see `arduino/smart_field_alert_ultrasonic`)
- Camera module to capture images of intruders
- Solar power for remote fields
- Mobile app or Telegram notifications using an ESP32 / NodeMCU
