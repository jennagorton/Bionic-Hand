<h1 align="center">Bionic Hand</h1>
<p align="center">Jenna Gorton, July 2025</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/f601ad8c-18e4-4f91-ac03-f83e57e84e80"
       alt="workingTest" width="420">
</p>
<p align="center">Opening and closing fist with button input</p>

About
==
In this project, I designed and built a bionic hand controlled by user input. I undertook this challenge to enhance my skills in CAD design, programming, and electronics. While only using my laptop, 3D printer, and Arduino, I was able to bring this idea to life. The primary goals were to achieve realistic hand motion and enable both independent and simultaneous control of individual fingers, while staying within a low budget.

<p align="center">
  <img src="https://github.com/user-attachments/assets/f50e57e2-b567-4774-af4b-3b592ba4cc88"
       alt="workingTest" width="420">
</p>

Design
==
The design incorporates compliant fingers, palm-integrated motors, a capacitive touch interface, and a cable-concealing stand.
- To introduce compliance in the fingers, I fabricated the joints using TPU, while the rest of the structure was printed in PLA. This material combination allowed the fingers to bend under applied force and return to their original position, providing the strength of a rigid finger with the flexibility of a compliant one.
- By integrating the servos within the palm, the hand functions independently without requiring an attached arm. This compact, self-contained design ensures compatibility with various arm attachments—whether used as a prosthetic or as a component of a larger robotic system.

Programming  
==

The bionic hand is controlled using an **Adafruit 16-Channel PWM Servo Driver** (PCA9685) and an Arduino. Each finger is assigned to a dedicated servo motor, which the driver addresses through I²C communication. The servos are configured with defined pulse-width ranges to open and close the fingers smoothly.  

### Key Features  
- **Finger Control**  
  The top row of capacitive touch sensors each corresponds to a specific finger. When touched, the associated servo toggles between open and closed positions, where the servo controls the closure, and the compliance pulls the finger open.

- **Predefined Gestures**  
  The second row of touch sensors allows for more complex motions:  
  - **Close Fist** – Sequentially closes all five fingers.  
  - **Open Hand** – Sequentially opens all five fingers.  
  - **Peace Sign** – Closes the thumb, ring, and pinky while opening the index and middle fingers.  

- **State Tracking**  
  Finger positions are tracked with global variables (`indexPos`, `thumbPos`, etc.) to prevent conflicting commands and allow toggling.  

- **Smooth Motion**  
  Servo positions are updated incrementally with small delays to create natural, fluid finger movements instead of abrupt snapping.  

### Example: Peace Sign Gesture  
Below is the function that creates a **peace sign** when the corresponding touch sensor is pressed:  

```cpp
if (c4r2 == 1) { // Peace sign gesture
  for (uint16_t pulselen = SERVOMAX, pulseopp = SERVOMIN; 
       pulselen > SERVOMIN && pulseopp < SERVOMAX; 
       pulselen--, pulseopp++) {
    // Closing thumb, ring, pinky
    if (thumbPos == 0) pwm.setPWM(THUMB, 0, pulselen);
    if (ringPos == 0)  pwm.setPWM(RING, 0, pulselen);
    if (pinkyPos == 0) pwm.setPWM(PINKY, 0, pulselen);

    // Opening index, middle
    if (middlePos == 1) pwm.setPWM(MIDDLE, 0, pulseopp);
    if (indexPos == 1)  pwm.setPWM(INDEX, 0, pulseopp);

    delay(3); // Smooth motion
  }
  indexPos = middlePos = 0; // Open
  ringPos = pinkyPos = thumbPos = 1; // Closed
}

```
Demo
==
The fingers can be configured to create any hand gesture 

| <div align="center">![GIF 1](https://github.com/user-attachments/assets/6bfcbe33-06f2-4777-a149-9dc311425ca3)<br></div> | <div align="center">![GIF 2](https://github.com/user-attachments/assets/d395dfa5-f051-4d73-8600-d89baa14dd21)<br></div> |
|---|---|
| <div align="center">![GIF 3](https://github.com/user-attachments/assets/6c6e3028-d866-42da-94da-07117bd4202b)<br></div> | <div align="center">![GIF 4](https://github.com/user-attachments/assets/4df38f67-b705-4f12-80ea-dc7b00007f68)<br></div> |











