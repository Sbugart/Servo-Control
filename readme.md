## Purpose
This repository was created as a modular component for future robotics projects.

This repository provides a reusable servo control module designed to be integrated into larger embedded projects.

It implements PWM-based servo control using threads, making it easy to reuse in robotics or embedded systems.

The implementation was tested with the MG90S servo motor, which operates with the following pulse width limits:

- Minimum pulse width: 500 µs
- Maximum pulse width: 2500 µs

## Hardware
- ESP32-C3
- MG90S Servo Motor

## Features
- PWM control using LEDC
- Servo angle control
- Thread-based control structure