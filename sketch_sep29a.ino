
// // FOR "B" NOTE -> initial test, new has less voltage levels
// int levelYList[] = {0,2,4,3,2,1,0};
// int levelXList[] = {0,0,0,4,0,4,0};
// int period = 7;

// TODO this protocol appears to have its last move end at the bottom left
//  corner of the letter. See if this is good...
int levelYList[] = {2,2,1,0,0,2};
int levelXList[] = {0,2,1,2,0,0};
// TODO not permanent by any means
int period = 6;


// TODO may eventually have to diverge into x and y pin counts
#define PIN_COUNT 6
#define VOLTAGE_LVLS_TOTAL (1 << PIN_COUNT)
// TODO may change once we actually write all the chars
#define VOLTAGE_LVLS_CHAR 4
// TODO may change, also if change bits per row/col
#define CHARS_PER_ROW = (VOLTAGE_LVLS_TOTAL / VOLTAGE_LVLS_CHAR)


uint32_t curr_row = 0;
uint32_t curr_col = 0;

// Write to "low 'x' pins" 
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

// Write to "high 'y' pins" 
void write_high(uint32_t val) {
  for(int i = 0; i < PIN_COUNT; i++) {
    uint32_t temp = val << 31 - i;
    temp >>= 31;
    if(temp) {
      digitalWrite(i + PIN_COUNT,HIGH);
    } else {
      digitalWrite(i + PIN_COUNT,LOW);
    }
  }
}

// TODO future more params
void write_letter(uint32_t row, uint32_t col) {
  uint32_t row_offset = VOLTAGE_LVLS_TOTAL - (col * VOLTAGE_LVLS_CHAR);
  uint32_t col_offset = row * VOLTAGE_LVLS_CHAR; 
  for(int i = 0; i < period; i++) {
    write_low(col_offset + levelXList[i]);
    write_high(row_offset + levelYList[i]);
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  // TODO a delay could solve some issues I guess...
  delay(10);
  write_letter(curr_row, curr_col);
  curr_row = (curr_row + ((curr_col + 1) / CHARS_PER_ROW)) % CHARS_PER_ROW;
  curr_col = (curr_col + 1) % CHARS_PER_ROW;
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