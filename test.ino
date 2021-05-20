int count;

void setup() {
  
  Serial.begin(9600);
  
}

void loop() {
  
    if (Serial.available() > 0){
      String id_data = Serial.readString();
      start(id_data);
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
