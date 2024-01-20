#include <letters.h>
#include <letters_gen.h>

void letters_init() {
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

  for(int i = 0; i < 128; i++) {
    Serial.println("For %c:\n",i);
    for(int j = 0; letters[i].xList[j] != -1; j++) {
      Serial.print("%d,",letters[i].xList[j]);
    }
    Serial.println("\n");
  }
}