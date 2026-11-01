# IoT-Based Smart Classroom Energy Management System

An IoT prototype using NodeMCU ESP8266, PIR, digital LDR, DHT11, MQ gas sensor, relay, LED and Blynk IoT for classroom monitoring and appliance control.

## Hardware and pin mapping

| Component | ESP8266 pin | Purpose |
|---|---|---|
| PIR OUT | D5 | Occupancy/motion |
| Relay IN | D1 | Fan/load switching |
| LED | D7 | Lighting demonstration |
| Digital LDR OUT | D6 | Dark/light detection |
| MQ analog OUT | A0 | Raw gas reading |
| DHT11 DATA | D4 | Temperature/humidity |

## Blynk virtual pins

| Pin | Function |
|---|---|
| V0 | Temperature |
| V1 | Humidity |
| V2 | PIR motion state |
| V3 | AQI category text |
| V4 | Fan state/manual control |
| V5 | Raw gas sensor value |
| V6 | Return to automatic mode |

## Working

- Automatic fan: ON when motion is detected and temperature is above 25°C; otherwise OFF.
- Manual fan: V4 enables manual control; V6 returns to automatic mode.
- Lighting: digital LDR LOW is treated as dark and switches the LED ON.
- Sensor readings are sent to Blynk every 2 seconds.
- Relay and LED outputs are active-low in this firmware.

## Air-quality labels

The code labels the MQ analog reading as GOOD (<200), MODERATE (200–399), POOR (400–699), or HAZARDOUS (700+). These are prototype thresholds only, not calibrated or official AQI values.

## Setup

1. Install Arduino IDE and ESP8266 board support.
2. Install the Blynk and DHT libraries.
3. Create a Blynk template/device and configure virtual pins V0–V6.
4. Open `firmware/smart_classroom_blynk.ino`.
5. Replace the placeholder Blynk template ID, template name, auth token, Wi-Fi SSID and password in your private local copy.
6. Select the correct NodeMCU ESP8266 board and COM port, upload, and open Serial Monitor at 115200 baud.

## Security

Never publish Wi-Fi passwords or Blynk auth tokens. This repository contains placeholders only. Since credentials were pasted into a chat, rotate the Blynk auth token and change the Wi-Fi password if they are real and still active.

## Important implementation notes

- This README and firmware describe the Blynk-enabled version supplied for this repository.
- The earlier project report documents an earlier prototype and has some different pin/configuration descriptions. Verify your actual circuit against this firmware before claiming the wiring matches.
- Humidity is monitored but does not currently control the fan.
- No measured energy savings or calibrated AQI results are claimed here.
- Use a safe, properly rated and enclosed relay arrangement. Mains wiring must be handled by a qualified person; do not wire mains appliances on a breadboard.

## Future improvements

- Add occupancy timeout logic.
- Calibrate the gas sensor and validate air-quality interpretation.
- Add energy measurement and data logging.
- Test in a real classroom and quantify energy savings.
- Add circuit, prototype and Blynk dashboard images under `docs/`.

## Academic project

IoT-Based Smart Classroom Energy Management System. Add final team and institution credits if appropriate.
