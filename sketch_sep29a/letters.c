#include "letters_gen.h"
#include "letters.h"
#include "logging.h"

void letters_init() {
  
  int curr_idx = 0;
  for(int i = 0; i < 128; i++) {
    letters[i] = &fullLetterList[curr_idx];
    while(fullLetterList[curr_idx] != -1) {
      curr_idx++;
    }
    curr_idx++;
  }

}
