#include "letters_gen.h"
#include "letters.h"

void letters_init() {
  letters_gen_init();
  int curr_idx = 0;
  for(int i = 0; i < 128; i++) {
    letters[i].xList = &(fullXList[curr_idx]);
    letters[i].yList = &(fullYList[curr_idx]);
    letters[i].penUpList = &(fullPenUpList[curr_idx]);
    while(fullXList[curr_idx] != -1) {
      curr_idx++;
    }
    curr_idx++;
  }

}
