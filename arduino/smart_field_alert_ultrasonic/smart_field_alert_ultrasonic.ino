// Smart Field Alert System - PIR + Ultrasonic version
// An alert is raised only when the PIR sees motion AND the
// ultrasonic sensor (HC-SR04) measures something closer than ALERT_DISTANCE_CM.
// This reduces false alarms from far-away movement. The buzzer stops
// after BUZZER_MAX_MS even if motion continues.
//
// Wiring: PIR OUT -> D2 | Green LED -> D6 (220 ohm) | Red LED -> D7 (220 ohm)
//         Buzzer (active) -> D8 | HC-SR04 TRIG -> D9 | HC-SR04 ECHO -> D10
//         PIR / HC-SR04 VCC -> 5V, GND -> GND
//
// NOTE: Not tested on hardware. Compile and test it on your own board.

#define PIR     2
#define RED     7
#define GREEN   6
#define BUZZER  8
#define TRIG    9
#define ECHO    10

#define WARMUP_SECONDS     30
#define ALERT_DISTANCE_CM  150
#define BUZZER_MAX_MS      10000UL

bool alertActive = false;
unsigned long alertStart = 0;

// Returns distance in cm, or -1 if no echo was received.
long readDistanceCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000UL);  // 30 ms timeout (~5 m)
  if (duration == 0) return -1;
  return (long)(duration * 0.0343 / 2.0);
}

void setup() {
  pinMode(PIR, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);

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
  long distance = -1;
  bool intruder = false;

  if (motion) {
    distance = readDistanceCm();
    intruder = (distance > 0 && distance <= ALERT_DISTANCE_CM);
  }

  if (intruder) {
    if (!alertActive) {
      alertActive = true;
      alertStart = millis();
      Serial.print("Alert! Intruder at ");
      Serial.print(distance);
      Serial.println(" cm");
    }
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    // Buzzer sounds only for BUZZER_MAX_MS, then stays silent until reset
    digitalWrite(BUZZER, (millis() - alertStart < BUZZER_MAX_MS) ? HIGH : LOW);
  } else {
    if (alertActive) {
      alertActive = false;
      Serial.println("Field clear.");
    }
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BUZZER, LOW);
  }

  delay(100);
}
