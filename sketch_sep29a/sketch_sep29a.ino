
// IMPORTANT VALUES:
// 10 nF - 10,000 pF
// resistors all 1k
//IDEAS 
// mosfet between letters - short out capcaitor - makes line look invisible between
//  letters


#include "letters.h"

// TODO this protocol appears to have its last move end at the bottom left
//  corner of the letter. See if this is good...
int levelXList[] = {0,2,1,2,0,0};
int levelYList[] = {2,2,1,0,0,2};
int penUpList[] =   {0,0,0,0,0,1};
// TODO not permanent by any means
int period = 6;

#define LOW_PIN_OFFSET 2
// TODO may eventually have to diverge into x and y pin counts
#define PIN_COUNT 6
#define VOLTAGE_LVLS_TOTAL (1 << PIN_COUNT)
// TODO may change once we actually write all the chars
#define VOLTAGE_LVLS_CHAR 4
// TODO may change, also if change bits per row/col
#define CHARS_PER_ROW (VOLTAGE_LVLS_TOTAL / VOLTAGE_LVLS_CHAR)


uint32_t curr_row = 0;
uint32_t curr_col = 0;

void write_pos(uint32_t row, uint32_t col) {
// These values are too tightly coupled to arduino pins to generalize. Just use
//  magic nums sadly
    PORTD = col << 2;
    PORTB = row;
}

void write_pen(uint32_t status) {
  // PORTC controls pins A0-A5 + some other weird stuff
  PORTC = status;
}


// TODO future have a letter parameter
void write_letter(char letter, uint32_t row, uint32_t col) {
  // TODO maybe wait a little bit after setting the voltage to actually draw the
  //  letter
  uint32_t row_offset = VOLTAGE_LVLS_TOTAL - (row * VOLTAGE_LVLS_CHAR) - 1;
  uint32_t col_offset = col * VOLTAGE_LVLS_CHAR; 

  for(int i = 0; letters[letter][i] != -1; i++) {
    int x_pos = letters[letter][i] & 0x3;
    int y_pos = letters[letter][i] >> 2;
    write_pos(row_offset - y_pos, col_offset + x_pos);
    // TODO adjust timing or remove
//    delayMicroseconds(50);
    delayMicroseconds(40);
    write_pen(penUpList[i]);
    delayMicroseconds(40);
  }
}


void setup() {
// If serial monitor necessary
  Serial.begin(115200);

  letters_init();

//TODO remove
  // Verify letters
  for(int i = 0; i < 128; i++) {
    Serial.print("For");
    Serial.println(char(i));
    for(int j = 0; letters[i][j] != -1; j++) {
      Serial.print(letters[i][j]);
      Serial.print(",");
    }
    Serial.println("\n");
  }

  // We initialize all pins lol. Review if it turns out we need more pins
  for(int i = 2; i < 14; i++) {
    pinMode(i,OUTPUT);
  }
  // Do these individually instead of with the ddrc=0x2
  // I don't know what the default is but we should probably keep it that way
  pinMode(A0, OUTPUT);
//  pinMode(A1, OUTPUT);

// Website with the arduino stuff
// https://forum.arduino.cc/t/using-port-c-as-digital-output/15981/2
// ctrl+f for: Port C includes the RESET pin on PC6 and an undefined pin on PC7. PC0 thru PC5 map to Arduino A0 (14) thru to A5 (19). 

  write_pos(0,0);
}


//TODO temporary
char to_print[] = "william is the goat of reading bad handwriting";


void loop() {

for(int i = 0; i < CHARS_PER_ROW; i++) {
  for(int j = 0; j < CHARS_PER_ROW; j++) {
    int pos_to_print = i * CHARS_PER_ROW + j;
    if(pos_to_print < 46) {
      write_letter(to_print[pos_to_print],i,j);
    } else {
      write_letter(' ',i,j);
    }
  }
}



// TODO tests to see if the circuit works

//  for(int i = 0; i < 64; i++) {
//    write_low(i);
//    write_high(i);
//    delayMicroseconds(100);
//  }

}
