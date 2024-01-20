
#ifndef _LETTERS_H_
#define _LETTERS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

typedef struct letter_s {
  uint8_t *xList;
  uint8_t *yList;
  uint8_t *penUpList;
} letter_t;

letter_t letters[128];

void letters_init();

#ifdef __cplusplus
}
#endif

#endif
