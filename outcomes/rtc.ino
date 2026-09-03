#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// RTC
RTC_DS3231 rtc;


// Days of the week
const char* daysOfWeek[] =
{
  "SUNDAY",
  "MONDAY",
  "TUESDAY",
  "WEDNESDAY",
  "THURSDAY",
  "FRIDAY",
  "SATURDAY"
};


// Months
const char* months[] =
{
  "JAN",
  "FEB",
  "MAR",
  "APR",
  "MAY",
  "JUN",
  "JUL",
  "AUG",
  "SEP",
  "OCT",
  "NOV",
  "DEC"
};


void setup()
{
  Serial.begin(115200);

  // ESP32 I2C
  // SDA = GPIO21
  // SCL = GPIO22
  Wire.begin(21, 22);


  // ---------------- OLED INITIALIZATION ----------------

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED FAILED");

    while (1);
  }

  Serial.println("OLED OK");


  // ---------------- RTC INITIALIZATION ----------------

  if (!rtc.begin())
  {
    Serial.println("RTC FAILED");

    while (1);
  }

  Serial.println("RTC OK");


  // Set RTC only if it has lost power
  if (rtc.lostPower())
  {
    Serial.println("RTC LOST POWER");

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    Serial.println("RTC TIME SET");
  }


  // Initial display
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.display();

  delay(1000);
}


void loop()
{
  // Get current date and time from DS3231
  DateTime now = rtc.now();


  // =====================================================
  //                    12 HOUR FORMAT
  // =====================================================

  int hour12 = now.hour();

  const char* ampm;

  if (hour12 >= 12)
  {
    ampm = "PM";
  }
  else
  {
    ampm = "AM";
  }

  if (hour12 == 0)
  {
    hour12 = 12;
  }
  else if (hour12 > 12)
  {
    hour12 -= 12;
  }


  // =====================================================
  //                    SERIAL MONITOR
  // =====================================================

  Serial.print("Day: ");
  Serial.println(daysOfWeek[now.dayOfTheWeek()]);

  Serial.print("Time: ");

  if (hour12 < 10)
    Serial.print("0");

  Serial.print(hour12);
  Serial.print(":");

  if (now.minute() < 10)
    Serial.print("0");

  Serial.print(now.minute());
  Serial.print(":");

  if (now.second() < 10)
    Serial.print("0");

  Serial.print(now.second());

  Serial.print(" ");
  Serial.println(ampm);


  Serial.print("Date: ");

  if (now.day() < 10)
    Serial.print("0");

  Serial.print(now.day());

  Serial.print(" ");

  Serial.print(months[now.month() - 1]);

  Serial.print(" ");

  Serial.println(now.year());

  Serial.println("-------------------------");


  // =====================================================
  //                    OLED DISPLAY
  // =====================================================

  display.clearDisplay();


  // -----------------------------------------------------
  // OUTER BORDER
  // -----------------------------------------------------

  display.drawRect(1, 1, 126, 62, SSD1306_WHITE);


  // -----------------------------------------------------
  // TOP DAY
  // -----------------------------------------------------

  display.setTextSize(2);

  String dayName = daysOfWeek[now.dayOfTheWeek()];

  int dayWidth = dayName.length() * 12;

  int dayX = (128 - dayWidth) / 2;

  display.setCursor(dayX, 3);

  display.print(dayName);


  // -----------------------------------------------------
  // FIRST SEPARATOR LINE
  // -----------------------------------------------------

  display.drawLine(8, 15, 119, 15, SSD1306_WHITE);


  // -----------------------------------------------------
  // TIME
  // -----------------------------------------------------

  char timeString[6];

  sprintf(timeString,
          "%02d:%02d",
          hour12,
          now.minute());


  // Large time
  display.setTextSize(3);

  // 5 characters × 18 pixels = 90 pixels
  int timeX = 14;

  display.setCursor(timeX, 19);

  display.print(timeString);


  // -----------------------------------------------------
  // AM / PM
  // -----------------------------------------------------

  display.setTextSize(2);

  display.setCursor(104, 25);

  display.print(ampm);


  // -----------------------------------------------------
  // SECOND SEPARATOR LINE
  // -----------------------------------------------------

  display.drawLine(8, 44, 119, 44, SSD1306_WHITE);


  // -----------------------------------------------------
  // DATE
  // -----------------------------------------------------

  char dateString[12];

  sprintf(dateString,
          "%02d %s %04d",
          now.day(),
          months[now.month() - 1],
          now.year());


  display.setTextSize(1);

  // Center date
  int dateWidth = strlen(dateString) * 6;

  int dateX = (128 - dateWidth) / 2;

  display.setCursor(dateX, 51);

  display.print(dateString);


  // -----------------------------------------------------
  // UPDATE OLED
  // -----------------------------------------------------

  display.display();


  // Update every second
  delay(1000);
}