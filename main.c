#include <LiquidCrystal.h>

#define GAS_THRESHOLD 900
#define TEMP_THRESHOLD 50 
#define SAFE_MSG "Status: Safe  "
#define ALERT_MSG "Status: ALERT "

void setup() {
    Serial.begin(9600);
}

void loop() {
    delay(1000);
}