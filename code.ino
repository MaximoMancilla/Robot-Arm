#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

int channels[] = {0, 3, 6, 9, 12, 13, 15};

void setup() {
  Serial.begin(115200);
  pwm.begin();
  pwm.setPWMFreq(60);
  
  Serial.println("=== Robot Arm WebSerial Ready ===");
  Serial.println("Channels: 0,3,6,9,12,13,15");
  
  // Center on startup
  for(int i = 0; i < 7; i++) {
    int center = (channels[i] == 15) ? 455 : 375;
    pwm.setPWM(channels[i], 0, center);
  }
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    
    if (cmd.indexOf(':') != -1) {
      int ch = cmd.substring(0, cmd.indexOf(':')).toInt();
      int pulse = cmd.substring(cmd.indexOf(':') + 1).toInt();
      
      // Validate
      if (pulse >= 125 && pulse <= 625) {
        pwm.setPWM(ch, 0, pulse);
        Serial.print("Moved Ch");
        Serial.print(ch);
        Serial.print(" to ");
        Serial.println(pulse);
      }
    }
  }
}