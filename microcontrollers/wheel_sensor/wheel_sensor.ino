
#define timeSeconds 2


const int led = 2;
const int leftTickSensor = 19;
const int rightTickSensor = 23;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;

// Checks if motion was detected, sets LED HIGH and starts a timer
void IRAM_ATTR detectsLeftTick() {
  // digitalWrite(led, HIGH);
  Serial.println("left_tick");
}

void IRAM_ATTR detectsRightTick() {
  // digitalWrite(led, HIGH);
  Serial.println("right_tick");
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  pinMode(leftTickSensor, INPUT_PULLUP);
  pinMode(rightTickSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(leftTickSensor), detectsLeftTick, RISING);
  attachInterrupt(digitalPinToInterrupt(rightTickSensor), detectsRightTick, RISING);

  // Set LED to LOW
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  // Current time
  now = millis();
  if((digitalRead(led) == HIGH) && (motion == false)) {
    Serial.println("MOTION DETECTED!!!");
    motion = true;
  }
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("Motion stopped...");
    digitalWrite(led, LOW);
    startTimer = false;
    motion = false;
  }
}
