
// // FOR "B" NOTE -> initial test, new has less voltage levels
// int levelYList[] = {0,2,4,3,2,1,0};
// int levelXList[] = {0,0,0,4,0,4,0};
// int period = 7;

// TODO this protocol appears to have its last move end at the bottom left
//  corner of the letter. See if this is good...
int levelXList[] = {0,2,1,2,0,0};
int levelYList[] = {2,2,1,0,0,2};
// TODO not permanent by any means
int period = 6;

#define LOW_PIN_OFFSET 2
// TODO may eventually have to diverge into x and y pin counts
#define PIN_COUNT 4
#define VOLTAGE_LVLS_TOTAL (1 << PIN_COUNT)
// TODO may change once we actually write all the chars
#define VOLTAGE_LVLS_CHAR 4
// TODO may change, also if change bits per row/col
#define CHARS_PER_ROW (VOLTAGE_LVLS_TOTAL / VOLTAGE_LVLS_CHAR)


uint32_t curr_row = 0;
uint32_t curr_col = 0;

// Write to "low 'x' pins" 
void write_low(uint32_t val) {
  
  for(int i = 0; i < PIN_COUNT; i++) {
    uint32_t temp = val << 31 - i;
    temp >>= 31;
    if(temp) {
      digitalWrite(i + LOW_PIN_OFFSET,HIGH);
    } else {
      digitalWrite(i + LOW_PIN_OFFSET,LOW);
    }
  }
}

// Write to "high 'y' pins" 
void write_high(uint32_t val) {
//  Serial.println(val);
  for(int i = 0; i < PIN_COUNT; i++) {
    uint32_t temp = val << 31 - i;
    temp >>= 31;
    if(temp) {
//      TODO fix this!!! magic numbers
//      digitalWrite(i + PIN_COUNT + LOW_PIN_OFFSET,HIGH);

// Jamk
      digitalWrite(i + PIN_COUNT + LOW_PIN_OFFSET + 2,HIGH);

    } else {
//      digitalWrite(i + PIN_COUNT + LOW_PIN_OFFSET,LOW);
// jank
      digitalWrite(i + PIN_COUNT + LOW_PIN_OFFSET + 2,LOW);

    }
  }
}

void write_pos(uint32_t row, uint32_t col) {
  // TODO magic numbers
//    uint32_t temp = (row << 8) | (col << 2);
    PORTD = col << 2;
    PORTB = row;
}

// TODO future more params
void write_letter(uint32_t row, uint32_t col) {
  uint32_t row_offset = VOLTAGE_LVLS_TOTAL - (row * VOLTAGE_LVLS_CHAR) - 1;
  uint32_t col_offset = col * VOLTAGE_LVLS_CHAR; 
  for(int i = 0; i < period; i++) {
//    Serial.print(col_offset + levelXList[i]);
//    Serial.print(" ");
//    Serial.println(row_offset - levelYList[i]);
//    write_low(col_offset + levelXList[i]);
//    write_high(row_offset - levelYList[i]); 
    write_pos(row_offset - levelYList[i], col_offset + levelXList[i]);
    delayMicroseconds(100);
//    delay(1000);
  }
}


void setup() {
  // put your setup code here, to run once:
//  Serial.begin(115200);

  for(int i = 0; i < PIN_COUNT; i++) {
    pinMode(i + LOW_PIN_OFFSET,OUTPUT);
  }
  for(int i = LOW_PIN_OFFSET + PIN_COUNT; i < LOW_PIN_OFFSET + (PIN_COUNT * 2); i++) {
    pinMode(i + LOW_PIN_OFFSET,OUTPUT);
  }

  write_high(0);
  write_low(0);
}

void loop() {

  // TODO a delay could solve some issues I guess...

//  delay(10000);
//   Serial.println("printing new letter");
for(int i = 0; i < CHARS_PER_ROW; i++) {
  for(int j = 0; j < CHARS_PER_ROW; j++) {
//  for(int j = 0; j < 1; j++) {
    write_letter(i,j);
  }
}


// TODO tests to see if the circuit works

//  for(int i = 0; i < 64; i++) {
//    write_low(i);
//    write_high(i);
//    delayMicroseconds(100);
//  }

}




// THE GARBAGE CAN
// DO WITH THIS WHAT YOU WILL

// // TODO: do we have a max number of coords, or should we just print as soon as 
// //  we can? Worst case makes the most sense bc we can case on overlap...
// // TODO for now it is 7 but change it as seen fit.
// typedef struct one_char_s {
//   int level_x_list[7];
//   int level_y_list[7];
// } one_char_t;

// // For now we only need the letter "B" - in the future, make a convenient 
// //  array-like structure containing all of the info for the letter we need in
// //  its corresponding ascii index
// // one_char_t B;
// // void initialize_B() {
//   // B->
// // }

// // void initialize_char_list() {
// // //  somehow initialize the char array in here
// // // I could just have all the constants in a different file, and expose the big array of tyype one_char_t* [];...
// // //  char_list['B'] = 
// // //GUUUHHHHHHH I forgot arduino is c++ and not c... Could we use classes/is something improperly arcitected??
// // }

// // TODO this \/ could be it /\ 
// // one_char_t *char_list[128];


// // TODO this looks like trash idk what it is
// // FOR O
// //int levelList[] =  {0,1,2,3,4,3,2,1};
// //period = 8
// // TODO
// //int levelYList[] = {0,1,2,3,1,1,0};
// //int levelXList[] = {0,1,4,2,0,4,0};
// //int period = 7;
