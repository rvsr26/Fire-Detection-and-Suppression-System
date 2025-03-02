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

void readSensors(FireDetectionSystem* system) {
    system->temperatureSensor.value = analogRead(system->temperatureSensor.pin) * (500.0 / 1023.0);
    system->gasSensor.value = analogRead(system->gasSensor.pin);

    Serial.print("Temperature (C): ");
    Serial.print(system->temperatureSensor.value, 1);
    Serial.print(" | Gas: ");
    Serial.println(system->gasSensor.value);
}

void controlComponent(int pin, bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
}

void activateAlert(FireDetectionSystem* system) {
    controlComponent(system->motor[1], true);
    controlComponent(system->motor[0], false);
    controlComponent(system->ledRed, true);
    controlComponent(system->ledGreen, false);
    tone(system->buzzer, 220, 100);

    Serial.println("Warning...!!!! Room temperature is high or gas detected");
    Serial.println("Need water!! Switch on water pump");
    Serial.println("Fire and Rescue: Dial 101 immediately");
}

void deactivateAlert(FireDetectionSystem* system) {
    controlComponent(system->motor[1], false);
    noTone(system->buzzer);
    controlComponent(system->ledRed, false);
    controlComponent(system->ledGreen, true);

    Serial.println("All systems off. Safe.");
}

void checkStatus(FireDetectionSystem* system) {
    if (system->temperatureSensor.value < TEMP_THRESHOLD && system->gasSensor.value < GAS_THRESHOLD) {
        deactivateAlert(system);
    } else {
        activateAlert(system);
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("Fire Detection System\n");
    lcd.begin(16, 2);
    initFireSystem(&fireDetectionSystem);
}

void loop() {
    readSensors(&fireDetectionSystem);
    checkStatus(&fireDetectionSystem);
    delay(1000);
}