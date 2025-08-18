#include <Servo.h>

Servo servo1;  // Base
Servo servo2;  // Shoulder
Servo servo3;  // Elbow
Servo servo4;  // Wrist
Servo servo5;  // Wrist2
Servo servo6;  // Gripper

void setup() {
  Serial.begin(9600);
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo5.attach(10);
  servo6.attach(11);
  delay(1000);

  // Move to home
  servo1.write(0);
  servo2.write(30);
  servo3.write(0);
  servo4.write(70);
  servo5.write(0);
  servo6.write(1);
  Serial.println("✅ Arm at home position");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int angles[6];
    int count = 0;
    int lastIndex = 0;
    for (int i = 0; i < input.length(); i++) {
      if (input.charAt(i) == ',') {
        angles[count++] = input.substring(lastIndex, i).toInt();
        lastIndex = i + 1;
      }
    }
    angles[count] = input.substring(lastIndex).toInt();

    if (count == 5) {
      servo1.write(constrain(angles[0], 0, 180));
      servo2.write(constrain(angles[1], 0, 180));
      servo3.write(constrain(angles[2], 0, 180));
      servo4.write(constrain(angles[3], 0, 180));
      servo5.write(constrain(angles[4], 0, 180));
      servo6.write(constrain(angles[5], 0, 180));
      Serial.print("✅ Moved to angles: ");
      Serial.println(input);
    } else {
      Serial.println("❌ Invalid angle data");
    }
  }
}

