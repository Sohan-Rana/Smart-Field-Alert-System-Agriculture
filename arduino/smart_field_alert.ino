// Smart Field Alert System
// PIR Sensor (HC-SR501) + Red/Green LED + Active Buzzer
// Wiring: PIR OUT -> D2 | Green LED -> D6 | Red LED -> D7 | Buzzer -> D8
// Each LED needs a 220 ohm resistor in series.

#define PIR     2
#define RED     7
#define GREEN   6
#define BUZZER  8

#define WARMUP_SECONDS 30

bool lastMotion = false;

void setup() {
  pinMode(PIR, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);

  // PIR needs time to calibrate after power-up.
  // The green LED blinks while the sensor warms up.
  Serial.println("PIR warming up...");
  for (int i = 0; i < WARMUP_SECONDS; i++) {
    digitalWrite(GREEN, HIGH);
    delay(500);
    digitalWrite(GREEN, LOW);
    delay(500);
  }
  Serial.println("System ready. Field is secure.");
}

void loop() {
  bool motion = (digitalRead(PIR) == HIGH);

  if (motion) {
    // Motion detected: alert!
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BUZZER, HIGH);
    if (!lastMotion) {
      Serial.println("Alert! Motion Detected!");
    }
  } else {
    // Normal condition
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BUZZER, LOW);
    if (lastMotion) {
      Serial.println("Field clear.");
    }
  }

  lastMotion = motion;
  delay(100);
}
