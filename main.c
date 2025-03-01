#include <LiquidCrystal.h>

#define GAS_THRESHOLD 900
#define TEMP_THRESHOLD 50 
#define SAFE_MSG "Status: Safe  "
#define ALERT_MSG "Status: ALERT "

//structure for sensors
typedef struct {
    int pin;
    float value;
} Sensor;

//structure for the system's components
typedef struct {
    int motor[2];
    int ledRed;
    int ledGreen;
    int buzzer;
    Sensor temperatureSensor;
    Sensor gasSensor;
} FireDetectionSystem;

void setup() {
    Serial.begin(9600);
}

void loop() {
    delay(1000);
}