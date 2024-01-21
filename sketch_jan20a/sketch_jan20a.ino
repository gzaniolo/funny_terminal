
int iter;

char buf[256];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  iter = 0;
}



void loop() {
  // put your main code here, to run repeatedly:
  
  // Just have this keep pooping out "terminals"
  
  // For initial debugging purposes, just have this print out what it recieves to start off, to see if
  //  we can have a cpp program


  int byte;
  if(Serial.available() > 0) {
    byte = Serial.read();
    Serial.print(char(byte));
    if(iter == 0) {
      Serial.println();
    }
    iter = (iter + 1) % 256;
  }
}

