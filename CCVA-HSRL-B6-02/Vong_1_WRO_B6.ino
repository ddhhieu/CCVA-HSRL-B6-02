#include <MatrixMiniR4.h>
float intergral;
float LastError;
float Error;
float Derivative;
float PID;

void Di_line_phai_voi_toc_do_n_quang_duong_n_Kp_n_Ki_n_Kd_n_cach_tuong_n(float speed, float cm, float Kp, float Ki, float Kd, float mm) {
  MiniR4.M1.resetCounter();
  intergral = 0;
  LastError = 0;
  while(!(abs(MiniR4.M1.getDegrees()) > ((cm / 20.5) * 360)))
  {
    MiniR4.M1.setSpeed(speed);
    Error = (constrain(MiniR4.I2C2.MXLaserV2.getDistance(), 0, 800) - (mm * 1.53)) / 10;
    intergral = intergral + Error;
    Derivative = Error - LastError;
    PID = ((Kp * Error) + (Ki * intergral)) + (Kd * Derivative);
    MiniR4.RC1.setAngle(constrain((90 - PID), 54, 120));
    LastError = Error;
  }
  MiniR4.M1.setBrake(true);
}

void Di_mu_n_voi_toc_do_n(float cm, float speed) {
  MiniR4.M1.resetCounter();
  MiniR4.M1.setSpeed(speed);
  while(!(abs(MiniR4.M1.getDegrees()) > ((cm / 20.5) * 360)));
  MiniR4.M1.setBrake(true);
}

void Ra_khoi_bai_do_xe() {
  MiniR4.RC1.setAngle(35);
  delay(300);
  Di_mu_n_voi_toc_do_n(25, 1);
  delay(300);
  MiniR4.RC1.setAngle(155);
  delay(300);
  Di_mu_n_voi_toc_do_n(25, 1);
  delay(300);
  MiniR4.RC1.setAngle(90);
}

void Di_line_giua_voi_toc_do_n_quang_duong_n_Kp_n_Ki_n_Kd_n(float toc_do_giua, float cm_giua, float Kp, float Ki, float Kd) {
  MiniR4.M1.resetCounter();
  intergral = 0;
  LastError = 0;
  while(!(abs(MiniR4.M1.getDegrees()) > ((cm_giua / 20.5) * 360)))
  {
    MiniR4.M1.setSpeed(toc_do_giua);
    Error = constrain((MiniR4.I2C2.MXLaserV2.getDistance() - MiniR4.I2C1.MXLaserV2.getDistance()), 0, 100) / 10;
    intergral = intergral + Error;
    Derivative = Error - LastError;
    PID = ((Kp * Error) + (Ki * intergral)) + (Kd * Derivative);
    MiniR4.RC1.setAngle(constrain((90 - PID), 60, 120));
    LastError = Error;
  }
  MiniR4.M1.setBrake(true);
}

void Di_line_trai_toc_do_n_cm_n_Kp_n_Ki_n_Kd_n_cach_tuong_n(float toc_do, float cm, float Kp, float Ki, float Kd, float mm) {
  MiniR4.M1.resetCounter();
  intergral = 0;
  LastError = 0;
  while(!(abs(MiniR4.M1.getDegrees()) > ((cm / 20.5) * 360)))
  {
    MiniR4.M1.setSpeed(toc_do);
    Error = (constrain(MiniR4.I2C1.MXLaserV2.getDistance(), 0, 800) - (mm * 1.53)) / 10;
    intergral = intergral + Error;
    Derivative = Error - LastError;
    PID = ((Kp * Error) + (Ki * intergral)) + (Kd * Derivative);
    MiniR4.RC1.setAngle(constrain((90 + PID), 60, 120));
    LastError = Error;
  }
  MiniR4.M1.setBrake(true);
}

unsigned int CamData[10];
int CamStatus;
void Di_cung_chieu_kim_dong_ho() {
  for(int i_0 = 0; i_0 < 11; i_0++)
  {
    while(!((MiniR4.I2C3.MXColorV3.getV() > 42.5)||(MiniR4.I2C3.MXColorV3.getV() < 39.5)));
    MiniR4.RC1.setAngle(60);
    Di_mu_n_voi_toc_do_n(35, 80);
    Di_line_trai_toc_do_n_cm_n_Kp_n_Ki_n_Kd_n_cach_tuong_n(100, 145, 1.2, 0.02, 0.8, 200);
    MiniR4.RC1.setAngle(90);
    MiniR4.M1.setSpeed(80);
  }
  while(!((MiniR4.I2C3.MXColorV3.getV() > 42.5)||(MiniR4.I2C3.MXColorV3.getV() < 39.5)));
  MiniR4.RC1.setAngle(60);
  Di_mu_n_voi_toc_do_n(35, 80);
  Di_line_trai_toc_do_n_cm_n_Kp_n_Ki_n_Kd_n_cach_tuong_n(100, 80, 1.2, 0.02, 0.8, 200);
}

void DiNguocChieuKimDongHo() {
  for(int i_1 = 0; i_1 < 11; i_1++)
  {
    while(!(MiniR4.I2C3.MXColorV3.getV() > 45));
    MiniR4.RC1.setAngle(120);
    Di_mu_n_voi_toc_do_n(35, 80);
    Di_line_phai_voi_toc_do_n_quang_duong_n_Kp_n_Ki_n_Kd_n_cach_tuong_n(100, 145, 1.2, 0.02, 0.8, 120);
    MiniR4.RC1.setAngle(90);
    MiniR4.M1.setSpeed(80);
  }
  while(!(MiniR4.I2C3.MXColorV3.getV() > 45));
  MiniR4.RC1.setAngle(120);
  Di_mu_n_voi_toc_do_n(35, 80);
  Di_line_phai_voi_toc_do_n_quang_duong_n_Kp_n_Ki_n_Kd_n_cach_tuong_n(100, 80, 1.2, 0.02, 0.8, 120);
}

void setup()
{
  MiniR4.begin();
  MiniR4.PWR.setBattCell(2);
  Serial.begin(9600);
  MiniR4.I2C3.MXColorV3.begin();
  MiniR4.Vision.Begin();
  MiniR4.I2C1.MXLaserV2.begin();
  MiniR4.I2C2.MXLaserV2.begin();
  MiniR4.M1.setReverse(false);
  MiniR4.RC1.setAngle(90);
}

void loop()
{
  if(MiniR4.BTN_UP.getState())
  {
    MiniR4.RC1.setAngle(90);
    MiniR4.M1.setSpeed(60);
    while(!((MiniR4.I2C3.MXColorV3.getV() > 42.5)||(MiniR4.I2C3.MXColorV3.getV() < 39.5)));
    MiniR4.M1.setBrake(true);
    if(MiniR4.I2C1.MXLaserV2.getDistance() > MiniR4.I2C2.MXLaserV2.getDistance()) 
    {
      DiNguocChieuKimDongHo();
    }
    else
    {
      Di_cung_chieu_kim_dong_ho();
    }
  }

}