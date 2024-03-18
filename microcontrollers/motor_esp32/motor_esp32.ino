#include <ESP32Servo.h>

const int left_in1 = 27;
const int left_in2 = 26; 
const int leftEnable = 25; 

const int right_in3 = 32;
const int right_in4 = 33; 
const int rightEnable = 13; 

//Servo leftServo;
int leftServoPin = 14;


// setting PWM properties
const int freq = 50;
const int leftMotor = 2;
const int rightMotor = 0;

const int servo = 4;

const int servoOpened = 5;
const int servoClosed = 30;



const int resolution = 8;

#define TURNING_TIME "250"
#define STOP_TIME 100      

#define DEFAULT_SPEED "120"
 
void setup(){
    // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  pinMode(left_in1, OUTPUT);
  pinMode(left_in2, OUTPUT);  
  pinMode(leftEnable, OUTPUT);  
 
  pinMode(right_in3, OUTPUT);
  pinMode(right_in4, OUTPUT);
  pinMode(rightEnable, OUTPUT);  
  
  // configure LED PWM functionalitites
  ledcSetup(leftMotor, freq, resolution);
  ledcSetup(rightMotor, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(leftEnable, leftMotor);
  ledcAttachPin(rightEnable, rightMotor);

  ledcSetup(servo, freq, resolution);
  ledcAttachPin(leftServoPin, servo);
//  leftServo.setPeriodHertz(50);    // standard 50 hz servo
//  leftServo.attach(leftServoPin, 500, 2400); 
//
  ledcWrite(servo, servoOpened);
  Serial.begin(115200); 
}



void allStop() {
  digitalWrite(left_in1, 0);
  digitalWrite(left_in2, 0);
  digitalWrite(right_in3, 0);
  digitalWrite(right_in4, 0);
}

void loop(){
  if(Serial.available()){
    String full_command = Serial.readStringUntil('\n');
    int i1 = full_command.indexOf(',');
    int i2 = full_command.indexOf(',', i1+1);
    String cmd_arg = DEFAULT_SPEED;
    String cmd_arg2 = TURNING_TIME;
    String command = full_command;
    if (i1 > 0) {
      command= full_command.substring(0, i1);
      if (i2 > 0) {
        cmd_arg = full_command.substring(i1+1, i2);
        cmd_arg2 =  full_command.substring(i2+1);

      } else {
        cmd_arg = full_command.substring(i1+1);
      }
    }
    int turningSpeed = cmd_arg.toInt();
    int turningTime = cmd_arg2.toInt();

    Serial.printf("Command received %s, arg1=%s, arg2=%s \n", command, cmd_arg, cmd_arg2);
    if (command.equals("left")) {
      allStop();
      digitalWrite(left_in1, HIGH);
      digitalWrite(right_in3, HIGH);
      ledcWrite(leftMotor, turningSpeed);
      ledcWrite(rightMotor, turningSpeed);
      delay(turningTime);
      allStop();
      delay(STOP_TIME);
    } else if (command.equals("right")) {
      allStop();
      digitalWrite(left_in2, HIGH);
      digitalWrite(right_in4, HIGH);
      ledcWrite(leftMotor, turningSpeed);
      ledcWrite(rightMotor, turningSpeed);
      delay(turningTime);
      allStop();
      delay(STOP_TIME);
    } else if (command.equals("stop")) {
      allStop();
    } else if (command.equals("ahead")) {
      allStop();
      digitalWrite(left_in2, HIGH);
      digitalWrite(right_in3, HIGH);
      ledcWrite(leftMotor, turningSpeed);
      ledcWrite(rightMotor, turningSpeed);
    } else if (command.equals("open_gate")) {
      ledcWrite(servo, servoOpened);
    } else if (command.equals("close_gate")) {
      ledcWrite(servo, servoClosed);
//       leftServo.write(leftServoClosed);
    }
  }


}
