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

//LCD object
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Global fire detection system object
FireDetectionSystem fireDetectionSystem = {
    .motor = {10, 11},
    .ledRed = 12,
    .ledGreen = 9,
    .buzzer = 8,
    .temperatureSensor = {A1, 0.0},
    .gasSensor = {A0, 0.0}
};

void initFireSystem(FireDetectionSystem* system) {
    pinMode(system->buzzer, OUTPUT);
    pinMode(system->ledRed, OUTPUT);
    pinMode(system->ledGreen, OUTPUT);
    for (int i = 0; i < 2; i++) {
        pinMode(system->motor[i], OUTPUT);
    }
}

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    initFireSystem(&fireDetectionSystem);
}

void loop() {
    delay(1000);
}