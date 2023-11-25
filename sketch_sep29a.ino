// FOR O
//int levelList[] =  {0,1,2,3,4,3,2,1};
//period = 8

// FOR "B" NOTE -> initial test, new has less voltage levels
int levelYList[] = {0,2,4,3,2,1,0};
int levelXList[] = {0,0,0,4,0,4,0};
int period = 7;

// TODO
//int levelYList[] = {0,1,2,3,1,1,0};
//int levelXList[] = {0,1,4,2,0,4,0};
//int period = 7;

int p5lvl = 0;
int p6lvl = 0;

#define PIN_COUNT 6

typedef struct one_char_s {
  int level_x_list[];
  int level_y_list[];
} one_char_t;

one_char_t B;
void initialize_B() {
  B->
}

one_char_t *char_list[128];

void initialize_char_list() {
//  somehow initialize the char array in here
// I could just have all the constants in a different file, and expose the big array of tyype one_char_t* [];...
//  char_list['B'] = 
//GUUUHHHHHHH I forgot arduino is c++ and not c... Could we use classes/is something improperly arcitected??
}

void write_low(uint32_t val) {
  for(int i = 0; i < PIN_COUNT; i++) {
    uint32_t temp = val << 31 - i;
    temp >>= 31;
    if(temp) {
      digitalWrite(i,HIGH);
    } else {
      digitalWrite(i,LOW);
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // NOTE: this is a previous draft that only prints one character...
  
  // put your main code here, to run repeatedly:
  analogWrite(5,(225/4) * levelXList[p5lvl]);
  analogWrite(6,(225/4) * levelYList[p6lvl]);
  delay(10);
  p5lvl = (p5lvl + 1) % period;
  p6lvl = (p6lvl + 1) % period;
}
