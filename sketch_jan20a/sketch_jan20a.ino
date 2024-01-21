

char buf[256 + 1];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(2,OUTPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
  
  // Just have this keep pooping out "terminals"
  
  // For initial debugging purposes, just have this print out what it recieves to start off, to see if
  //  we can have a cpp program

  
  char byte = 0;
  int idx = 0;
  if(Serial.available() > 0) {
    while(byte != '\n') {
      if(Serial.available() > 0) {
        byte = Serial.read();
        buf[idx] = byte;
        byte++;
        idx++;
      }
    }
    if (idx < 256+1) {
      digitalWrite(2,HIGH);
      Serial.write(buf,idx);
      digitalWrite(2,LOW);
    }

    byte = 0;
    // Serial.println("done printing");
  }
}

