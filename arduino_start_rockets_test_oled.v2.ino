#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

String Captcha;
String plug;

// Arduino: SDA – A4, SCL – A5
// Wemos: SDA – D2, SCL – D1
 
void setup() {
  oled.init();        // инициализация
  oled.clear();       // очистка
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Captcha = String(random(10)) + String(random(10)) + String(random(10)) + String(random(10));
  Serial.println("Captcha: " + Captcha);
  oled.setScale(1);   // масштаб текста (1..4)
  oled.setCursorXY(2, 25);
  oled.print("Captcha: " + Captcha);
}

void loop() {
    if (Serial.available() > 0){
      String id_data = Serial.readString();
      Captcha_func(id_data);
    }   
}

void Captcha_func(String number){
  if (number == Captcha){
    Serial.println("Authorization was successful. Console yes");
    Serial.println("Write \"plugdi\" activates commands, \"plugen\" prohibits entering commands");
    Serial.println("Write \"start\" to start the launch(you need to enable \"plugdi\")");
    Serial.println("The plug is enabled");
    oled.clear(); 
    oled.setScale(1);   // масштаб текста (1..4)
    oled.setCursorXY(0, 0);
    oled.print("Authorized.Console on");
    oled.setCursorXY(0, 10);
    oled.print("commands:");
    oled.setCursorXY(0, 25);
    oled.print("-plugdi -plugen");
    oled.setCursorXY(0, 37);
    oled.print("-start");
    oled.setCursorXY(0, 53);
    oled.print("The plug is enabled");
    while(true){
      if (Serial.available() > 0){
      String id_data = Serial.readString();
      if (id_data == "plugen"){
        Serial.println("The plug is enabled");
        oled.clear(); 
        oled.setScale(1);   // масштаб текста (1..4)
        oled.setCursorXY(0, 0);
        oled.print("Authorized.Console on");
        oled.setCursorXY(0, 10);
        oled.print("commands:");
        oled.setCursorXY(0, 25);
        oled.print("-plugdi -plugen");
        oled.setCursorXY(0, 37);
        oled.print("-start");
        oled.setCursorXY(0, 53);
        oled.print("The plug is enabled");
        plug = "yes";
        }else if (id_data == "plugdi"){
          Serial.println("The plug is disable");
          oled.clear(); 
          oled.setScale(1);   // масштаб текста (1..4)
          oled.setCursorXY(0, 0);
          oled.print("Authorized.Console on");
          oled.setCursorXY(0, 10);
          oled.print("commands:");
          oled.setCursorXY(0, 25);
          oled.print("-plugdi -plugen");
          oled.setCursorXY(0, 37);
          oled.print("-start");
          oled.setCursorXY(0, 53);
          oled.print("The plug is disable");
          plug = "no";
          }
      if (plug == "no"){
        start(id_data);
        }
    }
      }
    }else{
      Serial.println("Authorization failed. Console no (you need to put \"No Line Ending\"!)");
      oled.clear(); 
      oled.setScale(1);   // масштаб текста (1..4)
      oled.setCursorXY(0, 0);
      oled.print("Authorization failed");
      }
  }

void start(String lift_off){
  String time_str;
  Serial.println(lift_off);
  if (lift_off == "start"){
    Serial.println("Command accepted. Please move away, very dangerous !!!");
    Serial.println("Countdown:");
    oled.clear(); 
    oled.setScale(1);   // масштаб текста (1..4)
    oled.setCursorXY(0, 0);
    oled.print("Command accepted");
    oled.setCursorXY(0, 15);
    oled.print("Please move away,");
    oled.setCursorXY(0, 25);
    oled.print("very dangerous");
    oled.setCursorXY(0, 45);
    oled.print("Countdown:");

    delay(5000);
    oled.clear(); 
    for (int time = 10; time >= -1; time--){
      if (time > 0){
          delay(1000);
          if (time < 10){
            time_str = "0" + String(time);
          }else{
            time_str = time;
          }
          Serial.println("T - 00:00:" + time_str);
          oled.setScale(2);   // масштаб текста (1..4)
          oled.setCursorXY(2, 25);
          oled.print("T-00:00:" + time_str);
        }
     
        else if(time == 0){
          delay(1000);
          Serial.println("T + 00:00:00");
          oled.setScale(2);   // масштаб текста (1..4)
          oled.setCursorXY(2, 25);
          oled.print("T-00:00:" + time_str);
          status_start_ok();
        }
    }
  }    
  else{
      Serial.println("Launch not allowed!");
      }
  }

void status_start_ok(){
  int seconds=0;
  int minute=0;
  int hours=0;
  String seconds_str;
  String minute_str;
  String hours_str;
  while(true){
    delay(1000);
    seconds++;
    if (seconds < 10){
            seconds_str = "0" + String(seconds);
          }else{
            seconds_str = seconds;
          }
    if (minute < 10){
            minute_str = "0" + String(minute);
          }else{
            minute_str = minute;
          }
    if (hours < 10){
            hours_str = "0" + String(hours);
          }else{
            hours_str = hours;
          }
    Serial.println("T + " + hours_str + ":" + minute_str + ":" + seconds_str );
    oled.setScale(2);   // масштаб текста (1..4)
    oled.setCursorXY(2, 25);
    oled.print("T+" + hours_str + ":" + minute_str + ":" + seconds_str );
    if (seconds == 59){
      minute++;
      seconds = -1;
    }
    if (minute == 59){
      hours++;
      minute = -1;
    }
     if (Serial.available() > 0){
      String id_data = Serial.readString();
      if (id_data == "stop"){
        Serial.println("stop");
        Serial.println("Captcha: " + Captcha);
        while(true){
        if (Serial.available() > 0){
          String id_data = Serial.readString();
          Captcha_func(id_data);
          }
        }
        }
    }
    }
  }  
