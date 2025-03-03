# ðŸ”¥ Fire Detection System using Arduino (Tinkercad)

## ðŸ“Œ Project Overview
This project implements a **Fire Detection and Alert System** using **Arduino UNO**, simulated in **Tinkercad**.  
The system detects **fire conditions** by monitoring **temperature** and **smoke intensity** using a temperature sensor and a gas sensor (used here as a **smoke/fire sensor**, not for gas leakage).

When fire is detected, the system activates an **alarm (buzzer)**, turns ON a **motor (water pump)**, switches ON a **red alert LED**, and displays warning messages on an **LCD screen**.

---

## ðŸŽ¯ Objectives
- Detect **fire or overheating conditions**
- Detect **smoke generated due to fire**
- Display real-time sensor readings on a **16Ã—2 LCD**
- Activate **alarm, motor, and LED indicators** during fire detection
- Simulate a fire safety system using **Tinkercad**

---

## ðŸ› ï¸ Components Used
- Arduino UNO
- Gas Sensor (used as smoke/fire detector)
- Temperature Sensor (LM35 / Analog)
- 16Ã—2 LCD Display
- Buzzer (Alarm)
- DC Motor / Water Pump
- Red LED (Alert)
- Green LED (Safe)
- Potentiometer (LCD contrast control)
- Breadboard
- Connecting wires

---

## ðŸ”Œ Pin Configuration
| Component | Arduino Pin |
|---------|------------|
| Smoke Sensor | A0 |
| Temperature Sensor | A1 |
| Buzzer | D8 |
| Green LED | D9 |
| Motor / Pump | D10, D11 |
| Red LED | D12 |
| LCD RS | D2 |
| LCD EN | D3 |
| LCD D4â€“D7 | D4â€“D7 |

---

## ðŸ§  System Working
1. Arduino continuously reads values from the **temperature sensor** and **smoke sensor**.
2. Sensor readings are displayed on the **LCD screen**.
3. The readings are compared with predefined **threshold values**:
   - Temperature > 50Â°C
   - Smoke level above threshold
4. If fire is detected:
   - Buzzer turns ON
   - Motor (water pump) activates
   - Red LED turns ON
   - Alert message is displayed on the LCD
5. If no fire is detected:
   - Green LED remains ON
   - System stays in safe mode

---

## ðŸ–¥ï¸ Software & Simulation
- Simulation Platform: **Tinkercad Circuits**
- Programming Language: **Embedded C (Arduino)**
- Library Used: **LiquidCrystal.h**


---

## ðŸ§ª Test Scenarios
| Condition | Expected Output |
|--------|----------------|
| Normal temperature, no smoke | Green LED ON |
| High temperature | Alarm + Motor ON |
| Smoke due to fire | Alarm + Motor ON |
| High temperature and smoke | Full alert system ON |