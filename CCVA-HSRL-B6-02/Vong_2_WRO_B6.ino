#include "MatrixMiniR4.h"
#include <algorithm> 

unsigned int visionBuffer[10];
float previousError = 0;
int objectColor, objectX, objectY, previousColor, checkpointCount = 0, detectedLineColor = 10, trackingStep = 0, encoderCheckpoint = 0;
bool finishFlag = false;
int greenCenter, redCenter, startLine, endLine, moveDirection, previousPosition, backupTimer = 0;

// Hằng số
const int Y_IGNOR = 50; // Vị trí tối thiểu để đọc khối theo trục Y (nếu xa hơn sẽ không đọc)
const int DOOR = 12; // Điều kiện kết thúc vòng chạy
const int d = 19.6;


// Giới hạn góc xoay
float clampValue(float value, float min, float max) {
  if (value < min) value = min;
  if (value > max) value = max;
  return value;
}

/*
  Tính toán vị trí xoay
  value: góc muốn xoay (0 = đi thẳng)
  l: giới hạn góc xoay
*/
void steerServo(float value, float l = 70) {
  float diff = 90 + clampValue(value, -l, l);
  MiniR4.RC1.setAngle(diff);
}

// dò đường trái
void followLeftWall(float khoang_cach, float kp, float kd) {
  float error = khoang_cach - MiniR4.I2C1.MXLaserV2.getDistance() / 10;
  float D = error - previousError;
  float PID = error * kp + D * kd;
  steerServo(PID, 45);
  previousError = error;
}

// dò đường phải
void followRightWall(float khoang_cach, float kp, float kd) {
  float error = MiniR4.I2C2.MXLaserV2.getDistance() / 10 - khoang_cach;
  float D = error - previousError;
  float PID = error * kp + D * kd;
  steerServo(PID, 45);
  previousError = error;
}

// Kiểm tra điều kiện kết thúc nếu: đi đủ khoảng cách + chạm đường xanh cam hoặc vòng đầu tiên + chạm đường xanh cam
void checkLine() {
  detectedLineColor = MiniR4.I2C3.MXColorV3.getColorID();

  if ((abs(encoderCheckpoint - MiniR4.M1.getDegrees()) * d / 360 > 100 and (detectedLineColor == 9 or detectedLineColor == 3)) or (checkpointCount == 0 and (detectedLineColor == 9 or detectedLineColor == 3))) {
    checkpointCount++;
    encoderCheckpoint = MiniR4.M1.getDegrees();
  }
}

// Khi đi tới vị trí góc sa bàn (ở giữa 2 đường xanh cam) robot sẽ xoay 1 góc rộng để quét các khối tiếp theo (nếu có)
bool scanTurn() {
  bool check = false; // Kiểm tra xem đã đến góc sa bàn chưa
    if (detectedLineColor == startLine and checkpointCount != DOOR) {
    
    previousError = 0; 
    check = true;
    MiniR4.LED.setColor(1, 255,255, 0);
    MiniR4.Vision.Data(visionBuffer);
      objectColor = visionBuffer[0];
      objectY = visionBuffer[2];
      if (objectY < Y_IGNOR) objectColor = 255;
      // Nếu không có khối nào tiếp theo
      if (objectColor == 255) {
        int startDegrees = abs(MiniR4.M1.getDegrees());
        // Vừa đi vừa xoay 1 góc rộng ví dụ 0 -> 42 để quét xem liệu có màu để bám theo ko
        int turn_angle = 15;
        while (detectedLineColor != endLine and abs(MiniR4.M1.getDegrees() - startDegrees) * d / 360 <= 30) {
          
          checkLine();

          // MiniR4.Vision.Data(visionBuffer);

          // objectColor = visionBuffer[0];
          // objectY = visionBuffer[2];
          // if (objectY < Y_IGNOR) objectColor = 255;
          // if (objectColor != 255) {
          //   MiniR4.LED.setColor(1, 255, 0, 255);
          //     checkLine();
          //     return check;
          // } 
          
          steerServo(turn_angle * moveDirection);
          if (turn_angle <= 45) {
            turn_angle += 15;
          }

          MiniR4.M1.setSpeed(20);

          detectedLineColor = MiniR4.I2C3.MXColorV3.getColorID();
          Serial.print(startDegrees);
          Serial.print(" ");
          Serial.print(MiniR4.M1.getDegrees());
          Serial.print(" ");
          Serial.println(abs(MiniR4.M1.getDegrees() - startDegrees) * d / 360);
        }
        if (objectColor == 255) {
        int turn_back = min(abs(MiniR4.M1.getDegrees() - startDegrees) * d / 360 / 3, 10);
          startDegrees = abs(MiniR4.M1.getDegrees());
          while (abs(MiniR4.M1.getDegrees() - startDegrees) * d / 360 <= turn_back) {
            MiniR4.M1.setSpeed(-20);
            MiniR4.Vision.Data(visionBuffer);
            steerServo(-40 * moveDirection);

            // objectColor = visionBuffer[0];
            // objectY = visionBuffer[2];
            // if (objectY < Y_IGNOR) objectColor = 255;
            // if (objectColor != 255) break;
          }
          MiniR4.M1.setSpeed(20);  
        }
      }

      detectedLineColor = MiniR4.I2C3.MXColorV3.getColorID();
  }
  checkLine();
  return check;
}
// Một khối chờ cho việc đi mù nếu gặp được khối nào đó thì sẽ bỏ qua và trực tiếp bám khối
bool moveCM(float quang_duong) {
  previousError = 0;
  int startDegrees = abs(MiniR4.M1.getDegrees());
  while(abs(MiniR4.M1.getDegrees() - startDegrees) * d / 360 <= quang_duong) {
    if(scanTurn()) {
      return false;
    }
  }
  return true;
}

void processLastStep(bool check = true) {
  if (finishFlag) {
    MiniR4.M1.setSpeed(30);
    if (moveCM(previousColor == 0 ? 10 : 13) && check) {
      if (previousColor == 1) {
        steerServo(-45);
        moveCM(8);
      } else if (previousColor == 0) {
        steerServo(45);
        moveCM(5);
      }
    }
    finishFlag = false;
    previousError = 0;
    previousColor = 255;
  } 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MiniR4.begin();
  MiniR4.M1.setReverse(false);
  MiniR4.RC1.begin();
  MiniR4.RC1.setHWDir(true);
  MiniR4.I2C1.MXLaserV2.begin();
  MiniR4.I2C2.MXLaserV2.begin();
  MiniR4.I2C3.MXColorV3.begin();
  MiniR4.Vision.Begin();
  MiniR4.Vision.reset();
}

void loop() {

  while (true) {
    if (MiniR4.BTN_DOWN.getState()) {
      while(1) {
        MiniR4.Vision.Data(visionBuffer);
      }
    } else if (MiniR4.BTN_UP.getState()) {
      break;
    }
  };
  MiniR4.Vision.Data(visionBuffer);

  int p = 0;
  int s = 0;
  while (p < 50) {
    int r = MiniR4.I2C2.MXLaserV2.getDistance();
    int l = MiniR4.I2C1.MXLaserV2.getDistance();
    if (r > l) s++;
    else s--;
    p += 1; 
  }

  moveDirection = 0;
  if (s > 0) {
    moveDirection = 1;
    greenCenter = 310;
    redCenter = 5;
    startLine = 9;
    endLine = 3;
  } else {
    moveDirection = -1;
    greenCenter = 10;
    redCenter = 305;
    startLine = 3;
    endLine = 9;
  }

  previousError = 0;
  objectColor = 255;
  objectX = 0;
  objectY = 0; 
  previousColor = 255;
  checkpointCount = 0;
  detectedLineColor = 10;
  trackingStep = 0;
  previousPosition = 0;
  backupTimer = 0;
  MiniR4.M1.resetCounter();
  encoderCheckpoint = abs(MiniR4.M1.getDegrees());
  finishFlag = false;

  steerServo(50 * moveDirection);
  MiniR4.M1.setSpeed(30);
  moveCM(6);
  steerServo(-50 * moveDirection);
  MiniR4.M1.setSpeed(-30);
  moveCM(4);
  MiniR4.M1.setSpeed(30);
  steerServo(50 * moveDirection);
  moveCM(12);
  steerServo(-50 * moveDirection);
  moveCM(4);
  
  while (true) {
        MiniR4.Vision.Data(visionBuffer);
    objectColor = visionBuffer[0];
    objectX = visionBuffer[1];
    objectY = visionBuffer[2];
    if (objectY < Y_IGNOR) objectColor = 255;
    MiniR4.M1.setSpeed(25);
    
    detectedLineColor = MiniR4.I2C3.MXColorV3.getColorID();
    scanTurn();


    if (objectColor != 255 and objectY < 100) {
        processLastStep(false);
        MiniR4.LED.setColor(1, 0, 0, 255);
        steerServo(int(objectX - 160) * 0.7, 30);
        MiniR4.M1.setSpeed(20);
        trackingStep = 1;
        finishFlag = false;
    } else if (objectColor == 0 && trackingStep == 1) {
        // MiniR4.M1.setBrake(true);
        // while(1);

        MiniR4.LED.setColor(1, 0, 255, 0);
        MiniR4.M1.setSpeed(30);
        steerServo(int(objectX - greenCenter) * 0.5, 70);
        finishFlag = true;
        previousColor = 0;
    } else if (objectColor == 1 && trackingStep == 1) {
        MiniR4.LED.setColor(1, 255, 0, 0);
        MiniR4.M1.setSpeed(30);
        steerServo(int(objectX - redCenter) * 0.65, 70);
        finishFlag = true;
        previousColor = 1;
    } else if (objectColor == 255 and detectedLineColor == 10) {
      processLastStep();
      MiniR4.LED.setColor(1, 0, 0, 0);
      MiniR4.M1.setSpeed(50);
      (moveDirection == 1 ? followLeftWall(63, 0.6, 2) : followRightWall(60, 1.4, 2));
      trackingStep = 0;
    } 

    checkLine();

    if (previousPosition == MiniR4.M1.getDegrees()) {
      if (backupTimer == 0) {
        backupTimer = millis();
      }
      if (millis() - backupTimer > 300) {
        backupTimer = 0;
        steerServo(0);
        MiniR4.M1.setSpeed(-100);
        moveCM(10);

        steerServo(45 * moveDirection);
        MiniR4.M1.setSpeed(100);
        moveCM(8);
        MiniR4.M1.setSpeed(25);
      }
    } else {
      backupTimer = 0;
    }

    previousPosition = MiniR4.M1.getDegrees();
    if (checkpointCount == DOOR) {
      MiniR4.M1.setBrake(true);
      break;
    } 
  }
}
