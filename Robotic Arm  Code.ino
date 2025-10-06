#include <Servo.h>

// Define servo objects for each motor
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristServo;

// Set initial positions for servos (adjust as needed)
int basePos = 180, shoulderPos = 0, elbowPos = 0, wristPos = 0;

// Movement increments for smoother control
const int movementStep = 5;  // Adjust for desired speed

// Optional: Define control method (e.g., button pins, serial commands)
const int controlMethod = 0;  // 0: Manual buttons, 1: Serial commands (modify)

// Define button pins for manual control (if using, replace with actual pins)
const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;

void setup() {
  // Attach servos to their respective pins (replace pin numbers if needed)
  baseServo.attach(9);
  shoulderServo.attach(10);
  elbowServo.attach(11);
  wristServo.attach(12);

  // Optional: Set up buttons as inputs (if using manual control)
  if (controlMethod == 0) {
    pinMode(button1Pin, INPUT);
    pinMode(button2Pin, INPUT);
    pinMode(button3Pin, INPUT);
    pinMode(button4Pin, INPUT);
  }
}

void loop() {
  // Control logic based on chosen method (modify as needed)
  if (controlMethod == 0) {
    // Manual button control (remove if not used)
    manualButtonControl();
  } else if (controlMethod == 1) {
    // Implement serial communication for control (add code here)
    // You can receive commands from a computer to control movements
  }

  // Update servo positions
  baseServo.write(basePos);
  shoulderServo.write(shoulderPos);
  elbowServo.write(elbowPos);
  wristServo.write(wristPos);

  // Optional: Add delays between movements for smoother transitions
  delay(15);  // Adjust delay as needed
}

// Function for manual button control (optional)
void manualButtonControl() {
  if (digitalRead(button1Pin) == LOW) {
    basePos += movementStep;  // Move base servo in positive direction
  }
  if (digitalRead(button2Pin) == LOW) {
    basePos -= movementStep;  // Move base servo in negative direction
  }
  // Add similar button control logic for other servos (shoulder, elbow, wrist)
}
