# ⏱️ ESP32-Based Real-Time Clock System

### DS3231 RTC • SSD1306 OLED • I²C Communication

<p align="center">
  <b>A professional embedded real-time clock and calendar display system built using ESP32.</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/MCU-ESP32-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/RTC-DS3231-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/Display-SSD1306-black?style=for-the-badge">
  <img src="https://img.shields.io/badge/Protocol-I2C-orange?style=for-the-badge">
  <img src="https://img.shields.io/badge/Language-C%2FC%2B%2B-informational?style=for-the-badge">
  <img src="https://img.shields.io/badge/Platform-Arduino%20IDE-lightgrey?style=for-the-badge">
</p>

---

## 📌 Project Overview

The **ESP32-Based Real-Time Clock System** is an embedded electronics project designed to display accurate date and time information using a **DS3231 Real-Time Clock (RTC)** and a **128×64 SSD1306 OLED display**.

The **ESP32** acts as the main microcontroller and communicates with both the RTC and OLED using the **I²C communication protocol**.

The system provides a clean and professional digital clock interface displaying:

- 🕐 Current Time
- 🌙 AM / PM
- 📅 Day of the Week
- 🗓️ Date
- 📆 Month
- 📆 Year

The project demonstrates practical implementation of **embedded C/C++ programming, I²C communication, RTC interfacing, OLED graphics, hardware debugging, and real-time data processing**.

---

# 🎯 Project Objectives

The main objectives of this project are:

1. Interface a **DS3231 RTC** with ESP32.
2. Interface an **SSD1306 OLED display** with ESP32.
3. Implement **I²C communication** between multiple devices.
4. Read real-time date and time information.
5. Convert 24-hour time into a **12-hour AM/PM format**.
6. Display the information in a clean graphical interface.
7. Understand practical embedded hardware and software integration.
8. Develop a reliable real-time embedded application.

---

# ✨ Features

- ⏱️ Real-time clock functionality
- 📅 Complete date display
- 📆 Day-of-week calculation
- 🌙 12-hour format with AM/PM
- 🖥️ 128×64 OLED graphical display
- 🔗 I²C communication
- 🔋 DS3231 battery-backed timekeeping
- ⚡ ESP32-based processing
- 🔄 Automatic display refresh
- 🧩 Multiple I²C devices on the same bus
- 🛠️ Practical embedded hardware interfacing
- 📡 Serial debugging support

---

# 🖥️ Display Interface

The OLED displays the information in the following format:

```text
┌────────────────────────┐
│        TUESDAY         │
│────────────────────────│
│      05:51 PM          │
│────────────────────────│
│      02 SEP 2026       │
└────────────────────────┘

 # Display Information

| Parameter | Description                 |
| --------- | --------------------------- |
| Day       | Current day of the week     |
| Time      | Current time                |
| AM/PM     | 12-hour time indication     |
| Date      | Current day, month and year |

🧠 System Architecture
                         ┌─────────────────────┐
                         │        ESP32        │
                         │   Main Controller   │
                         └──────────┬──────────┘
                                    │
                              I²C BUS
                         SDA → GPIO 21
                         SCL → GPIO 22
                                    │
                    ┌───────────────┴───────────────┐
                    │                               │
                    ▼                               ▼
             ┌───────────────┐              ┌────────────────┐
             │    DS3231      │              │    SSD1306     │
             │      RTC       │              │   OLED 128×64  │
             └───────┬───────┘              └───────┬────────┘
                     │                              │
                     ▼                              ▼
                Date & Time                    Visual Output


| USB Cable | 1 | Programming and power |
