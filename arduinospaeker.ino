#include <SD.h>                           //include SD module library
#include <TMRpcm.h>                       //include speaker control library
#include <Wire.h>
#include <DS3231.h>


int Year 2021;
int Mounth 02;
int Day 11;
int Hour 11;
int Minute 11;
int Second 11;


#define SD_ChipSelectPin 4                //define CS pin
DS3231 clock;
RTCDateTime dt;
TMRpcm tmrpcm;                            //crete an object for speaker library

void setup(){
  clock.armAlarm1(false);
  clock.armAlarm2(false);
  clock.clearAlarm1();
  clock.clearAlarm2();
  
  Serial.begin(9600);  
  clock.setDateTime(Year, Month, Day, Hour, Minute, Second);  // Manual (Year, Month, Day, Hour, Minute, Second)
  
  
  // Set Alarm1 - Every 20s in each minute
  // setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(0, 0, 0, 20, DS3231_MATCH_S);

  // Set Alarm2 - Every 01m in each hour
  // setAlarm2(Date or Day, Hour, Minute, Mode, Armed = true)
  clock.setAlarm2(0, 0, 1,     DS3231_MATCH_M);
    
  checkAlarms();
  tmrpcm.speakerPin = 9;                  //define speaker pin. 
  
  if (!SD.begin(SD_ChipSelectPin)) {      //see if the card is present and can be initialized
    
    return;                               //don't do anything more if not
  }
  
  tmrpcm.setVolume(6);                    //0 to 7. Set volume level
  tmrpcm.play("1.wav");         //the sound file "1" will play each time the arduino powers up, or is reset
}

void loop(){
if (clock.isArmed1())
  {
    a2 = clock.getAlarm1();
    tmrpcm.play("1.wav");
}
  
if (clock.isArmed2())
  {
    a2 = clock.getAlarm2();
    tmrpcm.play("2.wav");
}
