# ⏱️ ESP32 Real-Time Clock System

### DS3231 Precision RTC • SSD1306 OLED • I²C Communication

```{=html}
<p align="center">
```
`<img src="images/clock_display.jpg" alt="ESP32 Real-Time Clock OLED Display" width="720">`{=html}
```{=html}
</p>
```
```{=html}
<p align="center">
```
`<b>`{=html}A professional embedded timekeeping and calendar display
system built with ESP32.`</b>`{=html}
```{=html}
</p>
```
```{=html}
<p align="center">
```
`<img src="https://img.shields.io/badge/MCU-ESP32-blue?style=for-the-badge">`{=html}
`<img src="https://img.shields.io/badge/RTC-DS3231-green?style=for-the-badge">`{=html}
`<img src="https://img.shields.io/badge/Display-SSD1306-black?style=for-the-badge">`{=html}
`<img src="https://img.shields.io/badge/Protocol-I²C-orange?style=for-the-badge">`{=html}
`<img src="https://img.shields.io/badge/Language-C%2FC%2B%2B-informational?style=for-the-badge">`{=html}
```{=html}
</p>
```

------------------------------------------------------------------------

## 📌 Project Overview

This project implements an **ESP32-based real-time clock and calendar
display system** using the **DS3231 Real-Time Clock (RTC)** and a
**128×64 SSD1306 OLED display**.

The DS3231 maintains accurate date and time information, while the ESP32
reads the RTC data and presents it on the OLED in a clean,
human-readable interface.

The system uses the **I²C communication protocol**, allowing both the
RTC and OLED to operate on the same two-wire communication bus.

### Display Format

``` text
┌──────────────────────────────┐
│          TUESDAY             │
│──────────────────────────────│
│        05:51 PM              │
│──────────────────────────────│
│         02 SEP 2026          │
└──────────────────────────────┘
```

------------------------------------------------------------------------

## ✨ Key Features

-   ⏱️ Real-time clock using **DS3231 RTC**
-   📅 Day, date, month, and year display
-   🕐 12-hour time format
-   🌙 AM/PM indication
-   🖥️ 128×64 **SSD1306 OLED** interface
-   🔗 I²C communication between ESP32 peripherals
-   🔄 Continuous time update every second
-   🔋 RTC power-loss detection
-   ⚙️ Automatic RTC initialization after power loss
-   🧩 Modular embedded hardware architecture
-   💻 Developed using Arduino IDE and C/C++

------------------------------------------------------------------------

## 🧠 System Architecture

``` text
                    ┌──────────────────────┐
                    │        ESP32         │
                    │   Main Controller    │
                    └──────────┬───────────┘
                               │
                     I²C Bus   │
                 ┌─────────────┴─────────────┐
                 │                           │
                 ▼                           ▼
        ┌─────────────────┐         ┌─────────────────┐
        │   DS3231 RTC    │         │  SSD1306 OLED   │
        │                 │         │    128 × 64     │
        │ Date & Time     │         │                 │
        │ Timekeeping     │         │ Time / Date     │
        └─────────────────┘         └─────────────────┘
```

### Data Flow

``` text
DS3231
   │
   │ Current Date & Time
   ▼
ESP32
   │
   │ Process / Format Data
   ▼
SSD1306 OLED
   │
   ▼
User Display
```

------------------------------------------------------------------------

## 🔌 Hardware Components

  Component                 Purpose
  ------------------------- --------------------------------------
  **ESP32 DevKit V1**       Main microcontroller
  **DS3231 RTC Module**     Accurate real-time date/time keeping
  **SSD1306 128×64 OLED**   Visual output
  Jumper Wires              Hardware connections
  USB Cable / 5V Supply     System power

------------------------------------------------------------------------

## 🔗 I²C Hardware Connections

Both the DS3231 and SSD1306 share the same I²C bus.

  ESP32                     SSD1306 OLED   DS3231 RTC
  ------------------------- -------------- ------------
  **GPIO 21**               SDA            SDA
  **GPIO 22**               SCL            SCL
  **GND**                   GND            GND
  **3.3V / suitable VCC**   VCC            VCC

### I²C Bus

``` text
                ESP32
             ┌─────────┐
GPIO 21 SDA ─┤         ├──── SDA ─── SSD1306
GPIO 22 SCL ─┤         ├──── SCL ─── SSD1306
             │         │
             └─────────┘
                  │
                  ├──────── SDA ─── DS3231
                  └──────── SCL ─── DS3231
```

### I²C Addresses

  Device           Typical Address
  -------------- -----------------
  SSD1306 OLED              `0x3C`
  DS3231 RTC                `0x68`

Because the devices have different I²C addresses, they can operate on
the same SDA/SCL lines.

------------------------------------------------------------------------

## 💻 Software & Libraries

### Development Environment

-   **Arduino IDE**
-   **C/C++**
-   ESP32 Arduino Core

### Libraries

``` cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"
```

### Library Roles

  Library                Function
  ---------------------- -------------------------
  `Wire.h`               I²C communication
  `Adafruit_GFX.h`       Graphics/text rendering
  `Adafruit_SSD1306.h`   SSD1306 OLED control
  `RTClib.h`             DS3231 RTC interface

------------------------------------------------------------------------

## ⚙️ Operating Principle

### 1. ESP32 Initialization

The ESP32 initializes the I²C interface:

``` cpp
Wire.begin(21, 22);
```

where:

-   GPIO 21 → SDA
-   GPIO 22 → SCL

### 2. OLED Initialization

The SSD1306 is initialized at its I²C address:

``` cpp
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
```

### 3. RTC Initialization

The ESP32 checks communication with the DS3231:

``` cpp
rtc.begin();
```

### 4. RTC Power-Loss Detection

The controller checks whether the RTC lost its stored time:

``` cpp
if (rtc.lostPower())
{
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
```

This initializes the RTC using the firmware compilation date/time when
required.

### 5. Time Acquisition

The current RTC value is obtained using:

``` cpp
DateTime now = rtc.now();
```

### 6. Data Formatting

The raw RTC values are converted into:

-   12-hour time
-   AM/PM
-   Day of week
-   Day
-   Month
-   Year

### 7. OLED Update

The formatted information is rendered on the OLED and refreshed
continuously.

------------------------------------------------------------------------

## 🕐 12-Hour Time Conversion

The system converts the DS3231's 24-hour value into a user-friendly
12-hour format.

  RTC Time   OLED
  ---------- ------------
  `00:00`    `12:00 AM`
  `01:00`    `01:00 AM`
  `11:00`    `11:00 AM`
  `12:00`    `12:00 PM`
  `13:00`    `01:00 PM`
  `17:51`    `05:51 PM`
  `23:00`    `11:00 PM`

------------------------------------------------------------------------

## 🧪 Testing & Validation

The project was developed and tested progressively to isolate hardware
and software issues.

### Test 1 --- RTC Only

``` text
ESP32 → DS3231
```

Result:

``` text
RTC FOUND
RTC OK
```

### Test 2 --- OLED Only

``` text
ESP32 → SSD1306
```

Result:

``` text
OLED OK
```

### Test 3 --- Combined System

``` text
ESP32
 ├── DS3231
 └── SSD1306
```

Result:

``` text
OLED OK
RTC OK
```

### Final Validation

The final system successfully displays:

-   Current day
-   Current time
-   AM/PM
-   Current date
-   Month
-   Year

with automatic one-second updates.

------------------------------------------------------------------------

## 📂 Project Structure

``` text
ESP32-Real-Time-Clock-System/
│
├── ESP32_Real_Time_Clock/
│   └── ESP32_Real_Time_Clock.ino
│
├── images/
│   └── clock_display.jpg
│
└── README.md
```

------------------------------------------------------------------------

## 🚀 Getting Started

### Step 1 --- Install Arduino IDE

Install the Arduino IDE and configure the ESP32 board package.

### Step 2 --- Install Libraries

Install:

-   Adafruit GFX Library
-   Adafruit SSD1306
-   RTClib

### Step 3 --- Connect Hardware

Connect the OLED and DS3231 to:

``` text
SDA → GPIO 21
SCL → GPIO 22
```

### Step 4 --- Select Board

Select the appropriate ESP32 development board in Arduino IDE.

### Step 5 --- Upload Firmware

Open:

``` text
ESP32_Real_Time_Clock.ino
```

Compile and upload the firmware.

### Step 6 --- Open Serial Monitor

Set the baud rate to:

``` text
115200
```

Expected startup output:

``` text
OLED OK
RTC OK
```

The OLED will then begin displaying the current time and date.

------------------------------------------------------------------------

## 🛠️ Troubleshooting

### OLED shows "OLED FAILED"

Check:

-   OLED power
-   GND connection
-   SDA → GPIO 21
-   SCL → GPIO 22
-   OLED I²C address (`0x3C`)

### RTC shows "RTC FAILED"

Check:

-   DS3231 power
-   Common GND
-   SDA → GPIO 21
-   SCL → GPIO 22
-   RTC I²C address (`0x68`)

### Time is incorrect

If the RTC has lost power, allow the initialization code to set the
time:

``` cpp
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
```

After initialization, avoid repeatedly calling `rtc.adjust()` in
`loop()`, otherwise the clock will continuously reset.

------------------------------------------------------------------------

## 🔮 Future Enhancements

The project can be extended into a more advanced embedded product by
adding:

-   🔘 Push buttons for manual time/date adjustment
-   🌡️ Temperature display using DS3231 temperature data
-   🔔 Alarm functionality
-   ⏰ Multiple programmable alarms
-   🔋 Battery-backed RTC monitoring
-   📡 Wi-Fi time synchronization using NTP
-   🌐 Web-based time configuration
-   📱 Mobile-app configuration
-   💾 Non-volatile user settings
-   🌙 OLED power-saving modes
-   🔆 Automatic display brightness control
-   🧱 Custom PCB design
-   🏭 Enclosure and product-level hardware integration

------------------------------------------------------------------------

## 🎯 Embedded Systems Concepts Demonstrated

This project demonstrates practical experience with:

``` text
ESP32 Microcontroller
        │
        ├── I²C Communication
        │
        ├── RTC Interfacing
        │
        ├── OLED Interfacing
        │
        ├── Data Formatting
        │
        ├── Peripheral Initialization
        │
        ├── Hardware Debugging
        │
        └── Real-Time Data Display
```

It is particularly useful for demonstrating **microcontroller peripheral
interfacing, I²C communication, hardware debugging, and embedded C/C++
programming**.

------------------------------------------------------------------------

## 📸 Project Demonstration

Add your actual project photograph to:

``` text
images/clock_display.jpg
```

The image will automatically appear at the top of this README.

------------------------------------------------------------------------

## 👨‍💻 Author

**Shaik Rizwan Basha**

Embedded Systems \| Embedded C \| ESP32 \| STM32 \| UART \| SPI \| I²C
\| CAN

------------------------------------------------------------------------

## ⭐ Project Highlights

> **A practical embedded systems project demonstrating real-time data
> acquisition from a DS3231 RTC and graphical presentation through an
> SSD1306 OLED using the ESP32 and I²C communication.**

If you find this project useful, consider giving the repository a ⭐.

------------------------------------------------------------------------

### 📜 License

This project is open for learning, experimentation, and educational use.
