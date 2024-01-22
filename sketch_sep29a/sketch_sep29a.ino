
// IMPORTANT VALUES:
// 10 nF - 10,000 pF
// resistors all 1k
//IDEAS 
// mosfet between letters - short out capcaitor - makes line look invisible between
//  letters


// NOTE: something is getting corrupted on the arduino end :(


#include "letters.h"


#define LOW_PIN_OFFSET 2
// TODO may eventually have to diverge into x and y pin counts
#define PIN_COUNT 6
#define VOLTAGE_LVLS_TOTAL (1 << PIN_COUNT)
// TODO may change once we actually write all the chars
#define VOLTAGE_LVLS_CHAR 4
// TODO may change, also if change bits per row/col
#define CHARS_PER_ROW (VOLTAGE_LVLS_TOTAL / VOLTAGE_LVLS_CHAR)

#define CHAR_COUNT (CHARS_PER_ROW * CHARS_PER_ROW)


uint32_t curr_row = 0;
uint32_t curr_col = 0;

char char_buf[CHAR_COUNT];


void refresh_buf() {
  if(Serial.available() > 0) {

    //Serial.println("chars available");
    int idx = 0;
    char byte = 0;
    while(byte != '\n') {
      if(Serial.available() > 0) {
        byte = Serial.read();
        char_buf[idx] = byte;
        Serial.print(byte);
        idx++;
      }
    }
    while(idx < CHAR_COUNT) {
      char_buf[idx] = ' ';
      idx++;
    }
    Serial.println("done printing");
  }
}


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


void write_letter(char letter, uint32_t row, uint32_t col) {
  // TODO maybe wait a little bit after setting the voltage to actually draw the
  //  letter
  uint32_t row_offset = VOLTAGE_LVLS_TOTAL - (row * VOLTAGE_LVLS_CHAR) - 1;
  uint32_t col_offset = col * VOLTAGE_LVLS_CHAR; 

  for(int i = 0; letters[letter][i] != -1; i++) {
    int x_pos = letters[letter][i] & 0x3;
    int y_pos = (letters[letter][i] >> 2) & 0x3;
    int pen_up = (letters[letter][i] >> 4) & 0x3;
    write_pos(row_offset - y_pos, col_offset + x_pos);
    // TODO adjust timing or remove
    //  delayMicroseconds(50);
    delayMicroseconds(40);
    write_pen(pen_up);
    delayMicroseconds(40);
  }
}


void setup() {
// If serial monitor necessary
  Serial.begin(115200);

  letters_init();

  for(int i = 0; i < CHAR_COUNT; i++) {
    char_buf[i] = ' ';
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




void loop() {

  for(int i = 0; i < CHARS_PER_ROW; i++) {
    for(int j = 0; j < CHARS_PER_ROW; j++) {
      int pos_to_print = i * CHARS_PER_ROW + j;
  
      // Prints all ascii chars for debugging
      // if(pos_to_print < 128) {
      //   write_letter((char)pos_to_print,i,j);
      // } else {
      //   write_letter(' ',i,j);
      // }
  
      write_letter(char_buf[pos_to_print],i,j);
    }
  
  }
  refresh_buf();




// TODO tests to see if the circuit works

//  for(int i = 0; i < 64; i++) {
//    write_low(i);
//    write_high(i);
//    delayMicroseconds(100);
//  }

}
