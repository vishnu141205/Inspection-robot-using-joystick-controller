#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo pulse range
#define SERVOMIN 150
#define SERVOMAX 600

// Joystick
#define JOY_X A0
#define JOY_Y A1

int DEADZONE = 100;

int center[8] = {90,90,90,90,90,90,90,90};

// Convert angle to PCA9685 pulse
int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setServo(int ch, int angle) {
  pwm.setPWM(ch, 0, angleToPulse(angle));
}

void moveLeg(int hip, int knee, int hipAngle, int kneeAngle) {
  setServo(hip, hipAngle);
  setServo(knee, kneeAngle);
}

void stand() {
  for(int i=0;i<8;i++)
    setServo(i, center[i]);
}

// ================= FORWARD =================
int STEP = 30;
int LIFT = 25;

void stepForward() {

 
  moveLeg(0,1, center[0] + STEP, center[1] - LIFT);
  moveLeg(6,7, center[6] - STEP, center[7] - LIFT);
  delay(150);

  
  moveLeg(0,1, center[0] - STEP, center[1]);
  moveLeg(6,7, center[6] + STEP, center[7]);
  delay(150);

  moveLeg(2,3, center[2] - STEP, center[3] - LIFT);
  moveLeg(4,5, center[4] + STEP, center[5] - LIFT);
  delay(150);

 
  moveLeg(2,3, center[2] + STEP, center[3]);
  moveLeg(4,5, center[4] - STEP, center[5]);
  delay(150);
}
// ================= BACKWARD =================
void stepBackward() {

  moveLeg(0,1, center[0] - STEP, center[1] - LIFT);
  moveLeg(6,7, center[6] + STEP, center[7] - LIFT);
  delay(150);

  moveLeg(0,1, center[0] + STEP, center[1]);
  moveLeg(6,7, center[6] - STEP, center[7]);
  delay(150);

  moveLeg(2,3, center[2] + STEP, center[3] - LIFT);
  moveLeg(4,5, center[4] - STEP, center[5] - LIFT);
  delay(150);

  moveLeg(2,3, center[2] - STEP, center[3]);
  moveLeg(4,5, center[4] + STEP, center[5]);
  delay(150);
}

// ================= TURN LEFT =================
void turnLeft() {
  
  moveLeg(0,1, center[0]-STEP, center[1]-LIFT);  
  moveLeg(6,7, center[6]+STEP, center[7]-LIFT);  
  delay(250);
  moveLeg(0,1, center[0]-STEP, center[1]);       
  moveLeg(6,7, center[6]+STEP, center[7]);
  delay(250);
  
 
  moveLeg(2,3, center[2]-STEP, center[3]-LIFT);  
  moveLeg(4,5, center[4]+STEP, center[5]-LIFT);  
  delay(250);
  moveLeg(2,3, center[2]-STEP, center[3]);       
  moveLeg(4,5, center[4]+STEP, center[5]);
  delay(250);
}

// ================= TURN RIGHT =================
void turnRight() {

  moveLeg(0,1, center[0]+STEP, center[1]-LIFT);  
  moveLeg(6,7, center[6]-STEP, center[7]-LIFT);  
  delay(250);
  moveLeg(0,1, center[0]+STEP, center[1]);
  moveLeg(6,7, center[6]-STEP, center[7]);
  delay(250);
  
 
  moveLeg(2,3, center[2]+STEP, center[3]-LIFT);  
  moveLeg(4,5, center[4]-STEP, center[5]-LIFT);  
  delay(250);
  moveLeg(2,3, center[2]+STEP, center[3]);
  moveLeg(4,5, center[4]-STEP, center[5]);
  delay(250);
}



void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(1000);
  stand();
}


void loop() {
  // --- 1. PRIORITY: Serial Commands from YOLO ---
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim(); 
    
    if (command == "person") {
      Serial.println("Action: Person detected!");
    } 
    
    delay(50);
    
  }

  // --- 2. SECONDARY: Joystick Control ---
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  // Deadzone logic
  if (abs(x - 512) < DEADZONE) x = 512;
  if (abs(y - 512) < DEADZONE) y = 512;

  if (x > 900) {
    stepBackward();
  } else if (x < 100) {
    stepForward();
  } else if (y < 100) {
    turnLeft();
  } else if (y > 900) {
    turnRight();
  } else {
    // Only stand still if no joystick input AND no active serial command
    if (Serial.available() == 0) {
      stand();
    }
  }
}