# Metal-Detector-Robot

## Overview

The Metal Detector Robot is an innovative project that combines obstacle avoidance and metal detection capabilities. This robot utilizes various components like an ultrasonic sensor, Arduino Uno microcontroller, L293D motor driver shield, servo motor, and more to achieve its functionality.

## Features

### Obstacle Detection
The robot is equipped with an ultrasonic sensor that acts as its eyes. It sends out ultrasonic waves and measures the time taken for them to bounce back. By calculating this time, the robot can determine the distance to any obstacles in its path. This information is crucial for avoiding collisions and navigating through a complex environment.

### Metal Detection
The Metal Detector Robot is not just about obstacle avoidance; it can also detect metal objects. This feature is achieved using an RLC circuit, which operates based on Faraday's law. When a metal object comes near the coil in the RLC circuit, it induces a current in the coil. This change in current is detected and used to identify the presence of metal. This capability can be particularly useful in scenarios where finding hidden metallic objects is essential, such as in security applications or treasure hunting.

## Components Used

- **Arduino Uno:** The brains of the robot, responsible for processing sensor data and controlling motors.
- **L293D Motor Driver Shield:** This shield controls the four motors used for movement.
- **Servo Motor:** The servo motor provides precise control for various functions.
- **Chassis, Gears, and Motors:** These physical components form the robot's body and drive system.
- **Wheels:** Four wheels for smooth movement.
- **Resistors and Capacitors:** Used in the RLC circuit for metal detection.
- **Copper Coil:** The coil is a crucial part of the metal detection system.
- **Diode:** Used for circuit protection.
- **Buzzer:** A buzzer provides audio feedback, which can be customized based on robot actions.

## How It Works

1. **Obstacle Detection:** The ultrasonic sensor continuously sends out ultrasonic waves. When these waves hit an obstacle and bounce back, the sensor measures the time it takes for them to return. Based on this time measurement, the robot determines how far the obstacle is and adjusts its course accordingly to avoid collisions.

2. **Metal Detection:** The metal detection system, consisting of the RLC circuit and copper coil, works on the principle of electromagnetic induction. When a metal object comes close to the coil, it induces a current in the coil. This current change is detected, and the robot is programmed to respond in a specific way, such as sounding an alarm or triggering other actions.

## Applications

- **Security:** The metal detection capability can be valuable in security applications to locate concealed metallic objects.
- **Exploration:** This robot can be used in archaeological or treasure hunting expeditions to detect buried metallic artifacts.
- **Education:** It's a great educational tool for learning about sensors, circuits, and robotics.

## Getting Started

Follow the assembly and programming instructions in the project's documentation to build your Metal Detector Robot and start exploring its capabilities.

## License

This project is open-source and available under the [MIT License](LICENSE). Feel free to contribute, modify, and use it for your projects.

## Acknowledgments

I would like to express our gratitude to the open-source hardware and software communities for their invaluable contributions to this project. Additionally, I want to extend a special thanks to our teammates Arryan and Suchandra for their dedication and collaborative efforts in bringing this Metal Detector Robot project to fruition.

## Author
Pranay Desamsetti

## Contact
pranaydesamsetti@gmail.com 


