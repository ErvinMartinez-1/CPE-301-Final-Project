🧊 Swamp Cooler Simulation – Register-Level Arduino Control
📌 Project Overview

This project simulates the behavior of a swamp cooler (evaporative cooling system) using an Arduino microcontroller.

Unlike typical Arduino projects that rely on high-level functions such as digitalWrite() and analogRead(), this system was built by directly configuring and manipulating hardware registers to control:

GPIO ports

ADC (Analog-to-Digital Converter)

Timers

Interrupts

The goal was to demonstrate low-level embedded systems understanding and precise hardware control.

🎯 Objectives

Implement a finite-state machine to model swamp cooler behavior.

Read temperature and humidity sensor inputs.

Control fan outputs.

Use interrupts for state transitions.

Configure registers manually instead of Arduino abstraction libraries.

Simulate realistic system behavior.

⚙️ System Architecture
Inputs

Temperature sensor (analog input via ADC register configuration)

Humidity sensor (analog input)

Push buttons (interrupt-driven state changes)

Outputs

Fan motor (PWM via timer registers)

Water pump control

Status LEDs

LCD display (optional, if used)

🧠 State Machine Design

The system operates using a finite state machine:

State	Description
Idle	System waiting for activation
Running	Fan + pump operating
Cooling	Active cooling based on sensor thresholds
Error	Triggered by invalid sensor readings

Each state transition is controlled via:

External interrupts.

Sensor threshold checks.

Timer-based events.

🔩 Register-Level Implementation

Instead of using Arduino’s built-in functions, this project directly manipulated:

DDRx registers (data direction control)

PORTx registers (output control)

PINx registers (input reading)

ADCSRA, ADMUX (ADC configuration)

TCCRnA, TCCRnB (timer configuration)

EIMSK, EICRA (external interrupts)

Example: Configuring a Pin as Output
DDRB |= (1 << DDB5);  // Set PB5 as output
PORTB |= (1 << PORTB5); // Set HIGH

This approach provides:

Faster execution.

Better hardware understanding.

Greater control over microcontroller behavior.

🛠️ Technologies Used

Microcontroller: Arduino (MEGA 2560 architecture)

Language: 

Development Environment: Arduino IDE

Serial Monitor for debugging

📊 Key Technical Takeaways

Low-level hardware abstraction

Bitwise operations mastery

Interrupt-driven architecture

Real-time system design

State machine implementation

Hardware-software interaction

🧪 Testing & Validation

Sensor values validated via Serial Monitor

Verified PWM duty cycle using oscilloscope (if applicable)

Simulated edge cases for state transitions

Manual debugging of register configurations

🚀 How to Run

1) Clone the repository

2) Open project in Arduino IDE

3) Upload to Arduino board

4) Use serial monitor to observe system states

5) Interact with input buttons to simulate behavior
