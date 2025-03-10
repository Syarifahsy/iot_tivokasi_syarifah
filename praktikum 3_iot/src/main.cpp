#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define LDRPIN 32

#define SDA_PIN 21
#define SCL_PIN 22
LiquidCrystal_I2C lcd(0x27, 16, 2);

void scanI2C() {
    Serial.println("Scanning I2C...");
    for (byte addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            Serial.print("Found device at: 0x");
            Serial.println(addr, HEX);
        }
    }
}

void setup() {
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);
    delay(100);

    scanI2C();

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Sensor ESP32");
    delay(2000);
    lcd.clear();

    dht.begin();
}

void loop() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    int lightIntensity = analogRead(LDRPIN);

    Serial.print("Temp: "); Serial.print(temperature); Serial.print(" C, ");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.print(" %, ");
    Serial.print("Light: "); Serial.println(lightIntensity);

    lcd.setCursor(0, 0);
    lcd.print("T:"); lcd.print(temperature, 1); lcd.print("C H:"); lcd.print(humidity, 0); lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Light:"); lcd.print(lightIntensity);
    
    delay(2000);
}
