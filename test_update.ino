int count;
String Captcha;
String plug;
 
void setup() {
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Captcha = String(random(10)) + String(random(10)) + String(random(10)) + String(random(10));
  Serial.println(Captcha);
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
      Serial.println("Authorization failed. Console no");
      }
  }

void start(String lift_off){
  Serial.println(lift_off);
  if (lift_off == "start"){
    Serial.println("Command accepted. Please move away, very dangerous !!!");
    Serial.println("Countdown:");
    delay(5000);
    for (int time = 10; time >= -1; time--){
      if (time > 0){
          delay(1000);
          Serial.println(time);
        }
     
        else if(time == 0){
          delay(1000);
          Serial.println("start-up");
          status_start_ok();
        }
    }
  }    
  else{
      Serial.println("Launch not allowed!");
      }
  }

void status_start_ok(){
  while(true){
    Serial.println(count);
    count++;
    delay(1000);
    }
  }
