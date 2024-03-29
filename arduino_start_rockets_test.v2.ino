String Captcha;
String plug;
 
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Captcha = String(random(10)) + String(random(10)) + String(random(10)) + String(random(10));
  Serial.println("Captcha: " + Captcha);
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
    while(true){
      if (Serial.available() > 0){
      String id_data = Serial.readString();
      if (id_data == "plugen"){
        Serial.println("The plug is enabled");
        plug = "yes";
        }else if (id_data == "plugdi"){
          Serial.println("The plug is disable");
          plug = "no";
          }
      if (plug == "no"){
        start(id_data);
        }
    }
      }
    }else{
      Serial.println("Authorization failed. Console no (you need to put \"No Line Ending\"!)");
      }
  }

void start(String lift_off){
  String time_str;
  Serial.println(lift_off);
  if (lift_off == "start"){
    Serial.println("Command accepted. Please move away, very dangerous !!!");
    Serial.println("Countdown:");
    delay(5000);
    for (int time = 10; time >= -1; time--){
      if (time > 0){
          delay(1000);
          if (time < 10){
            time_str = "0" + String(time);
          }else{
            time_str = time;
          }
          Serial.println("T - 00:00:" + time_str);
        }
     
        else if(time == 0){
          delay(1000);
          Serial.println("T + 00:00:00");
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
