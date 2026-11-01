// Smart Field Alert System - GSM SMS version (SIM800L)
// Same LED + buzzer alert as the basic version, plus an SMS to the farmer.
// An SMS is sent at most once every SMS_COOLDOWN_MS.
//
// Wiring: PIR OUT -> D2 | Green LED -> D6 (220 ohm) | Red LED -> D7 (220 ohm)
//         Buzzer (active) -> D8
//         SIM800L TXD -> D10 (Arduino RX) | SIM800L RXD -> D11 (Arduino TX,
//         through a voltage divider, e.g. 1k + 2k, because the SIM800L is 3.3V logic)
//         SIM800L GND -> Arduino GND
//
// IMPORTANT: The SIM800L needs its own 3.7-4.2V supply that can give about 2A
// peaks (for example a LiPo battery or a good buck converter). The Arduino 5V
// pin cannot power it reliably. Put your own number in PHONE_NUMBER below.
//
// NOTE: Not tested on hardware. Compile and test it on your own board.

#include <SoftwareSerial.h>

#define PIR     2
#define RED     7
#define GREEN   6
#define BUZZER  8

#define GSM_RX  10   // Arduino RX  <- SIM800L TXD
#define GSM_TX  11   // Arduino TX  -> SIM800L RXD (use a voltage divider)

#define WARMUP_SECONDS   30
#define BUZZER_MAX_MS    10000UL
#define SMS_COOLDOWN_MS  60000UL

const char PHONE_NUMBER[] = "+8801XXXXXXXXX";   // <-- change to the farmer's number

SoftwareSerial gsm(GSM_RX, GSM_TX);

bool lastMotion = false;
unsigned long alertStart = 0;
unsigned long lastSmsTime = 0;
bool smsEverSent = false;

void sendSms(const char *text) {
  gsm.println("AT+CMGF=1");           // text mode
  delay(500);
  gsm.print("AT+CMGS=\"");
  gsm.print(PHONE_NUMBER);
  gsm.println("\"");
  delay(1000);
  gsm.print(text);
  delay(200);
  gsm.write(26);                      // Ctrl+Z ends the message
  delay(3000);
  Serial.println("SMS sent (check your phone).");
}

void setup() {
  pinMode(PIR, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  gsm.begin(9600);

  Serial.println("PIR warming up...");
  for (int i = 0; i < WARMUP_SECONDS; i++) {
    digitalWrite(GREEN, HIGH);
    delay(500);
    digitalWrite(GREEN, LOW);
    delay(500);
  }
  gsm.println("AT");                  // wake up the module
  delay(500);
  Serial.println("System ready. Field is secure.");
}

void loop() {
  bool motion = (digitalRead(PIR) == HIGH);

  if (motion) {
    if (!lastMotion) {
      alertStart = millis();
      Serial.println("Alert! Motion Detected!");
    }
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BUZZER, (millis() - alertStart < BUZZER_MAX_MS) ? HIGH : LOW);

    if (!smsEverSent || millis() - lastSmsTime >= SMS_COOLDOWN_MS) {
      sendSms("ALERT: Motion detected in your field!");
      lastSmsTime = millis();
      smsEverSent = true;
    }
  } else {
    if (lastMotion) {
      Serial.println("Field clear.");
    }
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BUZZER, LOW);
  }

  lastMotion = motion;
  delay(100);
}
