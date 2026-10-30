# Mosque Control System

An IoT system for monitoring and controlling a mosque's environment (temperature, lighting, airflow) from a mobile app, using ESP-based firmware and Firebase as the cloud link.

## Components

| Part | Folder | Role |
|------|--------|------|
| Monitoring firmware | `Mosque_Monitoring_Firmware/` | Reads temperature, light and flow sensors, drives LED strips and a buzzer for alerts, uploads readings to Firebase over WiFi |
| Controlling firmware | `Mosque_Controlling_Firmware/` | Receives commands from Firebase and switches the fan (via relay) and lighting |
| Mobile app | not in this repository | Flutter app: live dashboard, remote control, historical charts, notifications, multi-language, ML features |

The Flutter app source is not published in this repository. Its design and features are documented in the files below.

Design and usage notes are in `Mosque_Monitoring_Firmware/` (`Mosque Firmware.docx`, `mobile_documentation.pdf`, `MOSQUES AUTOMATION SYSTEM MOBILE APP REPORT.pdf`).

## Setup

1. Create a Firebase project and enable the Realtime Database.
2. Firmware: open each `.ino` in the Arduino IDE, install the required libraries, then set your WiFi credentials, Firebase credentials and pin numbers in `configs.h` and the `init_wifi.h` / `handle_firebase_data.h` headers. Flash each board.
3. App: point the Flutter app at the same Firebase project (add its config files), then `flutter pub get` and `flutter run`.

Never commit real WiFi or Firebase credentials.

## Safety

Mains-powered parts (fan, lighting relays) must follow local electrical standards and be installed by a qualified electrician.

## License

MIT.
