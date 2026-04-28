# Swamp Cooler Simulation 
### Register-Level Arduino Control (Embedded Systems Project)

---

## Project Overview

This project simulates the behavior of a **swamp cooler (evaporative cooling system)** using an Arduino microcontroller.

Unlike traditional Arduino implementations that rely on high-level abstraction functions such as `digitalWrite()` and `analogRead()`, this system was built by **directly configuring and manipulating hardware registers** to control:

- GPIO Ports  
- Analog-to-Digital Converter (ADC)  
- Timers / PWM  
- External Interrupts  

The purpose of this project was to demonstrate low-level embedded systems understanding, efficient hardware control, and state-driven system design.

---

## Project Objectives

- Implement a finite state machine (FSM) to model swamp cooler behavior  
- Read temperature and humidity sensors using manual ADC configuration  
- Control fan and pump outputs using register manipulation  
- Implement interrupt-driven state transitions  
- Configure timers for PWM without Arduino helper functions  
- Simulate realistic operational logic  

---

## System Architecture

### Inputs
- Temperature Sensor (Analog via ADC registers)
- Humidity Sensor (Analog via ADC registers)
- Push Buttons (External Interrupts)

### Outputs
- Fan Motor (PWM via Timer registers)
- Water Pump (Digital output)
- Status LEDs
- Serial Monitor (Debug output)

---

## Finite State Machine

| State      | Description |
|------------|-------------|
| **Idle**   | System waiting for activation |
| **Running**| Fan and pump operating |
| **Cooling**| Active cooling based on sensor thresholds |
| **Error**  | Triggered by invalid sensor readings |

State transitions are controlled through:
- External interrupts
- Sensor threshold comparisons
- Timer-based conditions

---

## Register-Level Implementation

This project avoids Arduino abstraction layers and directly manipulates AVR registers including:

- `DDRx`  → Data Direction Registers  
- `PORTx` → Output Registers  
- `PINx`  → Input Registers  
- `ADMUX`, `ADCSRA` → ADC Configuration  
- `TCCRnA`, `TCCRnB` → Timer Configuration  
- `EIMSK`, `EICRA` → External Interrupt Control  

### Example: Configuring a Pin as Output

```c
DDRB |= (1 << DDB5);      // Set PB5 as output
PORTB |= (1 << PORTB5);   // Set PB5 HIGH
