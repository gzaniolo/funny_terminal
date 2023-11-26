
// TODO remove for arduino use...
#include <stdint.h>
#include <stdlib.h>
// idek what to do...
// TODO idea: Should not be awful to just parse a file on startup

typedef struct one_pos_s {
  uint8_t x_lvl;
  uint8_t y_lvl;
} one_pos_t;

typedef struct one_char_s {
  uint8_t period;
  one_pos_t *pos_arr;
} one_char_t;

// When parsing the file, have it first read the period, malloc an area, then 
//  fill in each of the one_pos_t's 

one_char_t char_list[128];

int levelXList[] = {0,2,1,2,0,0};
int levelYList[] = {2,2,1,0,0,2};

// TODO can optimize these all with addition of capacitor short

void init_letters() {
  (char_list['a']).period = 7;
  ((char_list['a']).pos_arr) = (one_pos_t *)malloc(sizeof(one_pos_t) * (char_list['a']).period);
  ((char_list['a']).pos_arr)[0].x_lvl = 0;
  ((char_list['a']).pos_arr)[0].x_lvl = 2;
  ((char_list['a']).pos_arr)[1].x_lvl = 2;
  ((char_list['a']).pos_arr)[1].x_lvl = 2;
  // TODO there has to be a better way to do this...
}

// Letter "A" - len decreasible by 2
{0,0,1,2,0,2,2}
{2,1,0,1,1,1,2}

// Letter "B"
{0,2,1,2,0,0};
{2,2,1,0,0,2};

// Letter "C"
{0,0,2,0,0,2}
{2,0,0,0,2,2}

// Letter "D"
{0,0,1,2,0}
{2,0,1,2,2}

// Letter E
{0,0,2,0,0,2,0,0,2}
{2,0,0,0,1,1,1,2,2}

// For "f" it would be nice to short the capacitor...


