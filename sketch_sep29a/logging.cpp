#include <Arduino.h>

extern "C" {
  #include "logging.h"
}

void log_char(const char c) {
  Serial.println(c);
}

void log_int(const int i) {
  Serial.println(i);
}

void log_str(const char *str) {
  Serial.println(str);
}

void log_delay(int i) {
  delay(i);
}

