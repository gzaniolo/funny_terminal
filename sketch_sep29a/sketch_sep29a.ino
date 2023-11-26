
// IMPORTANT VALUES:
// 10 nF - 10,000 pF
// resistors all 1k
//IDEAS 
// mosfet between letters - short out capcaitor - makes line look invisible between
//  letters


#include <letters.h>

// TODO this protocol appears to have its last move end at the bottom left
//  corner of the letter. See if this is good...
int levelXList[] = {0,2,1,2,0,0};
int levelYList[] = {2,2,1,0,0,2};
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


// TODO future have a letter parameter
void write_letter(uint32_t row, uint32_t col) {
  uint32_t row_offset = VOLTAGE_LVLS_TOTAL - (row * VOLTAGE_LVLS_CHAR) - 1;
  uint32_t col_offset = col * VOLTAGE_LVLS_CHAR; 
  for(int i = 0; i < period; i++) {
    write_pos(row_offset - levelYList[i], col_offset + levelXList[i]);
    delayMicroseconds(50);
  }
}


void setup() {
// If serial monitor necessary
//  Serial.begin(115200);

  // MAKE THESE MACROS WHEN WE ACTUALLY NEED TO
//  for(int i = 0; i < PIN_COUNT; i++) {
//    pinMode(i + LOW_PIN_OFFSET,OUTPUT);
//  }
//  for(int i = LOW_PIN_OFFSET + PIN_COUNT; i < LOW_PIN_OFFSET + (PIN_COUNT * 2); i++) {
//    pinMode(i + LOW_PIN_OFFSET,OUTPUT);
//  }

  // We initialize all pins lol. Review if it turns out we need more pins
  for(int i = 2; i < 14; i++) {
    pinMode(i,OUTPUT);
  }


  write_pos(0,0);
}

void loop() {

for(int i = 0; i < CHARS_PER_ROW; i++) {
  for(int j = 0; j < CHARS_PER_ROW; j++) {
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
