# Industry-Oriented Smart Home Automation System Using IoT

## Overview

The Industry-Oriented Smart Home Automation System Using IoT is designed to provide remote and voice-controlled operation of household electrical appliances using the ESP8266 NodeMCU and the Sinric Pro IoT platform. The system allows users to control appliances through a smartphone or voice assistants such as Amazon Alexa and Google Assistant while also supporting manual switch operation.

---

## Objectives

- Develop a smart home automation system using IoT.
- Enable remote control of electrical appliances over Wi-Fi.
- Provide voice control through Alexa and Google Assistant.
- Reduce energy consumption through efficient appliance management.
- Improve user convenience and home automation.

---

## Features

- Wi-Fi based smart home automation
- Remote appliance control using Sinric Pro
- Voice control with Amazon Alexa and Google Assistant
- Manual push-button control
- Four-channel relay operation
- Real-time device synchronization
- Automatic restoration of relay states after restart
- Easy installation and low-cost implementation

---

## Hardware Components

- ESP8266 NodeMCU
- 4-Channel Relay Module
- Push Buttons
- Breadboard or PCB
- Jumper Wires
- Power Supply
- LED/Bulb/Fan (Load)

---

## Software Requirements

- Arduino IDE
- ESP8266 Board Package
- Sinric Pro Library
- ESP8266WiFi Library
- ArduinoJson Library

---

## Circuit Connections

| ESP8266 Pin | Relay |
|-------------|-------|
| D1 | Relay 1 |
| D2 | Relay 2 |
| D5 | Relay 3 |
| D6 | Relay 4 |

| ESP8266 Pin | Switch |
|-------------|--------|
| D7 | Switch 1 |
| D3 | Switch 2 |
| D4 | Switch 3 |
| RX | Switch 4 |

---

## Working Principle

1. ESP8266 connects to the Wi-Fi network.
2. Sinric Pro establishes cloud communication.
3. Users control appliances using the Sinric Pro app or voice assistants.
4. ESP8266 receives commands and switches the corresponding relay.
5. Manual switches can also control appliances while keeping cloud status synchronized.

---

## Project Structure

```
Industry-Oriented-Smart-Home-Automation-System-Using-IoT
│
├── SmartHome_ESP8266.ino
├── README.md
├── Circuit_Diagram.png
├── Block_Diagram.png
├── Images
│   ├── Prototype.jpg
│   └── Working.jpg
└── Report.pdf
```

---

## Applications

- Smart Homes
- Smart Offices
- Smart Buildings
- Industrial Automation
- IoT Learning Projects
- Energy Management Systems

---

## Future Enhancements

- Energy Consumption Monitoring
- Temperature and Humidity Monitoring
- Gas Leakage Detection
- Fire Detection
- Motion Detection
- Mobile Notifications
- AI-Based Automation
- MQTT Integration

---

## Technologies Used

- C++
- Arduino IDE
- ESP8266 NodeMCU
- IoT
- Wi-Fi
- Sinric Pro
- Embedded Systems

---

## Author

**Maria Ranjan Morais**

---

## License

This project is developed for educational and learning purposes.
