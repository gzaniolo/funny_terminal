

typedef struct letter_s {
  int *xList;
  int *yList;
  int *penUpList;
} letter_t;

letter_t letters[128];

void letters_init();
