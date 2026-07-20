<div align="center">

# Embedded Digital Clock using AVR-GCC

### AVR-Based 24-Hour Digital Clock using Timer Interrupts and Multiplexed 7-Segment Displays



</div>

---

# Overview

This project implements a **24-hour digital clock** using the **ATmega328P (Arduino Uno)** programmed in **Embedded C with AVR-GCC**. The clock displays **hours, minutes, and seconds** on six multiplexed 7-segment displays using a **7447 BCD-to-7-segment decoder**.

The project demonstrates the use of timers, interrupts, GPIO programming, and display multiplexing in an embedded system.

---

# Features

* 24-Hour Time Format (HH:MM:SS)
* Timer1 Interrupt-Based Timekeeping
* Multiplexed 7-Segment Display
* 7447 BCD-to-7-Segment Decoder
* AVR-GCC Compatible

---

# Hardware Requirements

| Component                      |    Quantity |
| ------------------------------ | ----------: |
| Arduino Uno (ATmega328P)       |           1 |
| 7447 BCD Decoder               |           1 |
| Common Anode 7-Segment Display |           6 |
| Breadboard                     |           1 |
| Jumper Wires                   | As Required |

---

# Hardware Connections

| Arduino Pin | Function            |
| ----------- | ------------------- |
| PD2         | BCD A               |
| PD3         | BCD B               |
| PD4         | BCD C               |
| PD5         | BCD D               |
| PD6         | Hour Tens Enable    |
| PD7         | Hour Units Enable   |
| PB0         | Minute Tens Enable  |
| PB1         | Minute Units Enable |
| PB2         | Second Tens Enable  |
| PB3         | Second Units Enable |

---

# Software Architecture

```text
          Timer1 (1 Second)
                  │
                  ▼
          Timer Interrupt
                  │
                  ▼
      Update Hours/Minutes/Seconds
                  │
                  ▼
        Extract Individual Digits
                  │
                  ▼
          Send BCD to 7447
                  │
                  ▼
      Multiplex 7-Segment Displays
```

---

# How It Works

### Timer1

Timer1 is configured to generate an interrupt every **1 second**. This interrupt updates the clock without using software delays.

### Time Update

Each interrupt increments the seconds. When seconds reach **60**, minutes are incremented. Similarly, minutes increment hours, and after **23:59:59**, the clock resets to **00:00:00**.

### Multiplexing

Only one display is enabled at a time. The microcontroller rapidly switches between all six displays, making them appear continuously ON due to persistence of vision.

### 7447 Decoder

The microcontroller sends a 4-bit BCD value to the 7447 decoder, which converts it into the signals required to drive the corresponding 7-segment display.

---

# Directory Structure

```text
Embedded-Digital-Clock
│
├── clock.c
│
├── README.md
```

---


# Concepts Demonstrated

* Embedded C Programming
* AVR-GCC
* GPIO Programming
* Timer1
* Interrupts
* Display Multiplexing
* 7447 BCD Decoder
* Real-Time Embedded Systems

---

# Future Enhancements

* Time Setting Buttons
* Alarm Feature
* Stopwatch Mode
* RTC (DS3231) Integration
* Brightness Control using PWM
* PCB Design using KiCad

