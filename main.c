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

// Function prototypes
void initFireSystem(FireDetectionSystem* system);
void readSensors(FireDetectionSystem* system);
void displayData(FireDetectionSystem* system);
void checkStatus(FireDetectionSystem* system);
void controlComponent(int pin, bool state);
void activateAlert(FireDetectionSystem* system);
void deactivateAlert(FireDetectionSystem* system);

// Function to initialize the components
void initFireSystem(FireDetectionSystem* system) {
    pinMode(system->buzzer, OUTPUT);
    pinMode(system->ledRed, OUTPUT);
    pinMode(system->ledGreen, OUTPUT);
    for (int i = 0; i < 2; i++) {
        pinMode(system->motor[i], OUTPUT);
    }
}

// Function to read sensor values
void readSensors(FireDetectionSystem* system) {
    system->temperatureSensor.value = analogRead(system->temperatureSensor.pin) * (500.0 / 1023.0);
    system->gasSensor.value = analogRead(system->gasSensor.pin);

    Serial.print("Temperature (C): ");
    Serial.print(system->temperatureSensor.value, 1);
    Serial.print(" | Gas: ");
    Serial.println(system->gasSensor.value);
}

// Function to control components (simplifies digitalWrite logic)
void controlComponent(int pin, bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
}

// Function to display sensor data on the LCD
void displayData(FireDetectionSystem* system) {
    lcd.clear(); // Clear previous data

    // Display room temperature
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(system->temperatureSensor.value, 1);
    lcd.print("C");

    // Display gas value
    lcd.setCursor(0, 1);
    lcd.print("Gas: ");
    lcd.print(system->gasSensor.value);

    // Wait for 1 second to ensure gas value is visible
    delay(1000);

    // Display safety status
    lcd.clear(); // Clear the display before showing the status
    if (system->temperatureSensor.value < TEMP_THRESHOLD && system->gasSensor.value < GAS_THRESHOLD) {
       lcd.setCursor(0, 0); 
      lcd.print(SAFE_MSG);
    } else {
      	lcd.setCursor(0, 0);
        lcd.print(ALERT_MSG);
      	lcd.setCursor(0, 1);
      	lcd.print("Dial 101 immediately");
    }
}

// Function to activate alert state
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

// Function to deactivate alert state
void deactivateAlert(FireDetectionSystem* system) {
    controlComponent(system->motor[1], false);
    noTone(system->buzzer);
    controlComponent(system->ledRed, false);
    controlComponent(system->ledGreen, true);

    Serial.println("All systems off. Safe.");
}

// Function to check system status and take action
void checkStatus(FireDetectionSystem* system) {
    if (system->temperatureSensor.value < TEMP_THRESHOLD && system->gasSensor.value < GAS_THRESHOLD) {
        deactivateAlert(system);
    } else {
        activateAlert(system);
    }
}

// Setup function
void setup() {
    Serial.begin(9600);
    Serial.println("Fire Detection System\n");

    lcd.begin(16, 2);
    lcd.print("Fire Detection");
    lcd.setCursor(4, 1);
    lcd.print("System!!");
    delay(2000);
    lcd.clear();

    // Initialize system components
    initFireSystem(&fireDetectionSystem);
}
// Main loop
void loop() {
    // Read sensors
    readSensors(&fireDetectionSystem);

    // Display data
    displayData(&fireDetectionSystem);

    // Check system status and take appropriate action
    checkStatus(&fireDetectionSystem);

    delay(1000); // 1 second delay for stability
}
