#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE_WIDTH 150
#define SERVO_MAX_PULSE_WIDTH 600
#define GRADUAL_DELAY_INTERVAL 10 // Adjust this value for smoother gradual transitions

// Define the PCA9685 channel assignments
#define SERVO2_CHANNEL 0
#define SERVO3_CHANNEL 1
#define SERVO4_CHANNEL 2
#define SERVO5_CHANNEL 3
#define SERVO6_CHANNEL 4
#define SERVO7_CHANNEL 5

void gradualDelay(int targetMicros, int currentMicros, int interval) {
  while (currentMicros != targetMicros) {
    delayMicroseconds(interval);
    if (currentMicros < targetMicros) {
      currentMicros += interval;
      if (currentMicros > targetMicros) {
        currentMicros = targetMicros;
      }
    } else {
      currentMicros -= interval;
      if (currentMicros < targetMicros) {
        currentMicros = targetMicros;
      }
    }
  }
}

void setServoAngle(uint8_t servoNum, int targetAngle) {
  int targetMicros = map(targetAngle, 0, 180, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
  int currentMicros = pwm.getPWM(servoNum);

  if (currentMicros != targetMicros) {
    int steps = abs(targetMicros - currentMicros) / GRADUAL_DELAY_INTERVAL;
    int increment = (targetMicros > currentMicros) ? GRADUAL_DELAY_INTERVAL : -GRADUAL_DELAY_INTERVAL;

    for (int i = 0; i < steps; i++) {
      currentMicros += increment;
      pwm.setPWM(servoNum, 0, currentMicros);
      delayMicroseconds(GRADUAL_DELAY_INTERVAL);
    }

    pwm.setPWM(servoNum, 0, targetMicros); // Set the final position
  }
}

void setDefaultPositions() {
  setServoAngle(SERVO3_CHANNEL, 40);
  delay(2000);
  setServoAngle(SERVO4_CHANNEL, 150);
  delay(2000);
  setServoAngle(SERVO5_CHANNEL, 180);
  delay(2000);
  setServoAngle(SERVO6_CHANNEL, 90);
  delay(2000);
}

void turnLeft() {
  setServoAngle(SERVO2_CHANNEL, 0);
  delay(2000);
}

void turnRight() {
  setServoAngle(SERVO2_CHANNEL, 180);
  delay(2000);
}

void middlePosition() {
  setServoAngle(SERVO2_CHANNEL, 85);
  delay(2000);
}

void goDown() {
  setServoAngle(SERVO3_CHANNEL, 80);
  delay(2000);
  setServoAngle(SERVO4_CHANNEL, 120);
  delay(2000);
  setServoAngle(SERVO3_CHANNEL, 90);
  delay(2000);
  setServoAngle(SERVO4_CHANNEL, 160);
  delay(2000);
  setServoAngle(SERVO5_CHANNEL, 80);
  delay(2000);
  setServoAngle(SERVO3_CHANNEL, 110);
  delay(2000);
   setServoAngle(SERVO5_CHANNEL, 60);
  delay(2000);
  setServoAngle(SERVO3_CHANNEL, 120);
  delay(1000);
  setServoAngle(SERVO6_CHANNEL, 90);
  delay(1000);
  setServoAngle(SERVO3_CHANNEL, 130);
  delay(1000);
}

void openPosition() {
  setServoAngle(SERVO7_CHANNEL, 40);
  delay(3000);
}

void closePosition() {
  setServoAngle(SERVO7_CHANNEL, 90);
  delay(2000);
}

void TransistionPosition() {
  setServoAngle(SERVO3_CHANNEL, 45);
  delay(2000);
  setServoAngle(SERVO4_CHANNEL, 180);
  delay(2000);
}

void grabPosition() {
  setServoAngle(SERVO7_CHANNEL, 60);
  delay(2000);
}

void setup() {
  Serial.begin(9600);

  // Initialize PCA9685
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates

  delay(10);

  // Set default positions for all servos
  setDefaultPositions();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'L' || command == 'l') {
      turnLeft();
    } else if (command == 'R' || command == 'r') {
      turnRight();
    } else if (command == 'D' || command == 'd') {
      goDown();
    } else if (command == 'S' || command == 's') {
      setDefaultPositions();
    } else if (command == 'O' || command == 'o') {
      openPosition();
    } else if (command == 'C' || command == 'c') {
      closePosition();
    } else if (command == 'T' || command == 't') {
      TransistionPosition();
    } else if (command == 'M' || command == 'm') {
      middlePosition();
    } else if (command == 'G' || command == 'g') {
      grabPosition();
    }
    delay(50);  // Additional delay for smoother operation
  }
  // Additional code for your main loop logic goes here
}
